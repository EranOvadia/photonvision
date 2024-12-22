/* Copyright 2019-2021 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef LIBCORAL_CORAL_POSE_ESTIMATION_POSENET_DECODER_OP_H_
#define LIBCORAL_CORAL_POSE_ESTIMATION_POSENET_DECODER_OP_H_

#include "tensorflow/lite/context.h"

namespace coral {

static const char kPosenetDecoderOp[] = "PosenetDecoderOp";

TfLiteRegistration* RegisterPosenetDecoderOp();

}  // namespace coral

#endif  // LIBCORAL_CORAL_POSE_ESTIMATION_POSENET_DECODER_OP_H_
