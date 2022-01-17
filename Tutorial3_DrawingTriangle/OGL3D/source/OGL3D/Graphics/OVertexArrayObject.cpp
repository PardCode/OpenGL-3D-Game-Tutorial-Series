/*MIT License

C++ OpenGL 3D Game Tutorial Series (https://github.com/PardCode/OpenGL-3D-Game-Tutorial-Series)

Copyright (c) 2021-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferId);


	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(0);

	m_vertexBufferData = data;
}

OVertexArrayObject::~OVertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 OVertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

ui32 OVertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
