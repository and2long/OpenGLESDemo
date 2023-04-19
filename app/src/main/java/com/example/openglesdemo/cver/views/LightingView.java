package com.example.openglesdemo.cver.views;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.example.openglesdemo.cver.NativeLibrary;
import com.example.openglesdemo.cver.config.ConfigChooser;
import com.example.openglesdemo.cver.config.ContextFactory;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class LightingView extends GLSurfaceView {

    public LightingView(Context context) {
        super(context);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    public LightingView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            NativeLibrary.stepLighting();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            NativeLibrary.initLighting(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }
}
