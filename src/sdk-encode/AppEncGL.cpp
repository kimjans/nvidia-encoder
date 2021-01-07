/*
* Copyright 2017-2018 NVIDIA Corporation.  All rights reserved.
*
* Please refer to the NVIDIA end user license agreement (EULA) associated
* with this source code for terms and conditions that govern your use of
* this software. Any use, reproduction, disclosure, or distribution of
* this software and related documentation outside the terms of the EULA
* is strictly prohibited.
*
*/
#include <napi.h>
#include <iostream>
#include <memory>
#include <stdint.h>
#include "EncoderProxy.h"

// simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();

// void ShowHelpAndExit(const char *szBadOption = NULL)
// {
//     bool bThrowError = false;
//     std::ostringstream oss;
//     if (szBadOption)
//     {
//         bThrowError = true;
//         oss << "Error parsing \"" << szBadOption << "\"" << std::endl;
//     }
//     oss << "Options:" << std::endl
//         << "-i           Input file path" << std::endl
//         << "-o           Output file path" << std::endl
//         << "-s           Input resolution in this form: WxH" << std::endl
//         << "-if          Input format: iyuv nv12" << std::endl
//         ;
//     oss << NvEncoderInitParam().GetHelpMessage(false, false, true);
//     if (bThrowError)
//     {
//         throw std::invalid_argument(oss.str());
//     }
//     else
//     {
//         std::cout << oss.str();
//         exit(0);
//     }
// }

// void EncodeCurrentFrame(NvEncoderGL *enc, std::ofstream *fpOut, bool lastFrame)
// {
//     //std::streamsize nRead = fpIn.read(reinterpret_cast<char*>(pHostFrame.get()), nFrameSize).gcount();

//     const NvEncInputFrame* encoderInputFrame = enc->GetNextInputFrame();
//     NV_ENC_INPUT_RESOURCE_OPENGL_TEX *pResource = (NV_ENC_INPUT_RESOURCE_OPENGL_TEX *)encoderInputFrame->inputPtr;

//     glBindTexture(GL_TEXTURE_2D, pResource->texture);
//     //glTexSubImage2D(pResource->target, 0, 0, 0, nWidth, nHeight * 3 / 2, GL_RED, GL_UNSIGNED_BYTE, pHostFrame.get());
    
//     //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, nWidth, nHeight, GL_RGBA, GL_UNSIGNED_BYTE, pHostFrame.get());

//     // unsigned char pixels[ 1 * 1 * 4 ] = { 0 };
//     // glReadPixels( 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
//     // std::cout << "r: " << static_cast< int >( pixels[ 0 ] ) << '\n';
//     // std::cout << "g: " << static_cast< int >( pixels[ 1 ] ) << '\n';
//     // std::cout << "b: " << static_cast< int >( pixels[ 2 ] ) << '\n';
//     // std::cout << "a: " << static_cast< int >( pixels[ 3 ] ) << '\n' << std::endl;

//     //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, nWidth, nHeight, 0);
//     glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, enc->GetEncodeWidth(), enc->GetEncodeHeight());
//     glBindTexture(GL_TEXTURE_2D, 0);

//     std::vector<std::vector<uint8_t>> vPacket;
//     if (lastFrame)
//     {
//         enc->EndEncode(vPacket);
//     }
//     else
//     {
//         enc->EncodeFrame(vPacket);
//     }
//     //nFrame += (int)vPacket.size();
//     for (std::vector<uint8_t> &packet : vPacket)
//     {
//         fpOut->write(reinterpret_cast<char*>(packet.data()), packet.size());
//     }

// }

// NvEncoderGL EncodeGL(int nWidth, int nHeight, NV_ENC_BUFFER_FORMAT eFormat, NvEncoderInitParam *encodeCLIOptions)
// {

//     NvEncoderGL enc(nWidth, nHeight, eFormat);

//     NV_ENC_INITIALIZE_PARAMS initializeParams = { NV_ENC_INITIALIZE_PARAMS_VER };
//     NV_ENC_CONFIG encodeConfig = { NV_ENC_CONFIG_VER };
//     initializeParams.encodeConfig = &encodeConfig;
//     enc.CreateDefaultEncoderParams(&initializeParams, encodeCLIOptions->GetEncodeGUID(),
//         encodeCLIOptions->GetPresetGUID());

//     encodeCLIOptions->SetInitParams(&initializeParams, eFormat);

//     enc.CreateEncoder(&initializeParams);

//     int nFrameSize = enc.GetFrameSize();
//     std::cout << "nFrameSize" << nFrameSize << std::endl;

//     std::unique_ptr<uint8_t[]> pHostFrame(new uint8_t[nFrameSize]);
//     //int nFrame = 0;
//     int totalFrame = 2000;

//     return enc;

    
// }

// void EndEncodeGL(NvEncoderGL *enc, std::ofstream *fpOut)
// {

//     enc->DestroyEncoder();
//     fpOut->close();
//     //fpIn.close();

//     //std::cout << "Total frames encoded: " << nFrame << std::endl;
//     //std::cout << "Saved in file " << szOutFilePath << std::endl;

// }



// /**
// *  This sample application illustrates encoding of frames stored in OpenGL
// *  textures. The application reads frames from the input file and uploads them
// *  to the textures obtained from the encoder using NvEncoder::GetNextInputFrame().
// *  The encoder subsequently maps the textures for encoder using NvEncodeAPI and
// *  submits them to NVENC hardware for encoding as part of EncodeFrame() function.
// */

// int start(int nWidth,int nHeight, char *outputPath)
// {
    
//     NV_ENC_BUFFER_FORMAT eFormat = NV_ENC_BUFFER_FORMAT_ABGR;
//     NvEncoderInitParam encodeCLIOptions = NvEncoderInitParam("");

//     try
//     {

//         std::ofstream fpOut(outputPath, std::ios::out | std::ios::binary);
//         if (!fpOut)
//         {
//             std::ostringstream err;
//             err << "Unable to open output file: " << outputPath << std::endl;
//             throw std::invalid_argument(err.str());
//         }

//         NvEncoderGL enc = EncodeGL(nWidth, nHeight, eFormat, &encodeCLIOptions);

//         std::cout << "A" << '\n';
//         int totalFrame = 2000;
//         for(int i = 0; i <= totalFrame; ++i){

//             EncodeCurrentFrame(&enc, &fpOut, i == totalFrame);

//         }
//         EndEncodeGL(&enc, &fpOut);
//     }
//     catch (const std::exception &e)
//     {
//         std::cout << e.what();
//         return 1;
//     }


//     return 0;
// }

// 자바스크립트의 String 객체를 반환하는 함수입니다.
// 파라미터는 info[n] 형태로 얻어올 수 있습니다.
Napi::Boolean CreateEncoder(const Napi::CallbackInfo& info) {
  //
  // info에는 현재 스코프 정보(env)도 들어있습니다.
  // 자바스크립트 객체를 생성하려면 반드시 이것부터 가져와야합니다.
  Napi::Env env = info.Env();

  Napi::Number width = info[0].As<Napi::Number>();
  Napi::Number height = info[1].As<Napi::Number>();
  Napi::String outputPath = info[2].As<Napi::String>();

  char outputPathChar[256] = "";
  sprintf(outputPathChar, outputPath.ToString().Utf8Value().c_str());


  //start(width.Int32Value(), height.Int32Value(), outputPathChar);

  //
  // 현재 스코프 정보(env)와 std::string을 사용하여,
  // "Hi!"라는 자바스크립트 문자열을 반환합니다.
  return Napi::Boolean::New(env, true);
}

//
// 애드온 이니셜라이져입니다.
// 자바스크립트 오브젝트(exports)에 함수를 하나씩 집어넣고,
// 다 집어넣었으면 리턴문으로 반환하면 됩니다.
Napi::Object initALL(Napi::Env env, Napi::Object exports) {
    //
    // 위의 함수를 "sayHi"라는 이름으로 집어넣습니다.
    exports.Set(Napi::String::New(env, "CreateEncoder"), Napi::Function::New(env, CreateEncoder));

    //
    // 다 집어넣었다면 반환합니다.
    return EncoderProxy::Init(env, exports);

};

//
// 애드온의 별명과, 이니셜라이져를 인자로 받습니다.
//NODE_API_MODULE(hello_world, initALL);
NODE_API_MODULE(NODE_GYP_MODULE_NAME, initALL)