#include <GLTools.h>
#include<GLShaderManager.h>

#ifdef __APPLE__
#include<glut/glut.h>
#else
#include<GL/glut.h>

#endif

GLBatch squreBatch;
GLShaderManager Move_shaderManager;

GLfloat blockSize = 0.1f;
GLfloat Move_vVerts[] = { -blockSize, -blockSize, 0.0f,
blockSize, -blockSize, 0.0f,
blockSize, blockSize, 0.0f,
-blockSize, blockSize, 0.0f };

void Move_SetupRC(){
	//�O����Ļ��ɫ
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	//��ʼ��shader
	Move_shaderManager.InitializeStockShaders();

	//����һ����Ⱦ�ڵ�
	squreBatch.Begin(GL_TRIANGLE_FAN,4);
	squreBatch.CopyVertexData3f(Move_vVerts); //���ƶ�������
	squreBatch.End();
}

void Move_SpecialKeys(int key, int x, int y){
	GLfloat stepSize = 0.025f;
	GLfloat blockX = Move_vVerts[0];
	GLfloat blockY = Move_vVerts[7];
	if (key == GLUT_KEY_DOWN)
		blockY -= stepSize;
	if (key == GLUT_KEY_UP)
		blockY += stepSize;
	if (key == GLUT_KEY_LEFT)
		blockX -= stepSize;
	if (key == GLUT_KEY_RIGHT)
		blockX += stepSize;


	GLfloat doubleSize = 2 * blockSize;
	//Խ����
	if (blockX < -1.0f) blockX = -1.0f;
	if (blockX > 1.0 - doubleSize){
		blockX = 1.0 - doubleSize;
	}
	if (blockY > 1.0f) blockY = 1.0f;
	if (blockY < -1.0f + doubleSize){
		blockY = -1.0f + doubleSize;
	}

	
	//��һ����
	Move_vVerts[0] = blockX;
	Move_vVerts[1] = blockY - doubleSize;

	//�ڶ�����
	Move_vVerts[3] = blockX + doubleSize;
	Move_vVerts[4] = blockY - doubleSize;

	//��������

	Move_vVerts[6] = Move_vVerts[3];
	Move_vVerts[7] = blockY;
	//���ĸ���

	Move_vVerts[9] = Move_vVerts[0];
	Move_vVerts[10] = Move_vVerts[7];


	squreBatch.CopyVertexData3f(Move_vVerts); //�����µĶ�������
	


}

void Move_RenderScene()//ˢ�´��ڵĕr��͕�����renderScene����
{
	printf("ssss");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 0.5f };
	Move_shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	squreBatch.Draw();

	// Flush drawing commands
	glutSwapBuffers(); //����̨�������Ķ������Ƶ�ǰ̨
	glutPostRedisplay(); //�ֶ�ˢ�´��ڣ����������ֻ�д��ڷ�����С�����ָ�����󻯣����ǣ�����������ʾ�ȱ仯�Żᷢ������
}

void Move_ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}


int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Move Block with Arrow Keys");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutReshapeFunc(Move_ChangeSize);
	glutDisplayFunc(Move_RenderScene);
	glutSpecialFunc(Move_SpecialKeys);

	Move_SetupRC();

	glutMainLoop();
	return 0;
}