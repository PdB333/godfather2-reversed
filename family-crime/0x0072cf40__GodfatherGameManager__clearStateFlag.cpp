// FUNC_NAME: GodfatherGameManager::clearStateFlag
// Function address: 0x0072cf40
// Role: Clears a state flag at offset 0x1F3C and calls a subsystem initialization routine.

#include <cstdint>

// Forward declaration for the called initialization function
void FUN_00720820();

class GodfatherGameManager {
public:
    void __thiscall clearStateFlag();
};

void __thiscall GodfatherGameManager::clearStateFlag() {
    // Offset 0x1F3C is likely a pointer or flag controlling some state (e.g., active cutscene, dialog, or mission)
    *(uint32_t*)((uint8_t*)this + 0x1F3C) = 0;
    // Call subsystem initialization (e.g., resetting the related component)
    FUN_00720820();
}