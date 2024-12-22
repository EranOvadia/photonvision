#include <jni.h>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "coral/learn/backprop/basic_engine.h"
#include "coral/pipeline/pipelined_model_runner.h"

static JClass detectionResultClass;

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
  JNIEnv *env;
  if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }

  detectionResultClass =
      JClass(env, "org/photonvision/coral/CoralJNI$CoralResult");

  if (!detectionResultClass) {
    std::printf("Couldn't find class!");
    return JNI_ERR;
  }

  return JNI_VERSION_1_6;
}

static jobject MakeJObject(JNIEnv *env, const detect_result_t &result) {
  jmethodID constructor =
      env->GetMethodID(detectionResultClass, "<init>", "(IIIIFI)V");

  // Actually call the constructor
  return env->NewObject(detectionResultClass, constructor, result.x1,
                        result.y1, result.x2, result.y2,
                        result.confidence, result.label);
}


/*
 * Class:     org_photonvision_coral_CoralJNI
 * Method:    create
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL
Java_org_photonvision_coral_CoralJNI_create
  (JNIEnv *env, jclass, jstring javaString, jint numClasses, jint modelVer, jint coreNum)
{
  const char *nativeString = env->GetStringUTFChars(javaString, 0);
  std::printf("Creating for %s\n", nativeString);

//   YoloModel *ret;
//   if (static_cast<ModelVersion>(modelVer) == ModelVersion::YOLO_V5) {
//     printf("Starting with version 5\n");
//     ret = new YoloV5Model(nativeString, numClasses, coreNum);
//   } else {
//     printf("Starting with version 8\n");
//     ret = new YoloV8Model(nativeString, numClasses, coreNum);
//   }
  
  static std::unique_ptr<edgetpu::BasicEngine> engine = std::make_unique<edgetpu::BasicEngine>(nativeString);

  env->ReleaseStringUTFChars(javaString, nativeString);
  return reinterpret_cast<jlong>(engine);
}

/*
 * Class:     org_photonvision_coral_CoralJNI
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_org_photonvision_coral_CoralJNI_destroy
  (JNIEnv *env, jclass, jlong ptr)
{
  delete reinterpret_cast<YoloModel *>(ptr);
}



/*
 * Class:     org_photonvision_coral_CoralJNI
 * Method:    detect
 * Signature: (JJDDI)[Ljava/lang/Object;
 */
JNIEXPORT jobjectArray JNICALL
Java_org_photonvision_coral_CoralJNI_detect
  (JNIEnv *env, jclass, jlong detector_, jlong input_cvmat_ptr,
   jdouble nms_thresh, jdouble box_thresh)
{
  CoralDriver *coral = reinterpret_cast<CoralDriver *>(detector_);
  cv::Mat *input_img = reinterpret_cast<cv::Mat *>(input_cvmat_ptr);
  
  // Run inference
  std::vector<uint8_t> input_data(*input_img.data, *input_img.data + *input_img.total());
  auto results = *coral->RunInference(input_data);

  if (results.count < 1) {
    return nullptr;
  }

  jobjectArray jarr = env->NewObjectArray(results.count, detectionResultClass, nullptr);

  for (size_t i = 0; i < results.count; i++) {
    jobject obj = MakeJObject(env, results.results[i]);
    env->SetObjectArrayElement(jarr, i, obj);
  }

  return jarr;
}
}
