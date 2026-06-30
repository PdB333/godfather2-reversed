// FUNC_NAME: ControllerManager::ControllerManager
// Address: 0x006a16d0
// Role: Constructor for ControllerManager singleton. Sets vtable, stores self in global, calls init.

#include <cstdint>

// Forward declarations
void debugLog(int level, const char* message);
void ControllerManager_init(ControllerManager* self);

// Global singleton pointer
extern ControllerManager* g_controllerManager;

class ControllerManager {
public:
    void** vtable; // +0x00 vtable pointer
    // Remaining members not defined here
};

// Constructor
ControllerManager* __thiscall ControllerManager::ControllerManager(ControllerManager* this_)
{
    // Log message with channel 6 (likely debug channel)
    debugLog(6, (const char*)DAT_00d5c454);
    
    // Store this as the global singleton instance
    g_controllerManager = this_;
    
    // Set vtable to the class's vtable (at PTR_FUN_00d5d094)
    this_->vtable = (void**)(&PTR_FUN_00d5d094);
    
    // Call the actual initialization routine (separate function for clarity)
    ControllerManager_init(this_);
    
    return this_;
}