#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

in vec3 Normal;//法向量
in vec3 Position;//片段的位置

uniform vec3 cameraPos; //摄像机的位置
uniform samplerCube skybox; //天空盒的纹理

uniform sampler2D texture1;

void main()
{   //vec3 I = normalize(Position - cameraPos);//视角的向量
	//vec3 R = reflect(I,normalize(Normal)); //反射片段的向量

    //FragColor = vec4(texture(skybox,R).rgb,1.0);//获得周围环境的纹理

	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I,normalize(Normal),ratio);
	FragColor = vec4(texture(skybox,R).rgb,1.0);
}