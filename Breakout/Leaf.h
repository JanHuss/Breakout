// Leaf is designated for "Tracks" that can make use of the transport 
// controls.
// Currently, Tracks are Children only and can only hold one audio asset.

#pragma once

// Headers
#include "Component.h"
#include "RealVoicePool.h"
#include "VirtualVoicePool.h"

// Libraries
#include <string>
#include <vector>
#include <iostream>

class Leaf :
    public Component
{
public:
    std::string Operation() const override; 

    void assignAssetToTrack(std::vector<float> asset);

    void assignTrackToRealVoice();
    void assignTrackToVirtualVoice();

    void removeTrackFromRealVoice();
    void removeTrackFromVirtualVoice();

    std::vector<float> getAudioData();

    // high-level interface
    void play() override;
    void pause() override;
    void stop() override;

    void setVolume(float vol) override;
    void setPanning(float lp, float rp) override;
    void setPitch(float semitones);

    void setCurrentVoice(VoiceBase* voice);
    VoiceBase* getCurrentVoice();

    void setIsPlaying(bool isPl) override;
    bool getIsPlaying() override;
    
private:
    std::vector<float> audioData;
    enum VOICETYPE {REAL, VIRTUAL};
    VOICETYPE voiceType;
    float volume = 1.0f;
    float pitch = 0.0f;
    float leftPan = 0.5f;
    float rightPan = 0.5f;
    bool isLooping;
    bool isPlaying = false;

    // think this can be removed
    VoiceBase* currentVoice = nullptr;

    RealVoice* realVoice = nullptr;
    VirtualVoice* virtualVoice = nullptr;

};

