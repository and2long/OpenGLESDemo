package com.example.openglesdemo.cver

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class DetailActivity : AppCompatActivity() {
    private var gLView: GLSurfaceView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val param = intent.getStringExtra("param")
        gLView = buildView(param)
        setContentView(gLView)
    }

    private fun buildView(param: String?): GLSurfaceView? {
        return when (param) {
            PARAM_SIMPLE_CUBE -> SimpleCubeView(this)
            PARAM_SIMPLE_TRIANGLE -> SimpleTriangleView(this)
            else -> null
        }
    }

    override fun onPause() {
        super.onPause()
        gLView?.onPause()
    }

    override fun onResume() {
        super.onResume()
        gLView?.onResume()
    }
}