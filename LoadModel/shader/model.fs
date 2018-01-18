#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D texture_diffuse1;
uniform vec3 viewPos; //摄像机的位置

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

	//衰减公式参数
	float constant;
	float linear;
	float quadratic;

	//手电筒的有效夹角
	float cutOff;

};
uniform Light light;

void main()
{    
	//手电筒
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(FragPos-light.position);;
	float theta = dot(lightDir,normalize(-light.position));
	float distance = length(light.position - FragPos);
	vec3 diffuse;
	vec3 specular;

	//漫反射
	float diff =  max(dot(-norm,lightDir),0.0);
	diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords)) ;


	//镜面反射
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,-norm);
	specular =  light.specular * vec3(texture(texture_diffuse1, TexCoords)) ;

	//环境光
	vec3 ambient = material.ambientness * light.ambient * vec3(texture(texture_diffuse1, TexCoords));

	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	ambient  *= attenuation;  
	diffuse   *= attenuation;
	specular *= attenuation;   

	vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result,1.0f);//texture(texture_diffuse1, TexCoords);
}