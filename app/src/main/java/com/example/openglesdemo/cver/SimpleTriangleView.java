package com.example.openglesdemo.cver;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.example.openglesdemo.cver.config.ConfigChooser;
import com.example.openglesdemo.cver.config.ContextFactory;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class SimpleTriangleView extends GLSurfaceView {

    public SimpleTriangleView(Context context) {
        super(context);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    public SimpleTriangleView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            NativeLibrary.stepSimpleTriangle();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            NativeLibrary.initSimpleTriangle(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }
}
