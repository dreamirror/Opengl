#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

in vec3 Normal;//������
in vec3 Position;//Ƭ�ε�λ��

uniform vec3 cameraPos; //�������λ��
uniform samplerCube skybox; //��պе�����

uniform sampler2D texture1;

void main()
{   //vec3 I = normalize(Position - cameraPos);//�ӽǵ�����
	//vec3 R = reflect(I,normalize(Normal)); //����Ƭ�ε�����

    //FragColor = vec4(texture(skybox,R).rgb,1.0);//�����Χ����������

	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I,normalize(Normal),ratio);
	FragColor = vec4(texture(skybox,R).rgb,1.0);
}