// FUNC_NAME: CharacterAnimationController::updateAnimations
bool CharacterAnimationController::updateAnimations(float deltaTime)
{
    // param_1 is this pointer
    // +0x24: pointer to animation config/settings
    int* config = *(int**)(this + 0x24);
    if ((*(uint*)(config + 0x10c) & 0x10000000) != 0) {
        deltaTime = 0.0f; // if config flag 0x10000000 set, freeze time
    }

    int* rendererContext = **(int***)(__readfsdword(0x2c) + 0x2c); // global renderer/context
    int* skeleton = *(int**)(this + 0x10);
    if ((*(byte*)(skeleton + *(int*)(rendererContext + 8)) & 0x10) != 0) {
        *(uint*)(this + 0x2c) |= 0x800; // set flag 0x800
    }

    float elapsedTime = *(float*)(this + 0x44) + deltaTime;
    *(float*)(this + 0x44) = elapsedTime;

    // +0xc8? Actually config + 200 = config + 0xc8 (offset? Let's use hex)
    float maxAnimationTime = *(float*)(config + 0xc8); // +200 decimal = 0xC8
    uint flags = *(uint*)(this + 0x2c);
    if (((maxAnimationTime > 0.0f) && ((flags & 4) == 0)) && ((flags & 0x800) == 0) && (maxAnimationTime <= elapsedTime)) {
        flags |= 0x800;
        *(uint*)(this + 0x2c) = flags;
        *(float*)(this + 0x44) = maxAnimationTime; // clamp to max
        char ready = FUN_005098a0(); // check if animation can complete/transition
        if (ready) {
            uint* skeletonPtr = (uint*)(*(int*)(rendererContext + 8) + skeleton);
            *skeletonPtr |= 1; // set bit 0 (dirty flag)
        }
    }

    config = *(int**)(this + 0x24);
    bool done = false;
    if ((*(float*)(config + 0x11c) <= 0.0f) || (*(float*)(this + 0x44) >= *(float*)(config + 0x11c))) {
        done = true; // animation duration exceeded? +0x11c might be maxDuration
    }

    // Handle animation blend decay (offset +0x94)
    if (*(float*)(this + 0x94) != 0.0f) {
        float decayRate = *(float*)(config + 0x180);
        if (decayRate < *PTR_FUN_00e4462c) { // something global
            float decay = *(float*)(this + 0x94) - (deltaTime / decayRate) * *(float*)(config + 0x17c);
            *(float*)(this + 0x94) = decay;
            bool decayDone;
            if (*(float*)(config + 0x17c) <= 0.0f) {
                decayDone = (decay < 0.0f);
            } else {
                decayDone = (decay > 0.0f);
            }
            if (!decayDone) {
                *(float*)(this + 0x94) = 0.0f;
            }
        }
        *(float*)(this + 0x90) = *(float*)(this + 0x94) * deltaTime + *(float*)(this + 0x90);
    }

    ushort currentSlot = *(ushort*)(this + 0x74); // +0x74: start slot
    ushort slotCount = *(ushort*)(this + 0x76); // +0x76: number of slots to process
    uint slotIndex = (uint)currentSlot;
    uint processedSlots = 0;
    int savedSlotPtr0 = 0;
    int savedSlotPtr1 = 0;
    uint savedSlotIdx = 0;
    uint slotBase = (uint)slotCount;
    uint slotRemaining = (uint)currentSlot;

    if (slotRemaining != 0) {
        do {
            slotRemaining--;
            int* slotEntry = (int*)(this + 0xb0 + ((int)slotBase >> 3) * 8); // array of 8-byte entries at +0xB0
            uint slotOffset = slotBase & 7;
            int slotDataPtr = slotEntry[0];
            float* slotTime = (float*)(slotDataPtr + slotOffset * 4 + *(int*)(rendererContext + 8));
            int slotData = *(int*)(rendererContext + 8) + slotDataPtr + slotOffset * 0x50; // +0x50 per slot? Actually offset * 0x50

            if ((*(byte*)(slotData + 0x54) & 2) == 0) { // If slot not disabled
                config = *(int**)(this + 0x24);
                float speed = *(float*)(config + 0xcc);
                if ((*(byte*)(config + 0x10c) & 2) != 0) {
                    // Compute speed modification
                    speed = ((float)(int)(*(float*)(config + 0x178) * *(float*)(config + 0xcc)) + *DAT_00e2b1a4) * *(float*)(*(int*)(this + 0x24) + 0x174);
                    if ((*(uint*)(*(int*)(this + 0x24) + 0x108) & 0x20000000) != 0) {
                        speed += (*(float*)(slotData + 0x58) - *DAT_00e2b1a4) * *(float*)(*(int*)(this + 0x28) + 0xc);
                    }
                    if (speed <= 0.0f) {
                        speed = 0.0f;
                    }
                }

                if (((speed >= 0.0f) && (speed < *slotTime + deltaTime)) || done) {
                    // Slot completed
                    processedSlots++;
                    FUN_0050c9a0(this, slotEntry); // start next animation on this slot?
                    byte* flagsPtr = (byte*)(slotDataPtr + slotOffset * 0x50 + 0x54 + *(int*)(rendererContext + 8));
                    *flagsPtr |= 1; // set flag 1
                    char animType = *(char*)(this + 0x5b);
                    if (((animType != 0) && (animType != 3)) && (animType != 5)) {
                        FUN_0050fdc0(slotEntry); // stop old animation?
                    }
                    *slotTime = speed; // reset slot time to speed? or set to speed?
                    savedSlotPtr0 = slotEntry[0];
                    savedSlotPtr1 = slotEntry[1];
                    savedSlotIdx = slotOffset;
                } else {
                    *slotTime = *slotTime + deltaTime;
                    animType = *(char*)(this + 0x5b);
                    if (((animType != 0) && (animType != 3)) && ((animType != 5 && ((*(byte*)(slotDataPtr + slotOffset * 0x50 + 0x54 + *(int*)(rendererContext + 8)) & 1) == 0)))) {
                        FUN_00510110(this, slotEntry, slotOffset, deltaTime); // update slot with delta
                    }
                }
            } else {
                // Disabled slot, clear flag
                *(byte*)(slotData + 0x54) &= 0xfd; // clear bit 1
            }

            slotBase++;
            if ((int)*(short*)(this + 0x5c) <= (int)slotBase) {
                slotBase -= (int)*(short*)(this + 0x5c); // wrap around slot count
            }
        } while (slotRemaining != 0);

        if (processedSlots != 0) {
            uint newSlotCount = (uint)(ushort)slotCount + processedSlots;
            if (*(short*)(this + 0x5c) <= (int)newSlotCount) {
                newSlotCount -= *(short*)(this + 0x5c);
            }
            *(int*)(this + 0x54) += processedSlots; // total processed slots
            ushort newCurrentSlot = currentSlot - (ushort)processedSlots;
            // Check for events
            if (((*(byte*)(*(int*)(rendererContext + 8) + *(int*)(this + 0x10)) & 8) != 0) &&
                (config = *(int**)(this + 0x24), (*(uint*)(config + 0x10c) & 0x100) != 0)) {
                float blendWeight = *(float*)(*(int*)(rendererContext + 8) + savedSlotIdx * 4 + savedSlotPtr0);
                if (blendWeight < 0.0f) {
                    blendWeight = 0.0f;
                }
                uint eventFlags = 0;
                float unknown = *DAT_00e2b1a4;
                uint totalProcessed = *(uint*)(this + 0x54);
                if ((*(uint*)(config + 0x10c) & 0xc00) == 0) {
                    FUN_0050a9d0(this, &savedSlotPtr0, local_40); // get animation info
                    if ((*(uint*)(config + 0x10c) & 0x400) == 0) {
                        eventFlags |= 2;
                    }
                    if ((*(uint*)(config + 0x10c) & 0x800) == 0) {
                        eventFlags |= 4;
                    }
                }
                FUN_0051ab70(*(uint*)(this + 4), local_50); // get world transform
                *(uint*)(this + 0x54) = ((int)totalProcessed < 0) - 1 & totalProcessed; // wrap total
            }
        }
    }

    *(ushort*)(this + 0x76) = (ushort)newSlotCount; // update slot count
    *(ushort*)(this + 0x74) = newCurrentSlot; // update current slot

    // Check for some global rendering flag
    if ((*(uint*)(*(int*)(this + 0x24) + 0x10c) & 0x80000000) != 0) {
        FUN_0050d5e0();
        FUN_00533fb0();
    }

    uint flags2 = *(uint*)(*(int*)(this + 0x24) + 0x10c);
    if (((flags2 & 0x18) != 0) && (*(int*)(this + 0x70) != 0)) {
        FUN_004eb6a0(*(int*)(this + 0x10) + 0x80 + *(int*)(rendererContext + 8), flags2 >> 4 & 0xffffff01);
        int* skeletonPtr2 = *(int**)(rendererContext + 8) + *(int*)(this + 0x10);
        FUN_0056b230(local_50, skeletonPtr2 + 0x10, skeletonPtr2 + 0x50, 3);
        *(int*)(skeletonPtr2 + 0x5c) = 0;
        *(int*)(skeletonPtr2 + 0x6c) = 0;
        *(int*)(skeletonPtr2 + 0x7c) = 0;
    }

    *(float*)(this + 0x3c) -= deltaTime; // decrement some timer

    if ((deltaTime != 0.0f) && ((*(uint*)(*(int*)(this + 4) + 0xc) & 0x20000) == 0) && (!done)) {
        int steps = 2;
        float remainingTime = deltaTime;
        if (deltaTime <= *DAT_00e449ac) {
            steps = 1;
        }
        do {
            steps--;
            if ((*(float*)(this + 0x3c) > 0.0f) || (FUN_0050d660(*(ushort*)(this + 0x74), 0, &slotTime), remainingTime <= 0.0f)) {
                break;
            }
        } while (steps > 0);
    }

    bool result = false;
    if ((*(short*)(this + 0x74) == 0) &&
        (((flags2 = *(uint*)(this + 0x2c), (flags2 & 0x10) != 0) || ((*(uint*)(*(int*)(this + 4) + 0xc) & 0x20000) != 0))) {
        short maxSlots = *(short*)(*(int*)(this + 0x24) + 0x118);
        if (maxSlots < 0) {
            if (((*(byte*)(*(int*)(this + 0x10) + *(int*)(rendererContext + 8)) & 2) != 0) && (!done))
                goto LAB_0050def7;
            result = true;
            *(uint*)(this + 0x2c) |= 8;
        } else {
            result = (int)maxSlots <= *(int*)(this + 0x50);
            if (!result) goto LAB_0050def7;
            *(uint*)(this + 0x2c) |= 8;
        }
    } else {
LAB_0050def7:
        *(uint*)(this + 0x2c) &= 0xfffffff7; // clear bit 3
    }

    uint flags3 = *(uint*)(this + 0x2c);
    if (((flags3 & 4) != 0) && ((flags3 & 0x10) != 0)) {
        *(uint*)(this + 0x2c) = flags3 | 0x800;
    }

    if ((*(uint*)(this + 0x2c) & 8) != 0) {
        float maxTime = *(float*)(*(int*)(this + 0x24) + 0xc8);
        if ((maxTime > 0.0f) && (*(float*)(this + 0x44) >= maxTime)) {
            uint* skeletonPtr3 = (uint*)(*(int*)(this + 0x10) + *(int*)(rendererContext + 8));
            *skeletonPtr3 |= 1;
        }
    }

LAB_0050df45:
    if ((((*(uint*)(*(int*)(this + 0x24) + 0x108) & 0x2000) != 0) &&
        (*(int*)(*(int*)(this + 4) + 0xb0) == 4)) && (*(float*)(this + 0x98) < *DAT_00e2b1a4)) {
        int* somePtr = *(int**)(*(int*)(this + 4) + 0xc0);
        float blendProgress = *(float*)(this + 0x9c) * deltaTime + *(float*)(this + 0x98);
        *(float*)(this + 0x98) = blendProgress;
        if (*DAT_00e2b1a4 < blendProgress) {
            *(float*)(this + 0x98) = *DAT_00e2b1a4;
        }
        short frame = (short)(int)(((float)(*(short*)(somePtr + 2) - 1) + *DAT_00e2e210) * *(float*)(this + 0x98));
        *(short*)(this + 0x5e) = frame;
        if (*(short*)(somePtr + 2) - 1 < (int)frame) {
            *(short*)(this + 0x5e) = *(short*)(somePtr + 2) - 1;
        }
    }

    // Copy skeleton transform to local storage
    int* skeletonBase = *(int**)(this + 0x10) + 0x80 + *(int*)(rendererContext + 8);
    uint val1 = *(uint*)(skeletonBase + 4);
    uint val2 = *(uint*)(skeletonBase + 8);
    uint val3 = *(uint*)(skeletonBase + 12);
    *(uint*)(this + 0x80) = *(uint*)skeletonBase;
    *(uint*)(this + 0x84) = val1;
    *(uint*)(this + 0x88) = val2;
    *(uint*)(this + 0x8c) = val3;
    *(float*)(this + 0x30) = deltaTime;

    return result;
}