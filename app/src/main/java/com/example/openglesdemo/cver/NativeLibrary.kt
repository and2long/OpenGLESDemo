package com.example.openglesdemo.cver

object NativeLibrary {
    init {
        System.loadLibrary("openglesdemo")
    }

    external fun init()
}