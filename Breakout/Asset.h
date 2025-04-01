// An asset is capable of loading an audio file using the "miniaud.io" 
// "ma_decoder" type. This class will receive an overhaul, making use
// of a "ResourceManager" class.

#pragma once

// Headers
#include "miniaudio.h"

// Libraries
#include <string>
#include <iostream>
#include <vector>

enum FORMAT {PCM, STREAM};

class Asset
{
public:
    Asset();
    ~Asset();
    
    static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
    int initDevice();
    int loadFile(const std::string filePath, FORMAT form);
    void currentFileLoadedOnDevice(std::string filePath);
    void unload(std::string filepath);

    int pcmFormat(std::string filePath);
    int streamFormat(std::string filePath);

    // setter
    void setAudioData(std::vector<float> aD);
    

    // getter
    std::vector<float> getAudioData();
    ma_uint64 getTotalFrameCount();
    bool getIsStreaming();

    // public variables
    ma_decoder decoder;
    ma_decoder_config decoderConfig;
    ma_audio_buffer_config bufferConfig;
    FORMAT dataFormat;
    
private:
    int channels;
    int sampleRate;
    float volume;
    bool isLoaded = false;
    bool isStreaming = false;
    ma_uint64 totalFrames;


    std::vector<float> audioData ={};    
    
};
