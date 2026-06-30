// FUNC_NAME: Entity::syncPhysicsTransform
// Address: 0x004b6c20
// Role: Updates the world matrix of a physics body from a transform component if moving and not in sleeping/dead state.
//        Compares with cached matrix from manager and propagates changes.

void Entity::syncPhysicsTransform()
{
    // this->+0x20: pointer to TransformComponent (16 floats + body pointer)
    TransformComponent* pComponent = *(TransformComponent**)((char*)this + 0x20);
    if (pComponent == nullptr)
        return;

    // pComponent->+0x40: pointer to PhysicsBody
    PhysicsBody* pBody = *(PhysicsBody**)&pComponent->matrix[16]; // pointer after 16 floats
    if (pBody == nullptr)
        return;

    // Body states at +0xd8: 0x07 = sleeping? 0x06 = dead?
    if (*(uint8_t*)((char*)pBody + 0xd8) == 0x07)
        return;
    if (*(uint8_t*)((char*)pBody + 0xd8) == 0x06)
        return;

    // Body velocity at +0x1a0 (vec3). If speed^2 <= threshold, skip.
    float vx = *(float*)((char*)pBody + 0x1a0);
    float vy = *(float*)((char*)pBody + 0x1a4);
    float vz = *(float*)((char*)pBody + 0x1a8);
    if ((vx*vx + vy*vy + vz*vz) <= g_velocityThreshold) // DAT_00e2b05c
        return;

    // Manager from this->+0x8
    Manager* pManager = *(Manager**)((char*)this + 0x8);
    // pManager->+0x8: pointer to vtable? Actually deref+8 gives vtable pointer?
    // Actually decompiler: piVar5 = *(int **)(*(int *)(in_EAX + 8) + 8);
    // So: this->+8 is a pointer to something that has a pointer at its +8 (the vtable)
    VTable* pVTable = *(VTable**)(*(int**)((char*)this + 8) + 8); // careful: but we can simplify as a manager with vtable
    // For reconstruction: let's assume pManager has a vtable at offset 0.
    VTable* pVTable = *(VTable**)pManager; // common pattern

    uint8_t flags = *(uint8_t*)((char*)this + 0x28);
    float localMatrix[16]; // local_e0

    if (flags & 4) // bit 2/4? Check bit 4 as 0x04
    {
        // Copy pComponent's matrix (16 floats) into localMatrix
        for (int i = 0; i < 16; ++i)
            localMatrix[i] = pComponent->matrix[i];

        // Invert the last row (translation?) subtracting from a constant (DAT_00e44564)
        // DAT_00e44564 is likely 0.0f (negation) or 1.0f (inversion). We'll call it g_flipConstant
        localMatrix[12] = g_flipConstant - pComponent->matrix[12];
        localMatrix[13] = g_flipConstant - pComponent->matrix[13];
        localMatrix[14] = g_flipConstant - pComponent->matrix[14];
        localMatrix[15] = g_flipConstant - pComponent->matrix[15];

        // Copy the 7th element (index 7) to the 4th? Actually local_94 = local_c4 (index 7)
        // Then call copy function with pBody->worldMatrix at +0xe0
        copyMatrix((void*)((char*)pBody + 0xe0), &localMatrix[0]); // FUN_00aa1cf0
    }

    // Read current state from somewhere into a buffer (64 bytes = 16 floats)
    float currentMatrix[16];
    getCurrentMatrix(&currentMatrix[0]); // FUN_00aa1a10

    // Compare the currentMatrix with a cached matrix obtained from manager
    // Manager vtable+4 returns a pointer, and we compare at its +0x40
    int* pCache = (int*)pVTable->getCachePtr(); // (**(code **)(*piVar5 + 4))()
    // pCache+0x40 is the start of 64-byte cache
    int cmpResult = memcmp(&currentMatrix, (void*)((char*)pCache + 0x40), 64);
    if (cmpResult != 0)
    {
        // Copy our localMatrix (which might have been modified) into the cache area
        // Actually we copy from currentMatrix? The code copies local_90 (currentMatrix) to pCache+0x40.
        // local_90 is the result of getCurrentMatrix.
        // Then set some fields to 0 and one to a constant.
        // Then call notification.
        memcpy((void*)((char*)pCache + 0x40), &currentMatrix, 64);

        // Clear some fields (at +0x4c, +0x5c, +0x6c within the cache)
        *(int*)((char*)pCache + 0x4c) = 0;
        *(int*)((char*)pCache + 0x5c) = 0;
        *(int*)((char*)pCache + 0x6c) = 0;
        // Set +0x7c to a constant (DAT_00e2b1a4)
        *(int*)((char*)pCache + 0x7c) = g_anotherConstant;

        notifyChange(); // FUN_006101b0

        // Then get a listener from manager vtable+0x1c and call its method at vtable+0x68
        Listener* pListener = (Listener*)pVTable->getListener(); // (**(code **)(*piVar5 + 0x1c))()
        pListener->onMatrixChanged(); // (**(code **)(*piVar5 + 0x68))()
    }
}