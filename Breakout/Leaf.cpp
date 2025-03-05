#include "Leaf.h"

std::string Leaf::Operation() const
{
    return "Track";
}

void Leaf::assignAssetToTrack(std::vector<float> asset)
{
    audioData = asset;
    std::cout << "Leaf -> assigning Asset to Track" << std::endl;
    std::cout << "Leaf -> audio data's current size: " << getAudioData().size() << std::endl;
}

void Leaf::assignTrackToRealVoice()
{
    realVoice = realVoicePool->getRealVoice();
    if (realVoice)
    {
        std::cout << "Leaf -> assigning Track to \"Real Voice\"" << std::endl;
        realVoice->assignDataToBuffer(audioData, getLoop());
    }
}

void Leaf::assignTrackToVirtualVoice()
{
    virtualVoice = virtualVoicePool->getVirtualVoice();
    if (virtualVoice)
    {
        std::cout << "Leaf -> assigning Track to \"Virtual Voice\"" << std::endl;
        virtualVoice->assignDataToBuffer(audioData, getLoop());
        // give the virtual voice a reference of the track it is directing to
       
    }
}

void Leaf::removeTrackFromRealVoice()
{
   if(realVoice)
    {
        std::cout << "Leaf -> Removing \"Real Voice\" from Track" << std::endl;
        realVoice->clearBuffer();
        realVoice = nullptr;
    }
}

void Leaf::removeTrackFromVirtualVoice()
{
    if (virtualVoice)
    {
        std::cout << "Leaf -> Removing \"Virtual Voice\" from Track" << std::endl;
        virtualVoice->clearBuffer();
        virtualVoice = nullptr;
    }
}

std::vector<float> Leaf::getAudioData()
{
    //std::cout << "Leaf -> getting Audio Data" << std::endl;
    return audioData;
}

void Leaf::play()
{
    if (!realVoicePool->getAllVoicesActive())
    {
        voiceType = REAL;
        assignTrackToRealVoice();
        isPlaying = true;
        std::cout << "Leaf-> is playing real voice" << std::endl;
    }
    else
    {
        voiceType = VIRTUAL;
        isPlaying = true;
        assignTrackToVirtualVoice(); // think I need to pass track reference in here as a parameter
        std::cout << "Leaf -> No \"Real Voice\" Available. Assign asset to \"Virtual Voice\" " << std::endl;
    }
}

void Leaf::stop()
{
    // remove track from Voice
    std::cout << "Leaf -> Is stopping" << std::endl;
    switch (voiceType)
    {
    case REAL:
        removeTrackFromRealVoice();
        isPlaying = false;
        break;
    case VIRTUAL:
        removeTrackFromVirtualVoice();
        isPlaying = false;
        break;
    default:
        break;
    }

    
}

void Leaf::setVolume(float vol)
{
    volume = vol;
    adjustVolume();
}

void Leaf::adjustVolume()
{
    for (auto& sample : audioData)
        sample *= volume;
}

void Leaf::setCurrentVoice(VoiceBase* voice)
{
    currentVoice = voice;
}

VoiceBase* Leaf::getCurrentVoice()
{
    return currentVoice;
}