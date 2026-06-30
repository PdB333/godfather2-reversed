// FUNC_NAME: RingBufferAllocator::acquireSlot
int __thiscall RingBufferAllocator::acquireSlot(void* thisPtr)
{
    int currentSlot = *(int*)((char*)thisPtr + 0x1c);
    int base = *(int*)((char*)thisPtr + 0x18);

    if (currentSlot != 0) {
        // Check if current slot is already in use
        if (*(int*)(currentSlot + 0x24) == 1) {
            int iterSlot = currentSlot;
            do {
                // Advance to next slot (each slot is 0x2c bytes)
                *(int*)((char*)thisPtr + 0x1c) = iterSlot + 0x2c;
                if (iterSlot + 0x2c == base + 0x1130) {
                    // Wrap around to the beginning of the ring buffer
                    *(int*)((char*)thisPtr + 0x1c) = base;
                }
                iterSlot = *(int*)((char*)thisPtr + 0x1c);
            } while ((iterSlot != currentSlot) && (*(int*)(iterSlot + 0x24) == 1));
        }
        currentSlot = *(int*)((char*)thisPtr + 0x1c);
        if (*(int*)(currentSlot + 0x24) != 1) {
            // Found a free slot; initialize it via callback (FUN_006f5320)
            FUN_006f5320();
            // Mark as used
            *(int*)(currentSlot + 0x24) = 1;
            // Advance cursor past this slot
            int nextSlot = currentSlot + 0x2c;
            if (nextSlot == base + 0x1130) {
                nextSlot = base;
            }
            *(int*)((char*)thisPtr + 0x1c) = nextSlot;
            return currentSlot;
        }
    }
    return 0; // No free slot available
}