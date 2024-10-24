﻿#pragma once
#include "../IParticleForceGenerator.h"

class FrictionForceGenerator : public IParticleForceGenerator {
public:
    FrictionForceGenerator(float friction);
    void UpdateForce(std::shared_ptr<IObject>& object) override;

private:
    float friction_;
};
