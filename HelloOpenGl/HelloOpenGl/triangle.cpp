#include <GLTools.h>
#include <GLShaderManager.h>
#ifdef __APPLE__

#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>


#endif
#define GLEW_STATIC
GLBatch triangleBathc;
GLBatch squareBatch;
GLShaderManager shaderManager;
void ChangeSize(int w, int h)
{
	printf("w=%d\n",w);
	printf("w=%d\n", h);
	glViewport(100,100,w,h);
}
GLfloat vVerts[] = {
	-0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f
};

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

	shaderManager.InitializeStockShaders();

	triangleBathc.Begin(GL_TRIANGLES,3);
	triangleBathc.CopyVertexData3f(vVerts);
	triangleBathc.End();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
	triangleBathc.Draw();
	glutSwapBuffers();
}
GLfloat vVerts_1[] = {
	-0.5f, 0.0f, 0.0f,
0.5f, 0.0f, 0.0f,
0.0f, 0.5f, 0.0f,
0.0f, -0.5f, 0.0f };
void SpecialKeys(int key, int x, int y){
	GLfloat stepSize = 0.025f;
	GLfloat blockX = vVerts_1[0];
	GLfloat blockY = vVerts_1[7];
	GLfloat blockSize = 1.0f;
	if(key == GLUT_KEY_UP){
		blockY += stepSize;
	}

	if (key == GLUT_KEY_DOWN){
		blockY -= stepSize;
	}

	vVerts_1[0] = blockX;
	vVerts_1[1] = blockX - blockSize * 2;

	vVerts_1[3] = blockX + blockSize * 2;
	vVerts_1[4] = blockY - blockSize * 2;

	vVerts_1[6] = blockX + blockSize * 2;
	vVerts_1[7] = blockY;

	vVerts_1[9] = blockX;
	vVerts_1[10] = blockY;

	triangleBathc.CopyVertexData3f(vVerts_1);
	glutPostRedisplay();


}

int Triangle_main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv); //初始化glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("Triangle");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	
	GLenum err = glewInit(); //初始化glew
	if (GLEW_OK != err){
		fprintf(stderr,"GLEW Error : %s\n",glewGetErrorString(err));
		return 1;
	}
	SetupRC();
	glutSpecialFunc(SpecialKeys);

	glutMainLoop(); //開始消息主循環
	return 0;
}