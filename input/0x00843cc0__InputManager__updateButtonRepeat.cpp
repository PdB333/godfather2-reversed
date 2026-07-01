// FUNC_NAME: InputManager::updateButtonRepeat

// Function address: 0x00843cc0
// Role: Checks if a button/condition is active; increments a repeat counter; triggers action after 5 repeats

char __thiscall InputManager::updateButtonRepeat(int thisPtr)
{
    char isActive = isInputActive(); // +0x00 ? (call to check input state)
    
    if (isActive == '\0') {
        *(int32_t*)(thisPtr + 0x44) = 0; // Reset repeat counter
        return 0;
    }
    
    *(int32_t*)(thisPtr + 0x44) = *(int32_t*)(thisPtr + 0x44) + 1; // Increment
    if (*(uint32_t*)(thisPtr + 0x44) > 4) {
        onRepeatTriggered(); // Callback when repeats exceed threshold
        *(int32_t*)(thisPtr + 0x44) = 0;
        return 1;
    }
    return 0;
}