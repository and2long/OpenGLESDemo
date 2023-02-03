package com.example.openglesdemo.cver

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.openglesdemo.R

class NativeActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        NativeLibrary.init()
    }
}