#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoords;
uniform vec3 objectColor;
uniform vec3 lightColor;


uniform vec3 viewPos; //�������λ��
float specularStrength = 0.5; //������ǿ��

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
	float ambientness;
};
uniform Material material;

struct Light{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//˥����ʽ����
	float constant;
	float linear;
	float quadratic;

	//�ֵ�Ͳ����Ч�н�
	float cutOff;

};
uniform Light light;
uniform sampler2D ourTexture;

void main()
{
	//�ֵ�Ͳ
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(FragPos-light.direction);;
	float theta = dot(lightDir,normalize(-light.direction));
	float distance = length(light.position - FragPos);
	vec3 diffuse;
	vec3 specular;
	if (theta > light.cutOff){
		//������

		float diff =  max(dot(norm,lightDir),0.0);
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextCoords)) ;


		//���淴��
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir,norm);
		float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
		specular =  spec * light.specular * vec3(texture(material.specular, TextCoords)) ;
	}else
	{
	
	}


	//������
	vec3 ambient = material.ambientness * light.ambient * vec3(texture(material.diffuse, TextCoords));

	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	ambient  *= attenuation;  
   diffuse   *= attenuation;
   specular *= attenuation;   

	vec3 result = (ambient + diffuse + specular);
    FragColor = vec4( result, 1.0);
}