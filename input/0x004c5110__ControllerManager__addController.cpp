// FUNC_NAME: ControllerManager::addController

class ControllerManager {
    // Class layout:
    // +0x00 : other members (80 bytes total)
    // +0x50 : ControllerData controllers[8]; // each 0xC0 bytes (192 bytes)
    // +0x650: int controllerCount; // number of valid entries (0-8)
public:
    // Returns 1 on success, 0 if the array is full (already has 8 entries)
    int __thiscall addController(void* thisPtr, const undefined4* source);
};

int __thiscall ControllerManager::addController(void* thisPtr, const undefined4* source) {
    // Check if the array is full (maximum 8 entries)
    int* count = reinterpret_cast<int*>(static_cast<char*>(thisPtr) + 0x650);
    if (*count > 7) {
        return 0; // No space left
    }

    // Calculate pointer to the next free slot in the array
    // Array starts at +0x50, each element is 0xC0 bytes
    undefined4* dest = reinterpret_cast<undefined4*>(
        static_cast<char*>(thisPtr) + 0x50 + (*count) * 0xC0
    );

    // Copy 0x30 dwords (0xC0 bytes) from source to the slot
    for (int i = 0; i < 0x30; i++) {
        *dest = *source;
        ++dest;
        ++source;
    }

    // Increment the count of valid entries
    (*count)++;
    return 1; // Success
}