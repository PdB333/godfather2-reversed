// FUNC_NAME: AudioPerformanceRequestManager::AudioPerformanceRequestManager

// Function address: 0x006a4820
// Role: Constructor for AudioPerformanceRequestManager class
// Initializes base class, vtable, boolean flags, and registers two performance request types.

#include <cstdint>

// Forward declarations
class BaseAudioManager;
extern BaseAudioManager* g_ambientAudioPerfRequestClass;  // DAT_0112a534
extern BaseAudioManager* g_someOtherPerfRequestClass;     // DAT_0112db74

// Vtable structures (offsets from base of vtable pointer array)
struct AudioPerformanceRequestManagerVtable {
    void* vfunc0;   // PTR_FUN_00d5d724
    // ... other virtual functions
};

struct InnerVtable1 {
    // PTR_LAB_00d5d714
};

struct InnerVtable2 {
    // PTR_LAB_00d5d710
};

class AudioPerformanceRequestManager : public BaseAudioManager {
public:
    // +0x00: vtable pointer
    // +0x3C (0x0F * 4): pointer to inner vtable1 (list head?)
    // +0x48 (0x12 * 4): pointer to inner vtable2
    // +0x50: bool flag (initialized to 0)
    // +0x51: bool flag (initialized to 0)
    // +0x52: bool flag (initialized to 1)
    // +0x54: int (initialized to 0)
    // +0x58: int (initialized to 0)
    // +0x5C: int (initialized to 0)
    // +0x60: int (initialized to 0)

    AudioPerformanceRequestManager(void* param2);  // constructor
};

// External functions (from other modules)
extern BaseAudioManager* __thiscall BaseAudioManager::BaseAudioManager(void* param2); // FUN_0046c590
extern BaseAudioManager* __cdecl FindClassByName(const char* name); // FUN_00408240
extern void __thiscall RegisterRequestList(void* list, BaseAudioManager* classPtr, uint32_t flags); // FUN_00408900

AudioPerformanceRequestManager::AudioPerformanceRequestManager(void* param2) {
    // Call base class constructor
    BaseAudioManager::BaseAudioManager(param2);

    // Set vtable pointer
    this->vtable = &AudioPerformanceRequestManagerVtable;

    // Set inner vtable pointers
    *(void**)((uint32_t)this + 0x3C) = &InnerVtable1;  // param_1[0xf] = &PTR_LAB_00d5d714
    *(void**)((uint32_t)this + 0x48) = &InnerVtable2;  // param_1[0x12] = &PTR_LAB_00d5d710

    // Initialize flags
    *(bool*)((uint32_t)this + 0x50) = false;
    *(bool*)((uint32_t)this + 0x51) = false;
    *(bool*)((uint32_t)this + 0x52) = true;

    // Zero out integer fields
    *(int*)((uint32_t)this + 0x54) = 0;
    *(int*)((uint32_t)this + 0x58) = 0;
    *(int*)((uint32_t)this + 0x5C) = 0;
    *(int*)((uint32_t)this + 0x60) = 0;

    // Look up class handle by name and register
    BaseAudioManager* ambientClass = FindClassByName("AmbientAudioPerformanceRequest");
    if (ambientClass != nullptr) {
        RegisterRequestList(this + 0x3C, &ambientClass, 0x8000);
    }

    // Register second performance request class
    if (g_someOtherPerfRequestClass != nullptr) {
        RegisterRequestList(this + 0x3C, g_someOtherPerfRequestClass, 0x8000);
    }
}