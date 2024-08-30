#include "triangle.h"
#include "glad.h"
#include "glfw3.h"






void sausage::genreate_trinagle_buffer()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), sausage::getVerticies(), GL_STATIC_DRAW);
}

float* sausage::getVerticies()
{
	float vertisies[9] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	return vertisies;
}

void sausage::draw_triangle()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
