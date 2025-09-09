#include <jni.h>
#include <string>
#include<iostream>
#include<vector>
#include"Component/StartupNullptrEngineComponent.h"
#include"Component/GetDataNullptrEngineComponent.h"
#include<android/native_window.h>
#include<android/native_window_jni.h>
using namespace std;

StartupNullptrEngine NullptrEngine = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_com_operator_1about_nullptrengine_MainActivity_StartupNullptrEngine(
        JNIEnv* env,
        jobject /* this */, jobject Surface) {

    ANativeWindow* Window = ANativeWindow_fromSurface(env, Surface);
    NullptrEngine = StartupNullptrEngine(Window);
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_operator_1about_nullptrengine_MainActivity_GetDataNullptrEngine(
        JNIEnv* env,
        jobject /* this */) {

    string Properties;

    GetDataNullptrEngine Data = GetDataNullptrEngine();
    VkPhysicalDeviceProperties PDP = Data.GetPhysicalDeviceProperties(NullptrEngine.PhysicalDevice);
    Properties += string() + PDP.deviceName;

    return env->NewStringUTF(Properties.c_str());
}