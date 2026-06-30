// FUNC_NAME: SimManager::removeObjectByHandle

#include <cstdint>

// Forward declaration of the removal callback function
bool __fastcall objectRemovalCallback(uint32_t arg0, uint32_t arg1, uint32_t arg2);

class SimManager {
public:
    // Structure of an entry in the object array (size 0x30)
    struct ObjectEntry {
        uint8_t  pad0[0x2C];  // padding
        uint32_t handle;      // +0x2C: full handle (includes generation/type)
    };

    // Static callback arguments (pointed to by global unaff_ESI)
    struct RemovalContext {
        uint32_t arg0;
        uint32_t arg1;
        uint32_t arg2;
    };

    static RemovalContext s_removalContext;  // stored in static memory

    // This function uses the following register conventions:
    //   unaff_EDI = this pointer
    //   unaff_ESI = &s_removalContext
    // Parameters:
    //   param_1 (ECX) = unused (likely a leftover from earlier version)
    //   handle (EDX)  = the object handle to remove
    bool __fastcall removeObjectByHandle(uint32_t handle) {
        uint16_t index = static_cast<uint16_t>(handle & 0xFFFF);
        if (index < 0x200) {
            // Array starts at this+0x10, each element is 0x30 bytes
            ObjectEntry* entry = reinterpret_cast<ObjectEntry*>(
                reinterpret_cast<uintptr_t>(this) + 0x10 + index * sizeof(ObjectEntry)
            );
            if (entry != nullptr && entry->handle == handle) {
                // Call the removal backend with the static context
                objectRemovalCallback(
                    s_removalContext.arg0,
                    s_removalContext.arg1,
                    s_removalContext.arg2
                );
                return true;
            }
        }
        return false;
    }
};