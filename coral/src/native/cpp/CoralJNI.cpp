#include <jni.h>
#include <stdio.h>      // C Standard IO Header
#include "CoralJNI.h"
#include "..\native\coral\detection\adapter.cc"

JNIEXPORT jlong JNICALL Java_org_photonvision_coral_CoralJNI_create(JNIEnv *env, jobject obj, jstring model_path)
{
    const auto model = coral::LoadModelOrDie(model_path);
    auto edgetpu_context = coral::ContainsEdgeTpuCustomOp(*model)
                            ? coral::GetEdgeTpuContextOrDie()
                            : nullptr;
    auto interpreter = coral::MakeEdgeTpuInterpreterOrDie(*model, edgetpu_context.get());
    CHECK_EQ(interpreter->AllocateTensors(), kTfLiteOk);

    return ( (jlong) interpreter);
}

JNIEXPORT jlong JNICALL Java_org_photonvision_coral_CoralJNI_destory(JNIEnv *env, jobject obj, jlong nativeCoralPointer)
{
    NativeCoral *cppNativeCoral = (NativeCoral *) nativeCoralPointer;
    delete cppNativeCoral;
}

JNIEXPORT jobjectArray JNICALL Java_org_photonvision_coral_CoralJNI_detect(JNIEnv *env, jobject obj, jlong detector_, jlong input_cvmat_ptr, jdouble nms_tresh, jdouble box_tresh){
    
}

JNIEXPORT jboolean JNICALL Java_org_photonvision_coral_CoralJNI_checkIfTPUConnected(JNIEnv *env, jobject obj) {
    
}