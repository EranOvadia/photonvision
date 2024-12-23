#include <jni.h>

#ifndef CORAL_JAVA_SRC_MAIN_NATIVE_CPP_CORAL_JNI_H_
#define CORAL_JAVA_SRC_MAIN_NATIVE_CPP_CORAL_JNI_H_
#ifdef __cplusplus

extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_org_photonvision_coral_CoralJNI_create(JNIEnv *, jobject, jstring);
JNIEXPORT jlong JNICALL Java_org_photonvision_coral_CoralJNI_destory(JNIEnv *, jobject, jlong);

JNIEXPORT jobjectArray JNICALL Java_org_photonvision_coral_CoralJNI_detect(JNIEnv *, jobject, jlong, jlong, jdouble, jdouble);

JNIEXPORT jboolean JNICALL Java_org_photonvision_coral_CoralJNI_checkIfTPUConnected(JNIEnv *, jobject);

#ifdef __cplusplus
} // extern "C"
#endif
#endif