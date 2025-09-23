#include<jni.h>
#include<string>
#include<iostream>
#include<vector>
#include"Component/StartupNullptrEngineComponent.h"
#include"Component/GetDataNullptrEngineComponent.h"
#include"Component/ShutdownNullptrEngineComponent.h"
#include"Component/MemoryManagementNullptrEngineComponent.h"
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

    VkBuffer Buffer = {};
    CreateObjectNullptrEngine Object = CreateObjectNullptrEngine();
    Object.CreateBuffer(NullptrEngine.Device, Buffer, 1024*1024*8, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
    MemoryManagementNullptrEngine MemoryManagement = MemoryManagementNullptrEngine();
    VkMemoryRequirements MemBufferReq = {};
    MemoryManagement.GetBufferMemoryRequirements(NullptrEngine.Device, Buffer, MemBufferReq);
    Properties = to_string(static_cast<int>(MemBufferReq.size));

    if(Properties == "")
    {
        Properties = "NULL_VALUE_FOR_PROPERTIES";
    }
    return env->NewStringUTF(Properties.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_operator_1about_nullptrengine_MainActivity_ShutdownNullptrEngine(
        JNIEnv* env,
        jobject /* this */) {

    ShutdownNullptrEngine Shutdown = ShutdownNullptrEngine(NullptrEngine.Instance, NullptrEngine.Device);
}