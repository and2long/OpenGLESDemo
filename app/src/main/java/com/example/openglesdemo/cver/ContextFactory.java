package com.example.openglesdemo.cver;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

public class ContextFactory  implements GLSurfaceView.EGLContextFactory{

    @Override
    public EGLContext createContext(EGL10 egl10, EGLDisplay eglDisplay, EGLConfig eglConfig) {
        final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
        int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
        return egl10.eglCreateContext(eglDisplay, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
    }

    @Override
    public void destroyContext(EGL10 egl10, EGLDisplay eglDisplay, EGLContext eglContext) {
        egl10.eglDestroyContext(eglDisplay,  eglContext);
    }
}
