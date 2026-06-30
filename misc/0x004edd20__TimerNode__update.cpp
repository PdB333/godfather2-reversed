// FUNC_NAME: TimerNode::update
void __thiscall TimerNode::update(TimerNode* this, float deltaTime)
{
    float valueFromData;
    uint* flagPtr;
    float local_f4 = 0.0f;
    int* tls = *(int**)(__readfsdword(0x2c) + 0x2c); // Thread-local storage base

    // Store delta time at +0x30
    this->field_0x30 = deltaTime;

    // +0x24 points to some data structure
    valueFromData = *(float*)(*(int*)(this + 0x24) + 0x94);

    // Global threshold DAT_00e2eff4
    if (DAT_00e2eff4 < valueFromData)
    {
        if (*(float*)(this + 0x2c) <= valueFromData)
        {
            // Accumulate timer at +0x2c
            *(float*)(this + 0x2c) += deltaTime;
        }
        else if ((*(ushort*)(*(int*)(this + 0x24) + 0x2c) & 0x2000) == 0)
        {
            deltaTime = 0.0f; // Pause or skip
        }
        else
        {
            // Set a "finished" or "interrupt" flag on the indirect target
            flagPtr = (uint*)(*(int*)(this + 0x10) + *(int*)(*tls + 8));
            *flagPtr |= 0x20000000;
        }
    }

    // If the flag was not just set, continue processing subtimers
    if ((*(uint*)(*(int*)(*tls + 8) + *(int*)(this + 0x10)) & 0x20000000) == 0)
    {
        // Timer 1 (from bitfield bits 11-15 of field at +0x2c of data)
        if (*(int*)(this + 0x4c) != 0)
        {
            uint id1 = (uint)((*(ushort*)(*(int*)(this + 0x24) + 0x2c) >> 0xb) & 0x1F);
            *(float*)(this + 0x44) += deltaTime;
            FUN_004edf00(this, id1); // Fire event with ID1
        }

        // Timer 2 (from bitfield bits 12-16)
        if (*(int*)(this + 0x58) != 0)
        {
            uint id2 = (uint)((*(ushort*)(*(int*)(this + 0x24) + 0x2c) >> 0xc) & 0x1F);
            *(float*)(this + 0x50) += deltaTime;
            FUN_004edf00(this, id2);
        }

        // Additional timer based on condition from data+0x58 and this+0x5c
        if ((local_f4 <= *(float*)(*(int*)(this + 0x24) + 0x58)) && (*(char*)(this + 0x5c) != 0))
        {
            *(float*)(this + 0x34) += deltaTime;
        }
    }
}