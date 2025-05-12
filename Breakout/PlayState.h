#pragma once
#include "BaseState.h"
class PlayState :
    public BaseState
{
    void Update(float dt) override;
    void Render() override;
};

