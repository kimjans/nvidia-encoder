#include <napi.h>
#include "EncoderClass.h"

class EncoderProxy : public Napi::ObjectWrap<EncoderProxy> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS
  EncoderProxy(const Napi::CallbackInfo& info); //Constructor to initialise

 private:
  static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
  Napi::Value EncodeCurrentFrame(const Napi::CallbackInfo& info); //wrapped getValue function 
  Napi::Value Create(const Napi::CallbackInfo& info);
  Napi::Value Finish(const Napi::CallbackInfo& info);
  EncoderClass *encClass_; //internal instance of actualclass used to perform actual operations.
};
