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
#import <Cocoa/Cocoa.h>
#include <glad/glad.h>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
    //Create Dummy Cocoa Window and Dummy OpenGL Context in order to initialize Glad------------
    //-----------------------------------------------------------------------------
    NSUInteger windowStyle = 0;

    NSRect screenRect = [[NSScreen mainScreen] frame];
    NSRect viewRect = NSMakeRect(0, 0, 1, 1);
    NSRect windowRect = NSMakeRect(NSMidX(screenRect) - NSMidX(viewRect),
                                   NSMidY(screenRect) - NSMidY(viewRect),
                                   viewRect.size.width,
                                   viewRect.size.height);

    NSWindow * window = [[NSWindow alloc] initWithContentRect:windowRect
                                                              styleMask:windowStyle
                                                              backing:NSBackingStoreBuffered
                                                              defer:NO];

    assert(window);


    //Unfortunately, the last version of OpenGL supported on macOS is the 4.1.
    NSOpenGLPixelFormatAttribute windowedAttrs[] =
    {
        NSOpenGLPFAMultisample,
        NSOpenGLPFASampleBuffers, 0,
        NSOpenGLPFASamples, 0,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        0
    };

    NSOpenGLPixelFormat* pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:windowedAttrs];
    assert(pf);

    NSOpenGLContext*  _context = [[NSOpenGLContext alloc] initWithFormat: pf shareContext: NULL];
    assert(_context);


     [_context makeCurrentContext];

    if (!gladLoadGL())
        throw std::runtime_error("OCocoaGraphicsEngine - gladLoadGL failed");

    [_context release];
    [pf release];
    [window release];
}


OGraphicsEngine::~OGraphicsEngine()
{
}

