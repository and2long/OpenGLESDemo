package com.example.openglesdemo.cver;

public class NativeLibrary
{
    static
    {
        System.loadLibrary("openglesdemo");
    }
    public static native void init(int width, int height);
    public static native void step();
}
