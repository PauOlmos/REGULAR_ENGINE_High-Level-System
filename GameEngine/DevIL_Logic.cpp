#include "DevIL_Logic.h"

Application* DevIL_Logic::App = nullptr;
GLubyte DevIL_Logic::checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4] = {};
GLuint DevIL_Logic::textureID;

void DevIL_Logic::Init()
{
	//Initialize checker image
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE0);

	//Generate and bind texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//How texture behaves outside 0,1 range (S->x, T->y)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Texture behaviour after resize (MIN->smaller , MAG->bigger)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Create Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void DevIL_Logic::CleanUp()
{
	
}
