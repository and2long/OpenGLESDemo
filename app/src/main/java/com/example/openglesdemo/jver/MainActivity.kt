package com.example.openglesdemo.jver

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle

class MainActivity : AppCompatActivity() {

    private lateinit var gLView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        gLView = MyGLSurfaceView(this)
        setContentView(gLView)
    }

    override fun onResume() {
        super.onResume()
        gLView.onResume()
    }

    override fun onPause() {
        super.onPause()
        gLView.onPause()
    }

}