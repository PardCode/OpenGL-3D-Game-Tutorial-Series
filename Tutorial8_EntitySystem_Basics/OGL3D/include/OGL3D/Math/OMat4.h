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
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec3.h>

class OMat4
{
public:
	OMat4()
	{
		setIdentity();
	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(mat));
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setScale(const OVec3& scale)
	{
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setTranslation(const OVec3& translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}


	void setRotationX(f32 x)
	{
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(f32 y)
	{
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(f32 z)
	{
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}
	void operator *=(const OMat4& matrix)
	{
		OMat4 out;
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] +
					mat[i][3] * matrix.mat[3][j];
			}
		}
		*this = out;
	}


	void setOrthoLH(f32 width, f32 height, f32 nearPlane, f32 farPlane)
	{
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

public:
	f32 mat[4][4] = {};
};