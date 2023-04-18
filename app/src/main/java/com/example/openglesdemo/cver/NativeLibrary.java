package com.example.openglesdemo.cver;

public class NativeLibrary
{
    static
    {
        System.loadLibrary("openglesdemo");
    }
    public static native void initSimpleTriangle(int width, int height);
    public static native void stepSimpleTriangle();
    public static native void initSimpleCube(int width, int height);
    public static native void stepSimpleCube();
    public static native void initTextureCube(int width, int height);
    public static native void stepTextureCube();
}
