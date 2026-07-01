// FUNC_NAME: updateAttitudeBetweenEntities
byte __thiscall updateAttitudeBetweenEntities(int this, int other)
{
    uint thisAttitude = (uint)*(byte *)(this + 0x1f1c);
    uint otherAttitude = (uint)*(byte *)(other + 0x1f1c);
    
    // Ensure thisAttitude >= otherAttitude for index calculation
    if (thisAttitude < otherAttitude) {
        uint temp = thisAttitude;
        thisAttitude = otherAttitude;
        otherAttitude = temp;
    }
    
    // Compute index into triangular attitude table
    // Index = thisAttitude - triangle(0x4f - otherAttitude) - otherAttitude
    int n = 0x4f - otherAttitude;
    int triangle = (n * (n + 1)) >> 1;  // (0x4f - other) * (0x50 - other) / 2
    int index = thisAttitude - triangle - otherAttitude;
    
    byte* tableEntry = &g_attitudeTable[index];
    byte bVar3 = *tableEntry >> 1;  // Upper bits represent change state
    
    if (bVar3 != 0) {
        char cVar4 = bVar3 - 1;
        if (cVar4 == '\0') {
            // Cooldown: decrement global counter if still active
            if (g_attitudeChangeCounter != 0) {
                g_attitudeChangeCounter--;
            }
        }
        // Update table entry: preserve low bit, set new upper bits
        *tableEntry = (*tableEntry & 1) | (cVar4 * 2);
    }
    
    // Return the current attitude flag (low bit)
    return *tableEntry & 1;
}

// Global memory used:
// uint8 g_attitudeTable[];   // +0x112c7bf
// int32 g_attitudeChangeCounter; // +0x00e53778