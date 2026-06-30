// FUNC_NAME: MissionAction::setActionParams
// Function address: 0x00423110
// Role: Sets four parameters and a type (2) on a MissionAction object, then optionally enqueues it onto a global action list.
// Offsets:
//   +0x140 : type (int, set to 2 here)
//   +0x14c : param1
//   +0x150 : param2
//   +0x154 : param3
//   +0x158 : param4

#include <cstdint>

// Forward declaration of the global action list structure (size per entry = 0x18)
struct ActionListEntry {
    void** vtable;   // +0x00 (set to &PTR_LAB_0110b6cc)
    void* object;    // +0x04 (this pointer)
    int32_t param1;  // +0x08
    int32_t param2;  // +0x0C
    int32_t param3;  // +0x10
    int32_t param4;  // +0x14
};

// Access to thread-local storage (FS segment offset 0x2c) to get game state pointer
inline void* getGameState() {
    // FS:0x2C contains a pointer to some thread-local structure
    void* fsBase;
    __asm mov fsBase, fs:[0x2c]
    return *(void**)fsBase;
}

// Global pointer to the action list head (stored at DAT_01206880+0x14)
extern uint8_t* gActionListBuffer; // actually at DAT_01206880
extern uint8_t* gActionListWritePtr; // offset +0x14

void __thiscall MissionAction::setActionParams(void* this_ptr, int32_t param1, int32_t param2, int32_t param3, int32_t param4)
{
    // Store parameters into the object
    *(int32_t*)((uint8_t*)this_ptr + 0x14c) = param1;
    *(int32_t*)((uint8_t*)this_ptr + 0x150) = param2;
    *(int32_t*)((uint8_t*)this_ptr + 0x154) = param3;
    *(int32_t*)((uint8_t*)this_ptr + 0x140) = 2;   // action type
    *(int32_t*)((uint8_t*)this_ptr + 0x158) = param4;

    // Call some initialization routine (likely registers the action)
    FUN_00423900();

    // Check if the game state allows queuing (e.g., not in menu)
    void* gameState = getGameState();
    if (*(int32_t*)(*(uint8_t**)gameState + 0x34) == 0) {
        // Get the current write pointer in the global action list buffer
        uint8_t** listWritePtr = (uint8_t**)(gActionListBuffer + 0x14);
        uint8_t* curWritePos = *listWritePtr;

        // Set vtable for this entry
        *(void**)curWritePos = &PTR_LAB_0110b6cc;  // known vtable pointer

        // Advance write pointer past vtable
        *listWritePtr = curWritePos + 4;

        // Write the object pointer and parameters into the entry
        *(void**)(*listWritePtr) = this_ptr;
        *listWritePtr += 4;
        *(int32_t*)(*listWritePtr) = param1;
        *listWritePtr += 4;
        *(int32_t*)(*listWritePtr) = param2;
        *listWritePtr += 4;
        *(int32_t*)(*listWritePtr) = param3;
        *listWritePtr += 4;
        *(int32_t*)(*listWritePtr) = param4;

        // Advance write pointer past the entire entry (0x18 bytes total)
        *listWritePtr += 0x14;
    }
}