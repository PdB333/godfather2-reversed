// FUNC_NAME: ControllerManager::getActionForKey
// Address: 0x007baba0
// Role: Maps a virtual key code to an action ID, considering current player context and game state.

#include <cstdint>

// Forward declarations for global helper functions
bool __stdcall isGameActive();                 // from FUN_00481640
bool __stdcall isActionAllowedInContext(int contextId); // from FUN_007b9f80

// Global table of 12 action entries (DWORD each)
extern const uint32_t s_actionMappingTable[12]; // DAT_00d6dba0

class ControllerManager {
public:
    // Returns 0 if action is not available or mapping fails.
    uint32_t __thiscall getActionForKey(char virtualKey) const;
};

uint32_t __thiscall ControllerManager::getActionForKey(char virtualKey) const {
    // Context checks only occur when the game is not active (e.g., menus, loading).
    if (!isGameActive()) {
        // +0x188: Current player context ID (e.g., 0x48 = in car, 0x00 = on foot)
        int contextField = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x188);
        
        // 0 and 0x48 are sentinel values indicating invalid context.
        if (contextField == 0 || contextField == 0x48) {
            return 0;
        }
        
        // Convert context field to an array index by subtracting offset 0x48.
        int contextId = (contextField != 0) ? (contextField - 0x48) : 0;
        
        // Check whether the current context allows any action mapping.
        if (!isActionAllowedInContext(contextId)) {
            return 0;
        }
        
        // +0x90: flags; bit 0 = input blocked (e.g., during cutscene or pause)
        if ((*reinterpret_cast<const uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x90) & 1) != 0) {
            return 0;
        }
    }
    
    // Map virtual key (only keys 0x28–0x33 are valid) to the 12-entry global table.
    uint32_t index = static_cast<uint32_t>(static_cast<unsigned char>(virtualKey) - 0x28);
    if (index < 12) {
        return s_actionMappingTable[index];
    }
    
    return 0;
}