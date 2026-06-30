// FUNC_NAME: SoundInstance3D::updatePosition
void __fastcall SoundInstance3D::updatePosition()
{
    int* pSoundHandle = reinterpret_cast<int*>(mSoundHandle); // +0x84
    int sourceIndex = mSourceIndex; // +0x8c
    uint absIndex = (sourceIndex < 0) ? -1 & sourceIndex : sourceIndex; // absolute value
    
    // Check if sound handle is valid and play state
    if (*pSoundHandle == 0)
    {
        if (mIsPlaying) // +0x88
            goto SKIP_STOP;
    }
    else if (!mIsPlaying)
    {
        stopSound(); // FUN_005e7b60
        *pSoundHandle = 0;
        goto SKIP_STOP;
    }
SKIP_STOP:
    if (gAudioManager == 0) // DAT_0122339c
        return;
    
    int iVar6 = sourceIndex;
    uint validationResult = validateIndex(iVar6); // FUN_00424c90
    bool bValid = validationResult < gAudioManager->sourceCount; // +0x154
    
    if (*pSoundHandle == 0)
    {
        if ((iVar6 >= 0) && bValid)
        {
            acquireSoundHandle(); // FUN_005e7370
            setSoundInitialPosition(*pSoundHandle, initialPosition); // FUN_005e7a00, DAT_0110ac04
        }
        if (*pSoundHandle == 0)
            return;
    }
    
    if (!bValid)
        return;
    
    // Determine target object based on target type
    SymbolTableEntry* pEntry = nullptr;
    int targetObject = 0;
    if (mTargetType == 0 || mTargetType == 0x48)
    {
        if (gComponentList != 0)
        {
            pEntry = gComponentList->entries[absIndex]; // assuming array of pointers
            if (pEntry != 0)
            {
                targetObject = pEntry->getTarget(); // vt+0xC
            }
        }
    }
    else if (mTargetType != 0)
    {
        targetObject = mTargetType - 0x48;
    }
    
    Vector3 listenerDir; // 12 bytes
    getListenerDirection(&listenerDir, absIndex); // FUN_00425060
    
    Vector3 newPos; // 12 bytes stored as undefined8 + float
    switch (mBehaviorType)
    {
        default: // 0
            getCurrentSoundPosition(*pSoundHandle, &newPos); // FUN_005e7a40
            break;
        case 1:
        {
            if (targetObject == 0 || !(*(byte*)(targetObject + 0x40) & 1))
            {
                getListenerPosition(&newPos, absIndex); // FUN_00424fb0
            }
            else
            {
                newPos.x = *(float*)(targetObject + 0x100);
                newPos.y = *(float*)(targetObject + 0x104);
                newPos.z = *(float*)(targetObject + 0x108);
            }
            break;
        }
        case 2:
        {
            getListenerPosition(&newPos, absIndex); // via auStack_14
            break;
        }
        case 3: // fall through to 4 with bBlendToTarget = false
        case 4:
        {
            bool bBlendToTarget = (mBehaviorType == 4);
            Vector3 listenerPos;
            getListenerPosition(&listenerPos, absIndex); // FUN_00424fb0
            if (bBlendToTarget)
            {
                if (targetObject != 0 && (*(byte*)(targetObject + 0x40) & 1))
                {
                    Vector3 targetPos;
                    targetPos.x = *(float*)(targetObject + 0x100);
                    targetPos.y = *(float*)(targetObject + 0x104);
                    targetPos.z = *(float*)(targetObject + 0x108);
                    setBlendMode(1); // FUN_005e7b20
                    setInterpolatedPosition(&newPos, &targetPos); // FUN_005e7690
                    return;
                }
                // else fall through to LAB_0047e00f
                goto LAB_0047e00f;
            }
            else
            {
                // case 3: fall through to LAB_0047e00f
LAB_0047e00f:
                if (targetObject != 0 && (*(byte*)(targetObject + 0x40) & 1))
                {
                    Vector3 entityPos;
                    entityPos.x = *(float*)(targetObject + 0x100);
                    entityPos.y = *(float*)(targetObject + 0x104);
                    entityPos.z = *(float*)(targetObject + 0x108);
                    
                    if (mInterpMode == 1)
                    {
                        Vector3 diff;
                        diff.x = listenerPos.x - entityPos.x;
                        diff.y = listenerPos.y - entityPos.y;
                        diff.z = listenerPos.z - entityPos.z;
                        vectorNormalize(&diff); // FUN_0043a210
                        newPos.x = diff.x * mBlendFactor + entityPos.x;
                        newPos.y = diff.y * mBlendFactor + entityPos.y;
                        newPos.z = diff.z * mBlendFactor + entityPos.z;
                    }
                    else if (mInterpMode == 2)
                    {
                        Vector3 diff;
                        diff.x = entityPos.x - listenerPos.x;
                        diff.y = entityPos.y - listenerPos.y;
                        diff.z = entityPos.z - listenerPos.z;
                        vectorNormalize(&diff);
                        newPos.x = diff.x * mBlendFactor + listenerPos.x;
                        newPos.y = diff.y * mBlendFactor + listenerPos.y;
                        newPos.z = diff.z * mBlendFactor + listenerPos.z;
                    }
                    else
                    {
                        // Standard lerp from listener to entity
                        newPos.x = (entityPos.x - listenerPos.x) * mBlendFactor + listenerPos.x;
                        newPos.y = (entityPos.y - listenerPos.y) * mBlendFactor + listenerPos.y;
                        newPos.z = (entityPos.z - listenerPos.z) * mBlendFactor + listenerPos.z;
                    }
                }
                else
                {
                    newPos = listenerPos;
                }
            }
            break;
        }
    }
    
    setBlendMode(0); // FUN_005e7b20
    setSoundPosition(&newPos); // FUN_005e7530
}