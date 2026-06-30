// FUNC_NAME: AudioSourceComponent::updateStreamState
void __thiscall AudioSourceComponent::updateStreamState()
{
    int *piVar1;
    char cVar2;
    int *piVar3;
    uint uVar4;
    int iVar5;
    uint uVar6;
    uint auStack64[14]; // 56 bytes
    uint uStack44; // uStack_2c
    uint64 uStack36; // uStack_24, 8 bytes
    uint uStack28; // uStack_1c, 4 bytes
    uint64 uStack24; // uStack_18, 8 bytes
    uint64 uStack16; // uStack_10, 8 bytes
    uint64 uStack8; // uStack_8, 8 bytes

    // +0x14c: stream cooldown timer
    this->streamCooldown = 0;

    // +0x108: previously created stream handle
    if (this->previousStreamHandle != 0) {
        releaseStreamHandle(this->previousStreamHandle);
        this->previousStreamHandle = 0;
    }

    piVar1 = &this->callbackObject; // +0x10c
    if ((this->callbackObject != 0) &&
        ((**(code **)*this->callbackObject)(1), *piVar1 != 0)) {
        deleteObject(piVar1);
        *piVar1 = 0;
    }

    uVar6 = *(uint *)(*(int *)(this->audioSourceConfigPtr + 0x114)); // +0x100 points to config, +0x114 is a parameter

    // +0xa8: flags (bit13 = skipTransformUpdate)
    if ((this->flags >> 0xd & 1) == 0) {
        piVar3 = (int *)getAudioManagerSingleton(); // returns a pointer to global manager's node list
        piVar1 = &this->managerNode; // +0x118

        if (piVar1 != piVar3) {
            iVar5 = *piVar3;
            if (*piVar1 != iVar5) {
                if (*piVar1 != 0) {
                    deleteObject(piVar1);
                }
                *piVar1 = iVar5;
                if (iVar5 != 0) {
                    this->managerNodePrev = *(uint *)(iVar5 + 4); // +0x11c
                    *(int **)(iVar5 + 4) = piVar1;
                }
            }
        }

        iVar5 = piVar3[2]; // offset 8 into manager node
        this->sampleRate = iVar5; // +0x120

        if ((*piVar1 != 0) && (iVar5 != 0)) {
            setAudioSourceParameter(*(uint *)(this->audioHandle), // +0xb8
                                    *(uint *)(*(int *)(this->entityPtr + 0x5f0)), // +0x58 -> entity, +0x5f0 is some property
                                    0x40102, 0x2000000, uVar6);

            // Save current world transform (position + rotation)
            uStack24 = *(uint64 *)(this->worldPosition); // +0x134 (8 bytes, probably float3 x,y)
            uStack16 = *(uint64 *)(this->worldPosition + 8); // +0x13c
            uStack8 = *(uint64 *)(this->worldPosition + 0x10); // +0x144

            // Check flag bit0 at +0xab
            if ((this->extraFlags & 1) != 0) {
                uStack44 = uStack44 | 2;
            }

            computeTransformMatrix(&this->localTransform, auStack64, DAT_00d92d14); // +0x60 is localTransform (8 bytes? +0x68 extra)

            uVar4 = beginAudioUpdate();
            applyAudioTransform(uVar4);

            // If the extra flag was set and the computed flags don't have bit0, restore original transform
            if (((this->extraFlags & 1) != 0) && (~(byte)uStack44 & 1) != 0)) {
                *(uint64 *)(this->localTransform) = uStack36; // uStack_24
                *(uint *)(this->localTransform + 8) = uStack28; // uStack_1c
            }

            endAudioUpdate();
        }
    }

    // Check if we have all required resources ready for stream creation
    if (((this->managerNode != 0) && (this->sampleRate != 0)) &&
        (this->streamBuffer != 0) && (*(int *)(this + 0x12c) != 0)) {
        iVar5 = createOrBindStream(&this->managerNode,
                                   this->streamBuffer,
                                   0, 10,
                                   this->streamFlags, // +0x104
                                   uVar6,
                                   0xc000);
        this->previousStreamHandle = iVar5; // +0x108

        if ((iVar5 != 0) && (cVar2 = isAudioSystemReady(0), cVar2 != '\0')) {
            if (this->callbackObject != 0) {
                deleteObject(&this->callbackObject);
                this->callbackObject = 0;
            }

            cVar2 = isAudioStreamingEnabled();
            if (cVar2 != '\0') {
                iVar5 = allocateMemory(0x18);
                if (iVar5 == 0) {
                    uVar6 = 0;
                } else {
                    uVar6 = createAudioCallback();
                }
                constructStreamCallback(uVar6); // initializes callback object

                if ((this->callbackObject != 0) &&
                    (cVar2 = attachCallbackToStream(this->previousStreamHandle, this->callbackObject),
                     cVar2 != '\0')) {
                    startStream();
                }
            }

            releaseStreamHandle(this->previousStreamHandle);
            this->previousStreamHandle = 0;
        }
    }
}