#include "EventManager.h"

EventManager::EventManager() /*: playbackDevice(realVoicePool)*/
{
}

EventManager::~EventManager()
{
	delete tree;
	delete paddle;
	delete brick;
	delete pause;
	delete gameOver;
	delete levelComplete;

	//ma_decoder_uninit(&trapDoor.decoder);
	ma_device_uninit(&playbackDevice.device);
}

void EventManager::init()
{
	std::cout << "EventManager -> initialising \"eventManager\" object" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;

	// Game song
	tree->Add(gameMusic);
	smilyDay_Asset.loadFile("assets/audio/SmileyDayToYa.wav");
	gameMusic->assignAssetToTrack(smilyDay_Asset.getAudioData());
	gameMusic->setVolume(0.1f);
	gameMusic->setLoop(true);

	// Ball colliding with Paddle
	tree->Add(paddle);
	paddle_Asset.loadFile("assets/audio/PaddleBall.wav");
	paddle->assignAssetToTrack(paddle_Asset.getAudioData());
	paddle->setLoop(false);

	// Ball colliding with Bounds (same asset as paddle sound but pitched differently)
	tree->Add(bounds);
	paddle_Asset.loadFile("assets/audio/PaddleBall.wav");
	bounds->assignAssetToTrack(paddle_Asset.getAudioData());
	bounds->setLoop(false);
	bounds->setPitch(0.5);

	// Ball colliding with Brick
	tree->Add(brick);
	brick_Asset.loadFile("assets/audio/PaddleBrick.wav");
	brick->assignAssetToTrack(brick_Asset.getAudioData());
	brick->setLoop(false);

	// When entering and exiting the Pause menu
	tree->Add(pause);
	pause_Asset.loadFile("assets/audio/PauseMenu.wav");
	pause->assignAssetToTrack(pause_Asset.getAudioData());
	pause->setLoop(false);

	// When Game Over
	tree->Add(gameOver);
	gameOver_Asset.loadFile("assets/audio/GameOver.wav");
	gameOver->assignAssetToTrack(gameOver_Asset.getAudioData());
	gameOver->setLoop(false);

	// When winning a level
	tree->Add(levelComplete);
	levelComplete_Asset.loadFile("assets/audio/LevelComplete.wav");
	levelComplete->assignAssetToTrack(levelComplete_Asset.getAudioData());
	levelComplete->setLoop(false);

	// Padddle Shrink Debuf
	tree->Add(paddleShrink);
	paddleShrink_Asset.loadFile("assets/audio/paddleShrink.wav");
	paddleShrink->assignAssetToTrack(paddleShrink_Asset.getAudioData());

	// Paddle Expand Buff
	tree->Add(paddleExpand);
	paddleExpand_Asset.loadFile("assets/audio/paddleExpand.wav");
	paddleExpand->assignAssetToTrack(paddleExpand_Asset.getAudioData());

	// Ball speed for slow and fast ball buffs
	tree->Add(ballSpeed);
	ballSpeed_Asset.loadFile("assets/audio/SlowBall.wav");
	ballSpeed->assignAssetToTrack(ballSpeed_Asset.getAudioData());

	// Fireball buff
	tree->Add(fireBall);
	fireBall_Asset.loadFile("assets/audio/FireBall.wav");
	fireBall->assignAssetToTrack(fireBall_Asset.getAudioData());

}

void EventManager::update(float dt)
{
	checkIfRealVoiceAvailable();
	//std::clog << "Update -> delta time test" << std::endl;
}

void EventManager::TreeStructure(Component* component)
{
	std::cout << "EventManager -> Result: " << component->Operation() << std::endl;
}

void EventManager::TreeStructure(Component* component1, Component* component2)
{
	if (component1->IsComposite())
	{
		component1->Add(component2);

	}
	std::cout << "EventManager -> Result: " << component1->Operation() << std::endl;
}

void EventManager::checkIfRealVoiceAvailable()
{
	
	// Virtual to Real Voice switch algorithm
	if (!realVoicePool->getAllVoicesActive())
	{
		for (auto& virtualVoice : virtualVoicePool->getVirtualVoicePool())
		{
			if (realVoicePool->getAllVoicesActive())
				break;
			if (virtualVoice && virtualVoice->getIsActive())
			{
				//std::clog << "EventManager -> Virtual Voice buffer size: " << virtualVoice->getBuffer().size() << std::endl;
				// - Find inactive real voice and call capture on the the virtual voice 
				//   in the virtual voice pool
				for (auto& realVoice : realVoicePool->getRealVoicePool())
				{
					realVoicePool->checkIfVoiceActive();
					if (realVoicePool->getAllVoicesActive())
						break;
					if (realVoice && !realVoice->getIsActive())
					{
						//std::clog << "EventManager -> Voice Switch algorithm -> Found Active Real Voice" << std::endl;
						//std::clog << "EventManager -> Virtual Voice buffer size: " << virtualVoice->getBuffer().size() << std::endl;
						realVoice->captureData(virtualVoice);
						realVoicePool->checkIfVoiceActive();
						//realVoicePool->setAllVoicesActive(true);
						//realVoicePool->getRealVoice();
						//virtualVoice->setIsActive(false);
						std::clog << "EventManager -> PROMOTED a Virtual Voice to Real Voice" << std::endl;
						break;
					}
					
					// check for real voices in real voice pool
				}
				// - Set the real voice to active


				//realVoicePool->getRealVoice()->transferDataFrom(voice);
				//virtualVoice->setIsActive(false);
				//notifyVoiceSwitch(realVoicePool->getRealVoice());
			}
		}
	}
}

