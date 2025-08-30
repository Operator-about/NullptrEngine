#include <jni.h>
#include <string>
#include<iostream>
#include"Component/StartupNullptrEngineComponent.h"
using namespace std;

extern "C" JNIEXPORT void JNICALL
Java_com_operator_1about_nullptrengine_MainActivity_StartupNullptrEngine(
        JNIEnv* env,
        jobject /* this */) {

    StartupNullptrEngine NullptrEngine = StartupNullptrEngine();
}