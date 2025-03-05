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
	gameMusic->setVolume(0.75f);
	gameMusic->setLoop(true);

	// Ball colliding with Paddle
	tree->Add(paddle);
	paddle_Asset.loadFile("assets/audio/PaddleBall.wav");
	paddle->assignAssetToTrack(paddle_Asset.getAudioData());
	paddle->setLoop(false);

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


	// initialising the Engine's hierarchy. Making use of the 
	// composite pattern
	//tree->Add(bigWave_Event);
	//bigWave_Event->Add(bigWave); // add a Track to an Event
	//bigWave_Asset.loadFile("assets/audio/BigWave.wav"); // Load an Audio File
	//trapDoor->setVolume(0.5f);
	//bigWave->assignAssetToTrack(bigWave_Asset.getAudioData()); 
	//bigWave->setLoop(false);
	//
	//tree->Add(trapDoor_Event);
	//trapDoor_Event->Add(trapDoor);
	//trapDoor_Asset.loadFile("assets/audio/TrapDoor.wav");
	//trapDoor->setVolume(0.5f);
	//trapDoor->assignAssetToTrack(trapDoor_Asset.getAudioData()); 
	//trapDoor->setLoop(false);


	//tree->Add(janVoice_Event);
	//janVoice_Event->Add(janVoice_Track);
	//janVoice_Asset.loadFile("assets/audio/voiceJan.wav");
	//janVoice_Track->assignAssetToTrack(janVoice_Asset.getAudioData());
	//janVoice_Track->setLoop(false);
	//
	//tree->Add(thisIsMyVoice_Event);
	//thisIsMyVoice_Event->Add(thisIsMyVoice_Track);
	//thisIsMyVoice_Asset.loadFile("assets/audio/thisIsMyVoice.wav");
	//thisIsMyVoice_Track->assignAssetToTrack(thisIsMyVoice_Asset.getAudioData());
	//thisIsMyVoice_Track->setLoop(false);


	//TreeStructure(tree);

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

