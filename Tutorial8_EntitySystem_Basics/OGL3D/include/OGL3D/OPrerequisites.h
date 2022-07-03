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

#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class OVertexArrayObject;
class OUniformBuffer;
class OShaderProgram;

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;




typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct OVertexAttribute
{
	ui32 numElements = 0;
};

struct OVertexBufferDesc
{
	void* verticesList = nullptr;
	ui32 vertexSize = 0;
	ui32 listSize = 0;

	OVertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};

struct OIndexBufferDesc
{
	void* indicesList = nullptr;
	ui32 listSize = 0;
};

struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct OUniformBufferDesc
{
	ui32 size = 0;
};

enum class OTriangleType
{
	TriangleList = 0,
	TriangleStrip
};

enum class OCullType
{
	BackFace = 0,
	FrontFace,
	Both
};

enum class OWindingOrder
{
	ClockWise = 0,
	CounterClockWise
};

enum class OShaderType
{
	VertexShader = 0,
	FragmentShader
};


#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;


#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;