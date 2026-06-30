// FUN_004fd910: GhostManager::packTransformUpdate(GhostObject* ghost, GhostObject* otherGhost)

void GhostManager::packTransformUpdate(GhostObject* ghost, GhostObject* otherGhost)
{
    // Check update rate limit: +0x38 is written count, +0x3c is max count
    if (ghost->mWrittenCount >= ghost->mMaxWriteCount)
        return;

    // Get a free update packet from the pool
    NetUpdatePacket* packet = getFreeUpdatePacket();
    if (packet == nullptr)
        return;

    // Access global bone transformation at an indexed position
    // globalPtr is usually at FS:[0x2c] -> pointer to some global table
    uintptr_t* globalTable = *(uintptr_t**)(__readfsdword(0x2c) + 8);
    float* boneMatrix = (float*)(globalTable + 0x80 + ghost->mBoneIndex); // +0x10 is bone index

    float4 localRotation;
    localRotation.v[0] = boneMatrix[0];
    localRotation.v[1] = boneMatrix[1];
    localRotation.v[2] = boneMatrix[2];
    localRotation.v[3] = boneMatrix[3];

    CharacterState* state = ghost->mState; // +0x28

    // Rotation handling based on state flags
    if ((state->mFlags & 1) == 0) // +0x24
    {
        // Direct copy of bone rotation to packet
        packet->mRotation1[0] = localRotation.v[0];
        packet->mRotation1[1] = localRotation.v[1];
        packet->mRotation1[2] = localRotation.v[2];
        packet->mRotation1[3] = localRotation.v[3];
    }
    else if (state->mMoveSpeed <= 0.0f) // +0x14
    {
        // Zero out rotation if not moving
        packet->mRotation1[0] = 0.0f;
        packet->mRotation1[1] = 0.0f;
        packet->mRotation1[2] = 0.0f;
        packet->mRotation1[3] = 0.0f;
    }
    else
    {
        // Apply procedural noise to rotation (likely for character sway)
        float noise = getRandomFloat(); // FUN_004e41b0
        noise *= s_swayMagnitude; // DAT_00e2a848
        float processedNoise = applyNoise(noise); // indirectly calls FUN_004e41b0 again and FUN_004fc840
        float4 deltaRotation;
        applyRotationNoise(state->mMoveSpeed, &deltaRotation); // FUN_0045c110
        // Sum with original rotation
        packet->mRotation1[0] = localRotation.v[0] + deltaRotation.v[0];
        packet->mRotation1[1] = localRotation.v[1] + deltaRotation.v[1];
        packet->mRotation1[2] = localRotation.v[2] + deltaRotation.v[2];
        packet->mRotation1[3] = localRotation.v[3]; // Note: original code didn't add the last component? Actually it only added first three.
        // Actually in the decompiled code, only first three are added. Fourth remains? Let's keep as original: fStack_54 not added.
    }

    // Handle second rotation set (for "target" or "other ghost")
    if (state->mFlags & 0x40000000)
    {
        // Use a hardpoint manager or attachment system to get a child object
        HardpointSystem* hardpointSystem = ghost->mHardpointSystem; // +4 then +0x20?
        if (hardpointSystem != nullptr)
            hardpointSystem->addRef(); // reference count increment
        HardpointData* hardpointData = getHardpointData(hardpointSystem); // FUN_004feb20
        if (hardpointData == nullptr)
        {
            packet->mRotation2[0] = 0.0f;
            packet->mRotation2[1] = 0.0f;
            packet->mRotation2[2] = 0.0f;
            packet->mRotation2[3] = 0.0f;
        }
        else
        {
            packet->mRotation2[0] = hardpointData->mTransform[0];
            packet->mRotation2[1] = hardpointData->mTransform[1];
            packet->mRotation2[2] = hardpointData->mTransform[2];
            packet->mRotation2[3] = hardpointData->mTransform[3];
        }
        goto LAB_set_otherGhost;
    }

    if (otherGhost != nullptr)
    {
        float4 otherRotation;
        readEntityTransform(otherGhost, &otherRotation); // FUN_004e4b40
        CharacterState* otherState = otherGhost->mState; // +0x28
        if ((otherState->mFlags & 1) == 0)
        {
            packet->mRotation2[0] = otherRotation.v[0];
            packet->mRotation2[1] = otherRotation.v[1];
            packet->mRotation2[2] = otherRotation.v[2];
            packet->mRotation2[3] = otherRotation.v[3];
            goto LAB_set_otherGhost;
        }
        else if (otherState->mMoveSpeed > 0.0f)
        {
            float4 deltaRotation;
            applyRotationNoise(otherState->mMoveSpeed, &deltaRotation);
            float4 result;
            vectorAdd(&localRotation, &deltaRotation, &result); // FUN_0044d610
            packet->mRotation2[0] = result.v[0];
            packet->mRotation2[1] = result.v[1];
            packet->mRotation2[2] = result.v[2];
            packet->mRotation2[3] = result.v[3];
            goto LAB_set_otherGhost;
        }
    }
    // Default: zero out second rotation
    packet->mRotation2[0] = 0.0f;
    packet->mRotation2[1] = 0.0f;
    packet->mRotation2[2] = 0.0f;
    packet->mRotation2[3] = 0.0f;

LAB_set_otherGhost:
    packet->mOtherGhost = otherGhost; // +0x7c

    // Process and finalize packet
    processPacketRotation(&packet->mRotation2); // FUN_004fd350 (maybe normalize or interpolate)
    setStateCounter(ghost, ghost->mState->mSomeCounter); // FUN_004fd540, +0x9c

    // Set up heading and other state values
    packet->mHeadingOut = s_defaultHeading; // DAT_00e2b1a4 stored at +0x70
    packet->mUnknown72 = 0; // +0x74 originally undefined4, zeroed
    packet->mVelocity = ghost->mState->mVelocity; // +0x84 -> +0x6c

    // Clear first bit of flags
    packet->mFlags &= ~1;

    // Calculate and store detection volumes based on rotation data
    // These detection volumes are used for collision or proximity checks
    int detectionCount = ghost->mState->mFlags;
    if ((detectionCount & 0x40000000) != 0 &&
        (ghost->mState->mVolumeExtents[0] != 0 || ghost->mState->mVolumeExtents[1] != 0 ||
         ghost->mState->mVolumeExtents[2] != 0 || ghost->mState->mVolumeExtents[3] != 0))
    {
        // Create detection volume from state's extents
        float4 volumeExtents;
        volumeExtents.v[0] = (float)ghost->mState->mVolumeExtents[0]; // originally local_70 etc. but those are floats from rotation?
        // Wait, the code uses local_20 = (float)local_70 – but local_70 is a 4-byte undefined4.
        // Actually local_70 is part of the local_70 4-element array, which holds rotation data. So it's converting the rotation to floats for volume detection.
        float4 detectionRot;
        detectionRot.v[0] = (float)packet->mRotation2[0];
        detectionRot.v[1] = (float)packet->mRotation2[1];
        detectionRot.v[2] = (float)packet->mRotation2[2];
        detectionRot.v[3] = (float)packet->mRotation2[3];
        DetectionVolume* detection = createDetectionVolume(&detectionRot, ghost->mBoneIndex, 0); // FUN_004f79b0
        packet->mVolume1 = detection; // +0x84
        if (detection != nullptr)
        {
            detection->mBacklink = &packet->mVolume1;
        }
    }
    else
    {
        packet->mVolume1 = nullptr;

        if (otherGhost != nullptr)
        {
            CharacterState* otherState = otherGhost->mState;
            if (!(otherState->mVolumeExtents[0] == 0 && otherState->mVolumeExtents[1] == 0 &&
                  otherState->mVolumeExtents[2] == 0 && otherState->mVolumeExtents[3] == 0))
            {
                // Create detection volume from other ghost's rotation
                float4 otherRot;
                otherRot.v[0] = (float)packet->mRotation2[0];
                otherRot.v[1] = (float)packet->mRotation2[1];
                otherRot.v[2] = (float)packet->mRotation2[2];
                otherRot.v[3] = (float)packet->mRotation2[3];
                DetectionVolume* detection = createDetectionVolume(&otherRot, ghost->mBoneIndex, 0);
                packet->mVolume1 = detection;
                if (detection != nullptr)
                    detection->mBacklink = &packet->mVolume1;
            }
        }
    }

    // Handle second detection volume (for the ghost's own rotation)
    CharacterState* stateCheck = ghost->mState;
    if (stateCheck->mOwnVolumeExtents[0] == 0 && stateCheck->mOwnVolumeExtents[1] == 0 &&
        stateCheck->mOwnVolumeExtents[2] == 0 && stateCheck->mOwnVolumeExtents[3] == 0)
    {
        packet->mVolume2 = nullptr; // +0x80
    }
    else
    {
        float4 ownRot;
        ownRot.v[0] = localRotation.v[0];
        ownRot.v[1] = localRotation.v[1];
        ownRot.v[2] = localRotation.v[2];
        ownRot.v[3] = localRotation.v[3];
        DetectionVolume* detection = createDetectionVolume(&ownRot, ghost->mBoneIndex, 0);
        packet->mVolume2 = detection;
        if (detection != nullptr)
        {
            detection->mBacklink = &packet->mVolume2;
            ghost->mWrittenCount++;
            return; // early return as packet is fully written
        }
    }
    ghost->mWrittenCount++;
}