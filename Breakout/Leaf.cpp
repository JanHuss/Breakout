#include "Leaf.h"

std::string Leaf::Operation() const
{
    return "Track";
}

// Never used a parameter to be passed as a default value and this is the 
// time to use it ^^ 
void Leaf::assignAssetToTrack(std::vector<float> asset, 
    ma_decoder* streamDecoder)
{
    audioData = asset;

    // set the parameter to the decoder which will then 
    // be used in `assignTrackToRealVoice()` function
    decoder = streamDecoder;

    std::cout << "Leaf -> assigning Asset to Track" << std::endl;
    std::cout << "Leaf -> audio data's current size: " << getAudioData().size() << std::endl;
}

void Leaf::assignTrackToRealVoice()
{
    realVoice = realVoicePool->getRealVoice();

    if (realVoice)
    {
        setIsPlaying(true);
        setPitch(pitch);
        std::cout << "Leaf -> Current Pitch: " << pitch << std::endl;
        setVolume(volume);
        std::cout << "Leaf -> Current Volume: " << volume << std::endl;
        setPanning(leftPan, rightPan);
        std::cout << "Leaf -> Current Left Panning: " << leftPan << " and Right Panning: " << rightPan <<  std::endl;
        std::cout << "Leaf -> assigning Track to \"Real Voice\"" << std::endl;
        realVoice->assignDataToBuffer(audioData, getLoop(), [this](){
           realVoice = nullptr; }, decoder);
    }
}

void Leaf::assignTrackToVirtualVoice()
{
    virtualVoice = virtualVoicePool->getVirtualVoice();

    if (virtualVoice)
    {
        setIsPlaying(true);
        std::cout << "Leaf -> assigning Track to \"Virtual Voice\"" << std::endl;
        virtualVoice->assignDataToBuffer(audioData, getLoop(), [this](){
           realVoice = nullptr; });
        // give the virtual voice a reference of the track it is directing to
       
    }
}

void Leaf::removeTrackFromRealVoice()
{
   if(realVoice)
    {
        setIsPlaying(false);
        std::cout << "Leaf -> Removing \"Real Voice\" from Track" << std::endl;
        realVoice->clearBuffer();
        realVoice = nullptr;
    }
}

void Leaf::removeTrackFromVirtualVoice()
{
    if (virtualVoice)
    {
        setIsPlaying(false);
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
        if(!realVoice)
            assignTrackToRealVoice();
        realVoice->rVTransportState = RVPLAY;
        std::cout << "Leaf-> is playing real voice" << std::endl;
    }
    else
    {
        voiceType = VIRTUAL;
        if(!realVoice)
            assignTrackToVirtualVoice();
        virtualVoice->vVTransportState = VVPLAY;
        std::cout << "Leaf -> No \"Real Voice\" Available. Assign asset to \"Virtual Voice\" " << std::endl;
    }
}

void Leaf::pause()
{
    std::clog << "Leaf -> Is pausing" << std::endl;
    switch (voiceType)
    {
    case REAL:
        // add enmum to pause state here
        realVoice->rVTransportState = RVPAUSE; 
        std::cout << "Leaf-> is pausing real voice" << std::endl;
        break;
    case VIRTUAL:
        // add enmum to pause state here
        virtualVoice->vVTransportState = VVPAUSE;
        std::cout << "Leaf-> is pausing virtual voice" << std::endl;
        break;
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
        break;
    case VIRTUAL:
        removeTrackFromVirtualVoice();
        break;
    default:
        break;
    }

    
}

void Leaf::setVolume(float vol)
{
    std::clog << "Leaf -> setting volume to: \"" << vol << "\"" << std::endl;
    volume = vol;
    if (realVoice)
        realVoice->adjustVolume(vol);
}

void Leaf::setPanning(float lp, float rp)
{
    std::clog << "Leaf -> setting panning left: \"" << lp << "\" and panning right: \"" << rp << "\"" << std::endl;
    leftPan = lp;
    rightPan = rp;
    if (realVoice)
        realVoice->adjustPan(lp, rp);
}

void Leaf::setPitch(float semitones)
{
    std::clog << "Leaf -> setting pitch to: \"" << semitones << "\"" << std::endl;
    pitch = semitones;
    if (realVoice)
        realVoice->adjustPitch(semitones);
}

void Leaf::setCurrentVoice(VoiceBase* voice)
{
    currentVoice = voice;
}

VoiceBase* Leaf::getCurrentVoice()
{
    return currentVoice;
}

void Leaf::setIsPlaying(bool isPl)
{
    isPlaying = isPl;
}

bool Leaf::getIsPlaying()
{
    return isPlaying;
}
