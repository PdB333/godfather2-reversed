// FUNC_NAME: Animation::updateBlendWeights
void __thiscall Animation::updateBlendWeights(Animation* this, const BlendAdjustInfo* adjustInfo)
{
    // Subtract adjustment deltas from blend weights (9 floats at offsets 0x160-0x180)
    this->blendWeight[0] -= adjustInfo->deltaWeight[0];   // +0x160
    this->blendWeight[1] -= adjustInfo->deltaWeight[1];   // +0x164
    this->blendWeight[2] -= adjustInfo->deltaWeight[2];   // +0x168
    this->blendWeight[3] -= adjustInfo->deltaWeight[3];   // +0x16c
    this->blendWeight[4] -= adjustInfo->deltaWeight[4];   // +0x170
    this->blendWeight[5] -= adjustInfo->deltaWeight[5];   // +0x174
    this->blendWeight[6] -= adjustInfo->deltaWeight[6];   // +0x178
    this->blendWeight[7] -= adjustInfo->deltaWeight[7];   // +0x17c
    this->blendWeight[8] -= adjustInfo->deltaWeight[8];   // +0x180

    int* skeletonPtr = this->skeletonData; // +0x1d0
    float blendTime = this->blendTime; // +0x188

    // divisor is skeleton's weight multiplier if present, else 0
    float divisor = 0.0f;
    if (skeletonPtr) {
        divisor = *(float*)(skeletonPtr + 0x58) * blendTime;
    } else {
        adjustInfo = (const BlendAdjustInfo*)0; // workaround for later cast (likely misinterpretation)
    }

    int animPhase = *(int*)(this + 0x13c); // e.g. animation phase or frame count
    float phaseFloat = (float)animPhase;
    if (animPhase < 0) {
        phaseFloat += g_largeFloat; // DAT_00e44578 - correction for negative values
    }

    // Update blend time: divide by duration divisor from adjustInfo
    float newBlendTime = blendTime / adjustInfo->durationDivisor; // +0xd
    this->blendTime = newBlendTime; // +0x188

    if (skeletonPtr) {
        divisor = *(float*)(skeletonPtr + 0x58) * newBlendTime;
    }

    // Compute velocity-like effect value
    float effectValue = phaseFloat * (float)divisor - phaseFloat * (float)adjustInfo->skeletonWeightMul;

    if (this->effectEnabled) { // +0x230
        FUN_00892490(effectValue, 6); // apply positive effect (e.g. force direction 6)
    }

    // Update a time/phase field at +0x104, clamped between two global constants
    float timeField = this->animTime; // +0x104
    timeField += effectValue;
    float lowerBound = g_blendTimeMin; // DAT_00d7bcac
    float upperBound = g_blendTimeMax; // DAT_00d7bca8
    if (lowerBound < timeField) {
        lowerBound = timeField;
        if (upperBound <= timeField) {
            lowerBound = upperBound;
        }
    }
    this->animTime = lowerBound; // +0x104

    // Process adjustment based on time scale
    FUN_008be720(g_timeScale / adjustInfo->timeDivisor); // DAT_00d5780c / param_2[0xc]

    // Get node list from animation ID (adjustInfo->animID)
    int* nodeList = FUN_0084aea0(adjustInfo->animID); // *adjustInfo (first int)
    if (nodeList) {
        uint nodeCount = nodeList[2]; // +0x08 number of nodes
        for (uint i = 0; i < nodeCount; i++) {
            void* node = FUN_0084a3c0(i); // get node by index
            if (node) {
                FUN_006b3220(); // update/process node
            }
        }
    }

    // Compute total weight from all nodes
    int totalWeight = FUN_0084a5b0();
    if (this->effectEnabled) {
        FUN_00892490((float)-totalWeight, 0); // apply negative effect (force direction 0)
    }

    // Update anim time again (negative totalWeight)
    float newTime = this->animTime + (float)-totalWeight;
    if (newTime <= lowerBound) {
        // remain lower bound
    } else {
        lowerBound = upperBound;
        if (upperBound >= newTime) {
            newTime = lowerBound;
        }
    }
    this->animTime = newTime;

    // Check if there's an animation to remove (adjustInfo->removeAnimID)
    if (adjustInfo->removeAnimID) { // param_2[0x13]
        uint currentCount = this->activeAnimCount; // +0x128
        int* animArray = this->activeAnims; // +0x124
        uint idx = 0;
        while (idx < currentCount) {
            if (animArray[idx] == adjustInfo->removeAnimID) {
                if ((int)idx >= 0) {
                    if (idx != currentCount - 1) {
                        animArray[idx] = animArray[currentCount - 1]; // move last to current position
                    }
                    this->activeAnimCount--;
                    FUN_008c0d10(adjustInfo, 0); // clear/cleanup the adjusted animation
                }
                break;
            }
            idx++;
            animArray = animArray + 1;
        }
    }

    // Fire an event from stored callback at +0x224
    EventCallback callback = this->animEventCallback; // +0x224
    EventData eventData;
    eventData.value = 0;
    eventData.extra = 0;
    FUN_00408a00(&callback, 0); // invoke callback with event type 0
}