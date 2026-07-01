// FUNC_NAME: DebugLogger::logMarkerCallback
void DebugLogger::logMarkerCallback(void* thisPtr, void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
{
    // Magic markers used for stack integrity / debug identification
    uint32_t marker0 = 0xbadbadba; // Typically "bad" uninitialized memory
    uint32_t marker1 = 0xbeefbeef; // Typical "freed" memory pattern
    uint32_t marker2 = 0xeac15a55; // EA custom constant (EAC1 5A55?)
    uint32_t marker3 = 0x91100911; // Possibly a date or debug ID

    // Retrieve the current stack pointer from the object's internal tracker at +0x18.
    // The tracker is a pointer-to-pointer that points to a current stack slot.
    uint32_t* stackTracker = *(uint32_t**)((uint8_t*)thisPtr + 0x18);
    uint32_t stackValue = *stackTracker; // Value at current slot

    // Advance the tracker to the next slot (post-increment)
    *(uint32_t**)((uint8_t*)thisPtr + 0x18) = stackTracker + 1;

    // Hash the marker buffer (16 bytes, alignment 4) – likely for checksum validation
    HashMemory(&marker0, 0x10, 4);

    // Invoke the supplied callback with the original stack value and the four markers
    callback(stackValue, marker0, marker1, marker2, marker3);
}