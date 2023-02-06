package com.example.openglesdemo.cver;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class TutorialView extends GLSurfaceView {

    public TutorialView(Context context) {
        super(context);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    public TutorialView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser());
        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            NativeLibrary.step();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            NativeLibrary.init(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }
}
