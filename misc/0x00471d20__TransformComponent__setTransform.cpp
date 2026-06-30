// FUNC_NAME: TransformComponent::setTransform

void __thiscall TransformComponent::setTransform(float* newTransform)
{
    // Sub-object at +0x130 (e.g., attached visual/physics proxy)
    TransformComponent* subObj = *(TransformComponent**)((int)this + 0x130);
    if (subObj != 0) {
        // Copy first 2 vectors (16 bytes) from newTransform into sub-object at +0x20 and +0x28
        *(double*)((int)subObj + 0x20) = *(double*)newTransform;
        *(double*)((int)subObj + 0x28) = *(double*)(newTransform + 2);
    }

    // If logging/broadcasting is enabled (flag at +0x164)
    if (*(int*)((int)this + 0x164) != 0) {
        float fVar3 = newTransform[1];
        float fVar4 = newTransform[2];
        float fVar5 = newTransform[3];

        // Compare each component with the stored state; build a 4-bit mask
        // auVar9 holds -1 for equal, 0 for not equal (sign bit = set if equal)
        int auVar9[4];
        auVar9[0] = -((int)(*(float*)((int)this + 0x120) == newTransform[0]));
        auVar9[1] = -((int)(*(float*)((int)this + 0x124) == fVar3));
        auVar9[2] = -((int)(*(float*)((int)this + 0x128) == fVar4));
        auVar9[3] = -((int)(*(float*)((int)this + 300)  == fVar5));

        // Extract sign bits to form a mask (movmskps equivalent)
        int changeMask = 0;
        if (auVar9[0] < 0) changeMask |= 1;
        if (auVar9[1] < 0) changeMask |= 2;
        if (auVar9[2] < 0) changeMask |= 4;
        if (auVar9[3] < 0) changeMask |= 8;

        // Update internal state
        *(float*)((int)this + 0x120) = newTransform[0];
        *(float*)((int)this + 0x124) = fVar3;
        *(float*)((int)this + 0x128) = fVar4;
        *(float*)((int)this + 300)   = fVar5;

        // If any component changed (mask != 0xF), log the event
        if (changeMask != 0xF) {
            // Gather the new 16-byte state
            double stateLow  = *(double*)((int)this + 0x120);
            double stateHigh = *(double*)((int)this + 0x128);

            // Global event buffer: DAT_01206880 +0x14 holds a write pointer
            int** evtBuffer = *(int***)(DAT_01206880 + 0x14);
            evtBuffer[0] = &PTR_LAB_0110ba80;           // vtable/type descriptor
            int* writePos = evtBuffer + 4;              // advance by 4 bytes

            // Store the subject ID (pointer to component at +0x54)
            *(int*)*writePos = (int)this + 0x54;
            writePos = (int*)(((int)writePos + 7) & 0xFFFFFFFC); // align to 8 bytes

            // Store the 16-byte log data (new state)
            *(double*)writePos = stateLow;
            *(double*)(writePos + 2) = stateHigh;

            // Update the write pointer by 16 bytes
            evtBuffer = (int**)((int)evtBuffer + 16);
            *(int***)(DAT_01206880 + 0x14) = evtBuffer;
        }
    }
}