// FUN_004e39d0: CallbackManager::registerCallback

#include <cstdint>

// Global callback registration table (used for duplicate detection)
struct GlobalCallback {
    uint32_t id;    // +0x00
    uint32_t flags; // +0x04 (bottom 2 bits cleared on duplicate)
};

static GlobalCallback s_globalCallbacks[20]; // at 0x01218e50, 0x01218e54

// Per-slot callback table (one slot per controller/object instance)
struct InstanceCallback {
    uint32_t id;   // +0x00
    uint32_t data; // +0x04 (user parameter)
};

static InstanceCallback s_instanceCallbacks[20]; // at 0x011f38f0, 0x011f38f4

// Forward declaration of the notification function
void FUN_00609340();

// __fastcall: this appears to be a static method called with EAX=callbackId, EDX=userData, ESI=slotIndex
void __fastcall CallbackManager::registerCallback(uint32_t callbackId, uint32_t userData)
{
    int slotIndex = unaff_ESI; // value from register ESI (not shown in signature)

    // Slot 4 is reserved (e.g., system callback) – skip duplicate check for it
    if (slotIndex != 4)
    {
        // Search global list for an existing registration with same ID
        for (int i = 0; i < 20; i++)
        {
            if (s_globalCallbacks[i].id == callbackId)
            {
                // Clear the bottom two bits of the flags (reset status)
                s_globalCallbacks[i].flags &= 0xFFFFFFFC;
                break;
            }
        }
    }

    // Register the callback ID and user data in the instance's slot
    s_instanceCallbacks[slotIndex].id = callbackId;
    s_instanceCallbacks[slotIndex].data = userData;

    // Notify system of the new registration
    FUN_00609340();
}