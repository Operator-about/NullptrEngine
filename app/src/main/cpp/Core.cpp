#include <jni.h>
#include <string>
#include<android/native_window.h>
#include<android/window.h>
#include<android/native_window_jni.h>
#include"Component/VkMainComponent.h"
using namespace std;

extern "C" JNIEXPORT void JNICALL
Java_com_cubevertex_nullptrengine_MainActivity_VkStartup(
        JNIEnv* env,
        jobject /* this */, jobject Surface) {



    ANativeWindow* Window = ANativeWindow_fromSurface(env, Surface);
    VkMain Main = VkMain();
    Main.VkInitialization(Window);


}