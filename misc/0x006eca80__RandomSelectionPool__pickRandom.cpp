// FUNC_NAME: RandomSelectionPool::pickRandom
// Function at 0x006eca80 - Picks a random unused item from a pool, marking used in bitmask. Resets mask when all used.
// Structure: 
//   +0x00: pointer to array of items (void**)
//   +0x04: count (uint16)
//   +0x06: usedMask (uint16, bitmask of indices used so far)

// Note: DAT_00e44590 is a float constant (likely 1.0f / RAND_MAX) used to scale rand() to [0,1)
// Example: if RAND_MAX = 32767, then 1.0f / 32768.0f = 3.0518e-5

int __thiscall RandomSelectionPool::pickRandom(RandomSelectionPool* this, uint16_t* outIndex)
{
    uint32_t fullMask = 0;
    uint16_t usedMask = 0;
    uint32_t indexIter = 0;
    uint16_t count = *(uint16_t*)(this + 4); // offset +4: count
    
    if (count != 0) {
        do {
            uint8_t bitPos = (uint8_t)indexIter & 0x1f; // 5 bits for 16-bit shift (though shift limited to 31)
            fullMask |= (1 << bitPos);
            indexIter++;
            usedMask = (uint16_t)fullMask;
        } while (indexIter < count);
    }
    
    // If all items have been used, reset the mask
    uint16_t currentMask = *(uint16_t*)((int)this + 6); // offset +6: used mask
    if (usedMask == (usedMask & currentMask)) {
        *(uint16_t*)((int)this + 6) = 0; // reset mask
    }
    
    if (count == 0) {
        return 0; // no items available
    }
    
    // Random selection
    int randVal = rand();
    // Scale rand to [0,1) and multiply by count, then truncate to 16-bit index
    uint32_t rawIndex = (uint32_t)((float)randVal * DAT_00e44590 * (float)count) & 0xffff;
    uint16_t chosenIndex = (uint16_t)rawIndex;
    
    // Ensure chosen index is not already used
    currentMask = *(uint16_t*)((int)this + 6);
    if ((currentMask & (1 << (chosenIndex & 0x1f))) != 0) {
        // Wrap around modulo count until finding an unused slot
        do {
            chosenIndex = (uint16_t)((uint32_t)(chosenIndex + 1) % count);
        } while ((*(uint16_t*)((int)this + 6) & (1 << (chosenIndex & 0x1f))) != 0);
    }
    
    // Mark chosen index as used
    *(uint16_t*)((int)this + 6) = currentMask | (uint16_t)(1 << (chosenIndex & 0x1f));
    
    // Write index to output parameter
    *outIndex = chosenIndex;
    
    // Return pointer to the selected item (base + index * 4)
    return *(int*)(*(int*)this + chosenIndex * 4); // offset +0: pointer to array of ints
}