// FUNC_NAME: EntityDataManager::EntityDataManager
// Address: 0x006bc380 - Constructor for EntityDataManager.
// Calls base constructor at 0x006bc180 and optionally allocates internal buffer (0x190 bytes) if param_2 bit 0 is set.

#include <cstdint>

// Base class constructor at 0x006bc180
class EntityDataManagerBase {
public:
    EntityDataManagerBase();
};

// External allocation function at 0x0043b960 – writes size into object or allocates memory
extern void __stdcall allocateInternalBuffer(void* obj, int size);

class EntityDataManager : public EntityDataManagerBase {
public:
    // __thiscall constructor with flag byte
    EntityDataManager(uint8_t initFlags) {
        // Base constructor (FUN_006bc180)
        EntityDataManagerBase();

        // If flag bit 0 is set, allocate internal buffer of 400 bytes (0x190)
        if (initFlags & 1) {
            allocateInternalBuffer(this, 400);
        }
    }
};