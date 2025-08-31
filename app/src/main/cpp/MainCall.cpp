#include <jni.h>
#include <string>
#include<iostream>
#include"Component/StartupNullptrEngineComponent.h"
#include<android/native_window.h>
#include<android/native_window_jni.h>
using namespace std;


extern "C" JNIEXPORT void JNICALL
Java_com_operator_1about_nullptrengine_MainActivity_StartupNullptrEngine(
        JNIEnv* env,
        jobject /* this */, jobject Surface) {

    ANativeWindow* Window = ANativeWindow_fromSurface(env, Surface);
    StartupNullptrEngine NullptrEngine = StartupNullptrEngine(Window);
}