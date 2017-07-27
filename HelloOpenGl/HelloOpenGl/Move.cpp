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
	//設置屏幕颜色
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	//初始化shader
	Move_shaderManager.InitializeStockShaders();

	//设置一批渲染节点
	squreBatch.Begin(GL_TRIANGLE_FAN,4);
	squreBatch.CopyVertexData3f(Move_vVerts); //复制顶点数据
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
	//越界检测
	if (blockX < -1.0f) blockX = -1.0f;
	if (blockX > 1.0 - doubleSize){
		blockX = 1.0 - doubleSize;
	}
	if (blockY > 1.0f) blockY = 1.0f;
	if (blockY < -1.0f + doubleSize){
		blockY = -1.0f + doubleSize;
	}

	
	//第一个点
	Move_vVerts[0] = blockX;
	Move_vVerts[1] = blockY - doubleSize;

	//第二个点
	Move_vVerts[3] = blockX + doubleSize;
	Move_vVerts[4] = blockY - doubleSize;

	//第三个点

	Move_vVerts[6] = Move_vVerts[3];
	Move_vVerts[7] = blockY;
	//第四个点

	Move_vVerts[9] = Move_vVerts[0];
	Move_vVerts[10] = Move_vVerts[7];


	squreBatch.CopyVertexData3f(Move_vVerts); //复制新的定点数据
	


}

void Move_RenderScene()//刷新窗口的時候就會调用renderScene函数
{
	printf("ssss");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 0.5f };
	Move_shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	squreBatch.Draw();

	// Flush drawing commands
	glutSwapBuffers(); //将后台缓冲区的东西绘制到前台
	glutPostRedisplay(); //手动刷新窗口，正常情况下只有窗口发生最小化，恢复，最大化，覆盖，或者重新显示等变化才会发生更新
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