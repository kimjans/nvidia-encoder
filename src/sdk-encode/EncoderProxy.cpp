#include "EncoderProxy.h"

Napi::FunctionReference EncoderProxy::constructor;

Napi::Object EncoderProxy::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "EncoderProxy", {
    InstanceMethod("encodeCurrentFrame", &EncoderProxy::EncodeCurrentFrame),
    InstanceMethod("create", &EncoderProxy::Create),
    InstanceMethod("finish", &EncoderProxy::Finish),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("EncoderProxy", func);
  return exports;
}

EncoderProxy::EncoderProxy(const Napi::CallbackInfo& info) : Napi::ObjectWrap<EncoderProxy>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 3 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number nWidth = info[0].As<Napi::Number>();
  Napi::Number nHeight = info[1].As<Napi::Number>();
  Napi::String outputPath = info[2].As<Napi::String>();
  Napi::String encoderInitParam = info[3].As<Napi::String>();

  char outputPathChar[256] = "";
  char encoderInitChar[256] = "";
  sprintf(outputPathChar, outputPath.ToString().Utf8Value().c_str());
  sprintf(encoderInitChar, encoderInitParam.ToString().Utf8Value().c_str());

  this->encClass_ = new EncoderClass(nWidth.Int32Value(), nHeight.Int32Value(), outputPathChar, encoderInitChar);
}
Napi::Value EncoderProxy::Finish(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  double num = this->encClass_->finish();
  return Napi::Number::New(env, num);
}

Napi::Value EncoderProxy::EncodeCurrentFrame(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);


  Napi::Boolean lastFrame = info[0].As<Napi::Boolean>();
  
  double num = this->encClass_->encodeCurrentFrame( lastFrame.Value() ==0 ? false : true );
  return Napi::Number::New(env, num);
}
Napi::Value EncoderProxy::Create(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  double num = this->encClass_->create();
  return Napi::Number::New(env, num);
}


// Napi::Value EncoderProxy::Add(const Napi::CallbackInfo& info) {
//   Napi::Env env = info.Env();
//   Napi::HandleScope scope(env);

//   if (  info.Length() != 1 || !info[0].IsNumber()) {
//     Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
//   }

//   Napi::Number toAdd = info[0].As<Napi::Number>();
//   double answer = this->encClass_->add(toAdd.DoubleValue());

//   return Napi::Number::New(info.Env(), answer);
// }