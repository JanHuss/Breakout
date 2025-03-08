// Initialises and manages the hierarchial structure of the engine
// The structure is making use of the Composite Design pattern.
// EventManager is considered the "Client" and handles the components.

#pragma once
// Headers
#include "Component.h"
#include "Composite.h"
#include "Leaf.h"
#include "Asset.h"
#include "RealVoicePool.h"
#include "VirtualVoicePool.h"
#include "PlaybackDevice.h"

// libraries
#include <iostream>
#include <thread>


class EventManager
{
public:
	EventManager();
	~EventManager();

	void init();
	void update(float dt);

	void TreeStructure(Component* component);
    void TreeStructure(Component* component1, Component* component2);

	void checkIfRealVoiceAvailable();


	PlaybackDevice playbackDevice;

	// Composite objects
	Component* tree = new Composite;

	Component* gameMusic = new Leaf;
	Component* paddle = new Leaf;
	Component* bounds = new Leaf;
	Component* brick = new Leaf;
	Component* pause = new Leaf;
	Component* gameOver = new Leaf;
	Component* levelComplete = new Leaf;
	
private:

	// Assets
	Asset smilyDay_Asset;
	Asset paddle_Asset;
	Asset brick_Asset;
	Asset pause_Asset;
	Asset gameOver_Asset;
	Asset levelComplete_Asset;

	// Object Pool Setup
	RealVoicePool* realVoicePool = RealVoicePool::getInstance();
	VirtualVoicePool* virtualVoicePool = VirtualVoicePool::getInstance();

	
};

