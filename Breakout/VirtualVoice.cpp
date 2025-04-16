#include "VirtualVoice.h"

VirtualVoice::VirtualVoice()
{
	setIsStreaming(false);
}

void VirtualVoice::assignDataToBuffer(std::vector<float>& audioData,
	bool loop, std::function<void()> fCallback, ma_decoder* streamingDecoder)
{	
	if (streamingDecoder)
	{
		decoder = streamingDecoder;
		setIsStreaming(true);
		//ma_decoder_seek_to_pcm_frame(decoder, 0);
		channels = decoder->outputChannels;
	}
	else
	{
		buffer = audioData;
	}
	isLooping = loop;
	playHead.store(0);
	setIsActive(true);
	finishedCallback = fCallback;
}

void VirtualVoice::clearBuffer()
{
	buffer.clear();
    playHead.store(0);
    setIsActive(false);
    std::clog << "Virtual Voice -> Buffer cleared" << std::endl;
    std::clog << "Virtual Voice -> buffer size: " << buffer.size() << std::endl;
}

void VirtualVoice::processAudio(float* outputBuffer, ma_uint32 frameCount)
{
	// std::clog << "Virtual Voice -> process audio" << std::endl;
	// std::clog << "Virtual Voice -> buffer size: " << buffer.size() << std::endl;
	switch (vVTransportState)
	{
	case VVPLAY:
	{
		// --- Streaming Algorithm ---
		if (getIsStreaming() && decoder)
		{
			for (ma_uint32 i = 0; i < frameCount; ++i)
			{
				float theadPlayhead = playHead.load();
				ma_uint64 framesRead = 0;

				// a tempbuffer to pass into ma_decoder_read_pcm_frame 
				// assuming 2 channels
				float tempBuffer[2];
				ma_decoder_read_pcm_frames(decoder, tempBuffer, 1, &framesRead);

				if (framesRead != 0)
				{
					++theadPlayhead;
					playHead.store(theadPlayhead);
				}
				else if (framesRead == 0)
				{
					if (isLooping)
					{
						ma_decoder_seek_to_pcm_frame(decoder, 0);
						playHead.store(0);
					}
					else
					{
						setIsActive(false);
						finishedCallback();
						break;
					}
				}

				
			}

			return;
		}


		// --- Buffer Algorithm ---
		if (!getIsStreaming() && !decoder)
		{
		for (ma_uint32 i = 0; i < frameCount; ++i)
		{
			float threadPlayhead = playHead.load();
			if (threadPlayhead < buffer.size())
			{
				threadPlayhead++;
				//std::clog << "Virtual Voice playhead: " << playHead << std::endl;
				playHead.store(threadPlayhead);
			}
			else
			{
				if (isLooping)
				{
					threadPlayhead = 0;
					playHead.store(threadPlayhead);
				}
				else
				{
					setIsActive(false);
					std::clog << "Virtual Voice -> set Is active is false" << std::endl;
					finishedCallback();
					return;
					//break;
				}
			}
		

		}
		break;
		}
	}
	case VVPAUSE:
	{
		break;
	}
	default:
		break;
	}
	

}

void VirtualVoice::setIsStreaming(bool iS)
{
	isStreaming = iS;
}

bool VirtualVoice::getIsStreaming()
{
	return isStreaming;
}

std::vector<float> VirtualVoice::getBuffer()
{
	return buffer;
}

void VirtualVoice::setIsActive(bool iActive)
{
	isActive = iActive;
}

bool VirtualVoice::getIsActive()
{
	return isActive;
}

void VirtualVoice::captureData()
{
	std::clog << "VirtualVoice -> Empty Function" << std::endl;
}
