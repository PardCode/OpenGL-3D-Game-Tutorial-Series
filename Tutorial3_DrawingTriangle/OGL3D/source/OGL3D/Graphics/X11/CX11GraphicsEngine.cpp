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

#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad.h>
#include <glad/glad_glx.h>
#include <stdexcept>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/X11/CX11Globals.h>

Display* GlobalDisplay;
int GlobalScreenId;
Window GlobalWindowRoot;
Visual *GlobalVisual;
Colormap GlobalColorMap;


OGraphicsEngine::OGraphicsEngine()
{

    //Setup main X11 Resources (Display, RootWindow)------------
    //------------------------------------------------------------
    GlobalDisplay = XOpenDisplay(NULL);
    assert(GlobalDisplay);

    GlobalScreenId = DefaultScreen(GlobalDisplay);
    GlobalWindowRoot = RootWindow(GlobalDisplay, GlobalScreenId);
    GlobalVisual = DefaultVisual(GlobalDisplay, GlobalScreenId);

    GlobalColorMap = XCreateColormap(GlobalDisplay, GlobalWindowRoot, GlobalVisual, AllocNone);
    //------------------------------------------------------------



    //Create X11 Dummy Window and Dummy OpenGL Context in order to initialize Glad------------
    //-----------------------------------------------------------------------------
    XSetWindowAttributes attributes;
    attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
    attributes.colormap = GlobalColorMap;

    Window window =
        XCreateWindow(GlobalDisplay, GlobalWindowRoot, 0, 0, 800, 600, 0,
                      DefaultDepth(GlobalDisplay, GlobalScreenId), InputOutput, GlobalVisual,
                      CWColormap | CWEventMask, &attributes);
    assert(window);

    if (!gladLoadGLX(GlobalDisplay, GlobalScreenId))
        throw std::runtime_error("OGraphicsEngine - gladLoadGLX failed");

    GLint visual_attributes[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER, 1,
        None
    };

    int num_fbc = 0;
    GLXFBConfig *fbc = glXChooseFBConfig(GlobalDisplay, GlobalScreenId, visual_attributes, &num_fbc);

    GLint context_attributes[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 6,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        None
    };

    GLXContext context =
        glXCreateContextAttribsARB(GlobalDisplay, fbc[0], NULL, 1, context_attributes);
    assert(context);


    glXMakeCurrent(GlobalDisplay, window, context);

    if (!gladLoadGL())
       throw std::runtime_error("OGraphicsEngine - gladLoadGL failed");

    glXDestroyContext((Display*)GlobalDisplay,(GLXContext)context);
    XDestroyWindow( (Display*)GlobalDisplay,(Window)window );

    //-----------------------------------------------------------
}


OGraphicsEngine::~OGraphicsEngine()
{
    XFreeColormap(GlobalDisplay, GlobalColorMap);
    XCloseDisplay(GlobalDisplay);
}



