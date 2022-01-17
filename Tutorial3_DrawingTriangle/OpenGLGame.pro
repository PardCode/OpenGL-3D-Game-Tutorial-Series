#MIT License

#C++ OpenGL 3D Game Tutorial Series (https://github.com/PardCode/OpenGL-3D-Game-Tutorial-Series)

#Copyright (c) 2021-2022, PardCode

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += OGL3D/include
INCLUDEPATH += OGL3D/source
INCLUDEPATH += OGL3D/vendor/glad/include




unix:!macx {
    SOURCES += \
        OGL3D/source/OGL3D/Game/X11/CX11Game.cpp \
        OGL3D/source/OGL3D/Graphics/X11/CX11GraphicsEngine.cpp \
        OGL3D/source/OGL3D/Window/CX11Window.cpp\
        OGL3D/vendor/glad/src/glad_glx.c

    HEADERS+=\
            OGL3D/vendor/glad/include/glad/glad_glx.h\
            OGL3D/source/OGL3D/Graphics/X11/CX11Globals.h

}
win32: {
    SOURCES += \
    OGL3D/source/OGL3D/Game/Win32/CWin32Game.cpp \
    OGL3D/source/OGL3D/Graphics/Win32/CWin32GraphicsEngine.cpp \
    OGL3D/source/OGL3D/Window/CWin32Window.cpp\
    OGL3D/vendor/glad/src/glad_wgl.c

    HEADERS+=\
        OGL3D/vendor/glad/include/glad/glad_wgl.h
}
macx: {
    SOURCES += \
        OGL3D/source/OGL3D/Game/Cocoa/CCocoaGame.mm \
        OGL3D/source/OGL3D/Graphics/Cocoa/CCocoaGraphicsEngine.mm \
        OGL3D/source/OGL3D/Window/CCocoaWindow.mm\
}


SOURCES += \
    Game/main.cpp \
    OGL3D/source/OGL3D/Game/OGame.cpp \
    OGL3D/source/OGL3D/Graphics/OGraphicsEngine.cpp \
    OGL3D/source/OGL3D/Graphics/OVertexArrayObject.cpp \
    OGL3D/vendor/glad/src/glad.c

HEADERS += \
    OGL3D/include/OGL3D/Game/OGame.h \
    OGL3D/include/OGL3D/Graphics/OGraphicsEngine.h \
    OGL3D/include/OGL3D/Graphics/OVertexArrayObject.h \
    OGL3D/include/OGL3D/Math/OVec4.h \
    OGL3D/include/OGL3D/Math/ORect.h \
    OGL3D/include/OGL3D/OPrerequisites.h \
    OGL3D/include/OGL3D/Window/OWindow.h \
    OGL3D/vendor/glad/include/KHR/khrplatform.h \
    OGL3D/vendor/glad/include/glad/glad.h





macx {
         LIBS += -framework Cocoa -framework QuartzCore
         LIBS += -framework AppKit -framework OpenGL -framework Quartz
}

unix:!macx {
         LIBS += -lX11 -lGL -ldl
}
