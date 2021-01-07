#include "./Utils/Logger.h"
#include "NvEncoder/NvEncoderGL.h"
#include "./Utils/NvEncoderCLIOptions.h"
#include "./Utils/NvCodecUtils.h"
#include <iostream>
#include <memory>
#include <stdint.h>

class EncoderClass {
 public:
  EncoderClass(int nWidth, int nHeight, char *outputPath); //constructor
  bool create(); //getter for the value
  bool encodeCurrentFrame(bool lastFrame); //getter for the value
  bool finish(); //getter for the value
 private:
  int m_width;
  int m_height;

  char outputPath[256];
  NvEncoderGL *m_enc;
  std::ofstream *m_fpOut;
};