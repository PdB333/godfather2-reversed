// FUNC_NAME: ActionDecider::checkEventTrigger
// Address: 0x0071f690
// Checks if a random event should trigger based on a slot-derived key and a global threshold.
// The system must be in a valid state (not zero and not special value 0x1f30).
// The threshold is modified by a per-event seed (0x1cfd170f) via a noise function.

bool __fastcall ActionDecider::checkEventTrigger(void* this) {
    int key;
    int* systemPtr;

    // Check global system state: pointer at g_systemState + 0x04 must be valid
    systemPtr = *reinterpret_cast<int**>(g_systemState + 4); // g_systemState + 0x04: system state pointer
    if ((systemPtr == nullptr) || (systemPtr == reinterpret_cast<int*>(0x1f30))) {
        return false;
    }

    // Derive key from the slot index stored at this+0x04
    int slot = *reinterpret_cast<int*>(static_cast<char*>(this) + 4); // +0x04: slot index
    if (slot == 0) {
        key = 0;
    } else {
        key = slot - 0x48; // base offset for slot-derived random seed
    }

    // Generate a float value from the key (e.g., a hash or pseudo-random mapping)
    float randomValue = static_cast<float>(FUN_00470360(key)); // key-to-float conversion

    // Get the base threshold from global memory
    float threshold = g_baseThreshold; // DAT_00d5ddec: base threshold value

    // Modify threshold using event-specific seed (0x1cfd170f) via noise/adjustment function
    FUN_008934e0(0x1cfd170f, &threshold); // applies per-event variation

    // Return true if the random value is below the adjusted threshold
    return randomValue < threshold;
}