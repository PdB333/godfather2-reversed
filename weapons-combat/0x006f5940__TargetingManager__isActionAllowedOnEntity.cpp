// FUNC_NAME: TargetingManager::isActionAllowedOnEntity
#include <cstdint>

// Globals from decompilation (addresses in comments)
extern void* DAT_0112aa04;          // Hash table base pointer and size
extern uint32_t DAT_0112aa08;       // Some global flags
extern float _DAT_00d577a0;         // A constant float (likely 0.0f)
extern float DAT_01205214;          // Another float (distance threshold?)
extern void* DAT_012233a0;          // Some global object pointer

// Forward declarations of helper functions (only used in this function)
bool __thiscall someVirtualFunc(void* thisPtr, uint32_t someHash, void** outPtr); // vtable +0x10
bool __thiscall someOtherVirtualFunc(void* thisPtr, uint32_t param2, uint32_t param3, uint32_t param4); // vtable +0x30c
int __cdecl FUN_0077dd80();          // Returns some game state value
void* __cdecl FUN_006bc8d0(void* obj, uint32_t hash); // Cast/component retrieval

bool __thiscall TargetingManager::isActionAllowedOnEntity(
    uint32_t* entityInfo,      // Pointer to entity data (first uint is ID)
    int* actor,                // Actor/player context
    uint32_t actionFlags       // Bitmask of action flags
)
{
    uint32_t entityID;
    if (entityInfo == nullptr) {
        entityID = 0;
    } else {
        entityID = *entityInfo;
    }

    // Global hash table lookup: tableBase is at *DAT_0112aa04, bucket count at DAT_0112aa04[1]
    auto hashTableBase = *(uint32_t**)(DAT_0112aa04);
    uint32_t bucketIndex = entityID % ((uint32_t*)DAT_0112aa04)[1];
    uint32_t* entry = *(uint32_t**)((uint32_t)hashTableBase + bucketIndex * 4);

    if (entry != nullptr) {
        // Walk the chain until we find matching ID
        while (*entry != entityID) {
            entry = (uint32_t*)entry[3];
            if (entry == nullptr) {
                return false;
            }
        }

        // Validate entry and context
        if (entry != nullptr && entry != (uint32_t*)0xfffffffc && entityInfo != nullptr) {
            uint32_t entityFlags = entityInfo[7]; // +0x1C offset
            bool flagCheck = ((DAT_0112aa08 & entityFlags & 0xff000) == 0) || ((actionFlags & 0x102) != 0);
            
            if (flagCheck) {
                float entryFloat = *(float*)&entry[2]; // +0x08 offset in entry? Actually entry points to struct with [0]=ID, [1]=?, [2]=float, [3]=next
                if (entryFloat == _DAT_00d577a0 || entryFloat <= DAT_01205214) {
                    // Call virtual function on actor to get a context object
                    void* newEntityInfo = nullptr;
                    bool vfuncResult = ((bool (__thiscall*)(void*, uint32_t, void**))(*((uint32_t*)actor) + 0x10))(actor, 0x369ac561, &newEntityInfo);

                    if (!vfuncResult || newEntityInfo == nullptr) {
                        int stateValue = FUN_0077dd80();
                        if (stateValue <= (int)entityInfo[6]) { // +0x18 offset
                            // Check if actor is the global player
                            int* globalPlayer = nullptr;
                            if (*(int**)((uint32_t)DAT_012233a0 + 4) != 0) {
                                globalPlayer = *(int**)((uint32_t)DAT_012233a0 + 4) - 0x1f30; // offset -0x1f30 bytes
                            }
                            if (globalPlayer == actor) {
                                return true;
                            }
                            if ((entityInfo[7] & 0x100) != 0) { // +0x1C flag bit 0x100
                                return true;
                            }

                            // Try to get a component from actor using hash
                            void* component = (void*)FUN_006bc8d0(actor, 0x369ac561);
                            if (component == nullptr) {
                                return true;
                            }

                            // Modify actionFlags based on state
                            uint32_t modifiedFlags = actionFlags;
                            if ((int)entityInfo[6] > 2 || (actionFlags & 8) != 0) {
                                // Set bit 0 of modifiedFlags (maybe enabling something)
                                modifiedFlags = (modifiedFlags & 0xffffff00) | 1;
                            }

                            // Call another virtual function on the component
                            bool result = ((bool (__thiscall*)(void*, uint32_t, uint32_t, uint32_t))(*((uint32_t*)component) + 0x30c))(
                                component,
                                (uint32_t)(entityInfo) & 0xffffff00, // lower byte cleared?
                                actionFlags >> 4 & 0xffffff01,       // shifted bits with mask 0xffffff01
                                actionFlags >> 7 & 0xffffff01        // another shifted bit
                            );
                            if (result) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}