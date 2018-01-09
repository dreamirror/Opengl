#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
uniform vec3 objectColor;
uniform vec3 lightColor;


uniform vec3 viewPos; //摄像机的位置
float specularStrength = 0.5; //镜面光的强度

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
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

void main()
{
	//漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff =  max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * material.diffuse;

	//镜面反射
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = material.shininess * spec * lightColor;

	//环境光
	vec3 ambient = lightColor * material.ambientness;

	vec3 result = (ambient + diffuse + specular) *objectColor;
    FragColor = vec4( result, 1.0);
}