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



