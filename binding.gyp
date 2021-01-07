{
  "targets": [
    {
      "cflags!": [ "-fno-exceptions", "-Wall","-Wno-unused-parameter", "-Wextra" ],
      "cflags_cc": [ "-std=c++11" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/local/cuda-11/include",
        "./src/sdk-encode/NvCodec",
        "./src/sdk-encode/NvCodec/NvEncoder",
        "./src/sdk-encode/NvCodec/NvDecoder"
      ],
      "link_settings": {
        "libraries": ["-lX11","-lGL", "-lglut","-lGLEW"]
      },
      "target_name": "AppEncGL",
      "sources": [ "./video-src/sdk-encode/AppEncGL.cpp",
                   "./video-src/sdk-encode/NvCodec/NvEncoder/NvEncoderGL.cpp",
                  "./video-src/sdk-encode/NvCodec/NvEncoder/NvEncoder.cpp",
                  "./video-src/sdk-encode/EncoderClass.cpp",
                  "./video-src/sdk-encode/EncoderProxy.cpp"]
    }
  ]
}