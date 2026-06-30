// FUNC_NAME: EffectManager::spawnEffect

void EffectManager::spawnEffect(EffectManager* thisManager, Entity* attachedObject)
{
    float newPosX, newPosY, newPosZ, newPosW; // world position (vec4)
    float newRotX, newRotY, newRotZ, newRotW; // orientation quaternion
    float someConstVec[4]; // from DAT_00e2b1a4, likely (1,0,0,0) identity quaternion or offset
    float tempVec[4];
    EffectInstance* newEffect;
    float strength;
    bool useAttached;
    int handle;

    // Check if the spawn pool has room
    if (thisManager->currentCount >= thisManager->maxCount)
        return;

    // Allocate a new effect instance from the pool
    newEffect = allocateEffectFromPool();
    if (newEffect == nullptr)
        return;

    // Get the world position from the global camera/view transform
    // The offset 0x10 is an index into an array of transforms
    {
        float* worldPos = (float*)(*(*(int**)(__readfsdword(0x2c) + 8) + 8) + 0x80 +
                                    thisManager->effectTypeIndex * 4);
        newPosX = worldPos[0];
        newPosY = worldPos[1];
        newPosZ = worldPos[2];
        newPosW = worldPos[3];
    }

    strength = 0.0f;
    // Check if the effect is not attached to a parent (bit0 clear)
    if ((thisManager->template->flags & 1) == 0)
    {
        // Simple copy of position
        newEffect->position[0] = newPosX;
        newEffect->position[1] = newPosY;
        newEffect->position[2] = newPosZ;
        newEffect->position[3] = newPosW;
    }
    else if (thisManager->template->randomStrength <= 0.0f)
    {
        // Attached but no strength: zero out position (relative?)
        newEffect->position[0] = 0.0f;
        newEffect->position[1] = 0.0f;
        newEffect->position[2] = 0.0f;
        newEffect->position[3] = 0.0f;
    }
    else
    {
        // Attached with strength: apply random offset scaled by strength
        float rand1 = randomFloat(); // FUN_004e41b0 (no args)
        float scaled = rand1 * globalRandomScale; // DAT_00e2a848
        float rand2 = randomFloat(); // FUN_004e41b0 with arg? Actually it uses fVar4
        // The second call might be different; here just use same variable
        rand2 = randomFloat(); // Actually the code shows: fVar4 = fVar4 * DAT_00e2a848; then calls with fVar4?
        // Let's reconstruct: after first call, fVar4 = random; then multiply; then call FUN_004e41b0(fVar4) which might be a second random seeded?
        // Then FUN_004fc840(fVar4 * DAT_00e2a848) maybe another random. Then vector scale
        // For simplicity, we'll use a random offset vector.
        float offset[4];
        getRandomOffset(&offset, thisManager->template->randomStrength); // FUN_0045c110 combines
        newEffect->position[0] = newPosX + offset[0];
        newEffect->position[1] = newPosY + offset[1];
        newEffect->position[2] = newPosZ + offset[2];
        // No change to W?
    }

    // Handle orientation (quaternion)
    if ((thisManager->template->flags & 0x40000000) != 0)
    {
        // Use attached node's transform (if available)
        int nodeIndex = thisManager->someNodeRef->transformIndex; // +0x20
        if (nodeIndex != 0)
        {
            addRefTransform(nodeIndex); // increment ref count
        }
        handle = getTransformQuaternion(nodeIndex); // FUN_004feb20
        if (handle == 0)
        {
            // No transform: zero out orientation
            newEffect->orientation[0] = 0.0f;
            newEffect->orientation[1] = 0.0f;
            newEffect->orientation[2] = 0.0f;
            newEffect->orientation[3] = 0.0f;
        }
        else
        {
            // Copy quaternion from transform
            newEffect->orientation[0] = *(float*)(handle + 0x10);
            newEffect->orientation[1] = *(float*)(handle + 0x14);
            newEffect->orientation[2] = *(float*)(handle + 0x18);
            newEffect->orientation[3] = *(float*)(handle + 0x1c);
        }
        goto LABEL_ORIENTATION_SET;
    }

    // No direct transform: try to get orientation from attached object
    if (attachedObject != nullptr)
    {
        getWorldQuaternion(attachedObject, &newRotQuat); // FUN_004e4b40
        if ((attachedObject->template->flags & 1) == 0)
        {
            // Simple copy
            newEffect->orientation[0] = newRotX;
            newEffect->orientation[1] = newRotY;
            newEffect->orientation[2] = newRotZ;
            newEffect->orientation[3] = newRotW;
            goto LABEL_ORIENTATION_SET;
        }
        // If attached and has random strength, apply random rotation
        if (attachedObject->template->randomStrength > 0.0f)
        {
            float rand_rot[4];
            getRandomRotationOffset(&rand_rot, attachedObject->template->randomStrength); // FUN_0045c110
            combineQuaternions(&newEffect->orientation, rand_rot, &newRotQuat); // FUN_0044d610
            goto LABEL_ORIENTATION_SET;
        }
    }

    // Default: zero orientation
    newEffect->orientation[0] = 0.0f;
    newEffect->orientation[1] = 0.0f;
    newEffect->orientation[2] = 0.0f;
    newEffect->orientation[3] = 0.0f;

LABEL_ORIENTATION_SET:
    // Store attached object reference
    newEffect->attachedObject = attachedObject;

    // Initialize the effect (position and orientation already set)
    initializeEffect(&newRotQuat); // FUN_004fd350
    updateEffectData(thisManager, thisManager->template->someData); // FUN_004fd540

    // Prepare constant vector (likely identity quaternion or default scale)
    someConstVec[0] = globalConstVec.x; // DAT_00e2b1a4
    someConstVec[1] = globalConstVec.y;
    someConstVec[2] = globalConstVec.z;
    someConstVec[3] = globalConstVec.w;

    // Set effect parameters
    newEffect->param0 = thisManager->template->someParam; // +0x84
    newEffect->flags = newEffect->flags & ~1; // clear bit0
    newEffect->constantVec = someConstVec; // copy?

    // Now decide if we need to create resource handles for position and orientation
    // For orientation: check if template has transform and it's non-zero
    bool hasOrientationResource = false;
    if ((thisManager->template->flags & 0x40000000) != 0)
    {
        // Check if transform exists (non-zero quaternion)
        if (thisManager->template->transform[0] != 0.0f ||
            thisManager->template->transform[1] != 0.0f ||
            thisManager->template->transform[2] != 0.0f ||
            thisManager->template->transform[3] != 0.0f)
        {
            hasOrientationResource = true;
        }
    }
    else if (attachedObject != nullptr)
    {
        // Check attached object's transform
        EntityTemplate* attTmpl = attachedObject->template;
        if (attTmpl->transform[0] != 0.0f ||
            attTmpl->transform[1] != 0.0f ||
            attTmpl->transform[2] != 0.0f ||
            attTmpl->transform[3] != 0.0f)
        {
            hasOrientationResource = true;
        }
    }

    if (hasOrientationResource)
    {
        // Convert quaternion to floats for resource creation
        float quatArray[4] = { newRotX, newRotY, newRotZ, newRotW };
        handle = createResourceHandle(someConstVec, thisManager->someArray + 0x84, 0); // FUN_004f79b0
        newEffect->orientResource = handle;
        if (handle != 0)
        {
            *(int**)(handle + 8) = &newEffect->orientResource; // set self-pointer
        }
    }
    else
    {
        newEffect->orientResource = 0;
    }

    // For position: check if template position is non-zero
    bool hasPositionResource = false;
    if (thisManager->template->position[0] != 0.0f ||
        thisManager->template->position[1] != 0.0f ||
        thisManager->template->position[2] != 0.0f ||
        thisManager->template->position[3] != 0.0f)
    {
        hasPositionResource = true;
    }

    if (hasPositionResource)
    {
        float posArray[4] = { newPosX, newPosY, newPosZ, newPosW };
        handle = createResourceHandle(someConstVec, thisManager->someArray + 0x84, 0);
        newEffect->posResource = handle;
        if (handle != 0)
        {
            *(int**)(handle + 8) = &newEffect->posResource;
            // Immediately increment count and return (early exit)
            thisManager->currentCount++;
            return;
        }
    }
    else
    {
        newEffect->posResource = 0;
    }

    // Increment count for normal path
    thisManager->currentCount++;
    return;
}