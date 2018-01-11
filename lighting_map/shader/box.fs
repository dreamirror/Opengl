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

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;
uniform sampler2D ourTexture;

void main()
{
	//������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff =  max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextCoords));

	//���淴��
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular =  spec * light.specular * vec3(texture(material.specular, TextCoords));

	//������
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextCoords));

	vec4 textureColor = texture(ourTexture, TextCoords);
	vec3 result = (ambient + diffuse + specular) *objectColor * textureColor;
    FragColor = vec4( result, 1.0);
}