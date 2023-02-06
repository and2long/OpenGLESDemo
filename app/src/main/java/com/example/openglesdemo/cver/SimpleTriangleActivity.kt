package com.example.openglesdemo.cver

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class SimpleTriangleActivity : AppCompatActivity() {
    private lateinit var gLView: TutorialView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        gLView = TutorialView(this)
        setContentView(gLView)
    }

    override fun onPause() {
        super.onPause()
        gLView.onPause()
    }

    override fun onResume() {
        super.onResume()
        gLView.onResume()
    }
}