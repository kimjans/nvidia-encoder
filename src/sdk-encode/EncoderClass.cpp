#include "EncoderClass.h"
simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();
EncoderClass::EncoderClass(int nWidth, int nHeight, char *outputPath){
    this->m_width = nWidth;
    this->m_height = nHeight;
    std::copy(outputPath, outputPath+256, this->outputPath);

}

bool EncoderClass::create()
{

    try
    {

        this->m_fpOut = new std::ofstream(this->outputPath, std::ios::out | std::ios::binary);
        if (!this->m_fpOut)
        {
            std::ostringstream err;
            err << "Unable to open output file: " << this->outputPath << std::endl;
            throw std::invalid_argument(err.str());
        }
        NvEncoderInitParam encodeCLIOptions = NvEncoderInitParam("-preset HP -fps 24 -profile baseline -bitrate 2M");

        this->m_enc = new NvEncoderGL(this->m_width, this->m_height, NV_ENC_BUFFER_FORMAT_ABGR);
    
        NV_ENC_INITIALIZE_PARAMS initializeParams = { NV_ENC_INITIALIZE_PARAMS_VER };
        NV_ENC_CONFIG encodeConfig = { NV_ENC_CONFIG_VER };
        initializeParams.encodeConfig = &encodeConfig;
        this->m_enc->CreateDefaultEncoderParams(&initializeParams, encodeCLIOptions.GetEncodeGUID(),
            encodeCLIOptions.GetPresetGUID());

        encodeCLIOptions.SetInitParams(&initializeParams, NV_ENC_BUFFER_FORMAT_ABGR);

        this->m_enc->CreateEncoder(&initializeParams);

        int nFrameSize = this->m_enc->GetFrameSize();
        
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
        return 1;
    }


  return true;
}

bool EncoderClass::encodeCurrentFrame(bool lastFrame)
{
    const NvEncInputFrame* encoderInputFrame = this->m_enc->GetNextInputFrame();
    NV_ENC_INPUT_RESOURCE_OPENGL_TEX *pResource = (NV_ENC_INPUT_RESOURCE_OPENGL_TEX *)encoderInputFrame->inputPtr;

    glBindTexture(GL_TEXTURE_2D, pResource->texture);

    unsigned char pixels[ 1 * 1 * 4 ] = { 0 };
    glReadPixels( 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    // std::cout << "r: " << static_cast< int >( pixels[ 0 ] ) << '\n';
    // std::cout << "g: " << static_cast< int >( pixels[ 1 ] ) << '\n';
    // std::cout << "b: " << static_cast< int >( pixels[ 2 ] ) << '\n';
    // std::cout << "a: " << static_cast< int >( pixels[ 3 ] ) << '\n' << std::endl;

    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, this->m_enc->GetEncodeWidth(), this->m_enc->GetEncodeHeight());
    glBindTexture(GL_TEXTURE_2D, 0);

    std::vector<std::vector<uint8_t>> vPacket;
   if (lastFrame)
    {
        this->m_enc->EndEncode(vPacket);
    }
    else
    {
        this->m_enc->EncodeFrame(vPacket);
    }
    //nFrame += (int)vPacket.size();
    for (std::vector<uint8_t> &packet : vPacket)
    {
        this->m_fpOut->write(reinterpret_cast<char*>(packet.data()), packet.size());
    }
  return true;
}

bool EncoderClass::finish()
{
    this->m_enc->DestroyEncoder();
    this->m_fpOut->close();
  return true;
}
