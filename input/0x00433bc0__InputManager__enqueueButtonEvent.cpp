// FUNC_NAME: InputManager::enqueueButtonEvent

#include <cstdint>

// Global data pointers (addresses from decompilation)
extern int* DAT_01206880; // Points to a command queue structure [offset +0x14: write cursor]
extern int* DAT_012233a8; // Points to a game state structure [+4: instance, +0x3af8: flag field]

// Known vtable address for command objects (from PTR_LAB_0110b84c)
static const uintptr_t COMMAND_VTABLE = 0x0110b84c;

// Thread-local check: returns true if the current thread should use direct flag set (not main thread)
inline bool isNotMainThread()
{
    // FS:[0x2C] -> TEB, then +0x34 stores a thread identifier or lock flag
    return *(int*)(*(int*)(*(int*)(__readfsdword(0x2C) + 0x2C) + 0x34)) != 0;
}

void InputManager::enqueueButtonEvent(int32_t param_1)
{
    if (!isNotMainThread())
    {
        // Main thread: append a command object to the queue
        int* writeCursor = reinterpret_cast<int*>(DAT_01206880 + 0x14);
        // Write the vtable pointer (8 bytes per entry: [vtable, param])
        *reinterpret_cast<uintptr_t*>(*writeCursor) = COMMAND_VTABLE;
        *writeCursor += 4;
        // Store the parameter
        *reinterpret_cast<int*>(*writeCursor) = param_1;
        *writeCursor += 4;
        return;
    }

    // Background thread: directly set a flag at offset 0x3af8
    uint32_t* flagField = reinterpret_cast<uint32_t*>(
        *reinterpret_cast<int*>(DAT_012233a8 + 4) + 0x3af8);
    if (param_1 != 0)
    {
        // Clear bit 3 (0x8) when param is non-zero (disable state)
        *flagField &= ~0x8u;
    }
    else
    {
        // Set bit 3 when param is zero (enable state)
        *flagField |= 0x8u;
    }
}