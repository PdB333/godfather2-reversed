// FUNC_NAME: SomeObject::updateMovement
// Address: 0x00594fb0
// This function appears to be an update/tick for an object, likely related to movement or AI.
// It uses deltaTime, thresholds, and a global manager at 0x012055a8 (likely EARS::Framework::SimManager or similar).
// The this pointer is in ESI, fields accessed by offsets.

void SomeObject::updateMovement(float deltaTime)
{
    // Offset 0x4E (0x138 bytes into object) is some parameter, possibly speed or magnitude.
    float scaledValue = *(float*)(this + 0x138) * deltaTime;
    
    // Global threshold comparison
    if (DAT_00e2b05c < scaledValue)
    {
        // Construct temporary data on stack
        char localStack[76]; // length from local_50 size
        char tempBuffer[12];
        
        // Virtual call to this->vtable+0x18 (likely some init or begin)
        (*(void(__thiscall**)(SomeObject*))(((int*)this)[0]))(this, &localStack); // offset 0x18
        
        // Through global manager at DAT_012055a8 (likely a singleton)
        // vtable calls with offsets: 0x14, 0x24, 0x10, 0x64 (100), 0x30, 0x68, 0x28, 0x6c
        // These are methods of the manager.
        
        // First batch of calls
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x14))(DAT_012055a8, this + 0x20);
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x24))(DAT_012055a8, &localStack);
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x10))(DAT_012055a8, this + 0x28);
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x64))(DAT_012055a8, &scaledValue);
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x14))(DAT_012055a8, this + 0x20);
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x24))(DAT_012055a8, &somePtr); // somePtr from stack
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x10))(DAT_012055a8, this + 0x28);
        
        // Call with offset 0x30 (returns float)
        float result1 = (*(float(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x30))(DAT_012055a8);
        float threshold1 = DAT_00e2eff4;
        if (threshold1 <= result1)
        {
            float result2 = (*(float(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x30))(DAT_012055a8);
            if (result2 <= 1.0f)
            {
                result2 = (*(float(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x30))(DAT_012055a8);
                threshold1 = result2;
            }
        }
        
        // Compute some value
        float multiplied = threshold1 * DAT_00e445c8;
        
        if (/* unclear, probably comparison of pointers cast to float */ (float)&something < multiplied)
        {
            // Then branch
            (*(void(__thiscall**)(SomeObject*))(((int*)this)[0]))(this, &someArray); // vtable+0x18
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x68))(DAT_012055a8, &tempPtr);
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x28))(DAT_012055a8, &paramPtr);
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x10))(DAT_012055a8, &anotherPtr);
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x6c))(DAT_012055a8, /* division of pointers */);
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x28))(DAT_012055a8, &ptr);
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x10))(DAT_012055a8, &finalPtr);
        }
        else
        {
            // Else branch
            (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x10))(DAT_012055a8, this + 0x20);
            // Clear a flag at offset 0x1F (0x7C bytes) - bit 6 (0x40)
            *(int*)(this + 0x7C) &= ~0x40;
        }
        
        // Final calls
        (*(void(__thiscall**)(void*))((*(int*)DAT_012055a8) + 0x64))(DAT_012055a8, &temp);
        (*(void(__thiscall**)(SomeObject*))(((int*)this)[0]))(this, &buffer); // vtable+0x10
        (*(void(__thiscall**)(SomeObject*))(((int*)this)[0]))(this, &buffer2); // vtable+0x1C
    }
}