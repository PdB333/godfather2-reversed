// FUNC_NAME: SimManager::checkEntityActionStatus
// Address: 0x007abd90
// This function checks the action status of an entity given a query type.
// It appears to look up an entity from two possible lists (active and reserve)
// via offsets 0x24fc and 0x1c78 relative to a structure at this+0x58.
// Then it calls a virtual function on the entity (vtable+0x10) with hash 0x55859efa.
// Depending on the input byte (checkType), it returns either 1 (if 2 or 3) or
// the result of the virtual call with the low byte cleared.

#include <cstdint>

// Forward declarations (unknown types)
class SimEntity; // Entity with vtable

class SimManager {
public:
    // Offset 0x58: pointer to some global data block (likely a registry or pool)
    uint8_t* m_pGlobalData; // +0x58

    // Function to check entity action status
    uint32_t __fastcall checkEntityActionStatus(uint8_t checkType) {
        // Retrieve pointers from global data block
        uint32_t* pObject1 = *(uint32_t**)(*(int*)(m_pGlobalData + 0x24fc)); // +0x24fc
        int32_t iObject2Index = *(int*)(*(int*)(m_pGlobalData + 0x1c78));   // +0x1c78

        // Determine a valid entity pointer (vtable offset -0x48? maybe header)
        SimEntity* pEntity = nullptr;
        if (pObject1 != nullptr) {
            pEntity = (SimEntity*)((uint8_t*)pObject1 - 0x48);
        }
        if (pEntity == nullptr && iObject2Index != 0) {
            pEntity = (SimEntity*)((uint8_t*)iObject2Index - 0x48);
        }

        if (pEntity != nullptr) {
            uint32_t vtableCallResult = 0;
            // Call virtual function at offset 0x10 with a specific hash
            uint32_t (*vfunc)(uint32_t) = (uint32_t (*)(uint32_t))(*((uint32_t**)pEntity)[0x10 / 4]);
            vtableCallResult = vfunc(0x55859efa); // hash likely "isActive" or similar

            // Check low byte of result
            if ((vtableCallResult & 0xFF) != 0) {
                // Stack manipulation (likely a compiler artifact)
                uint8_t uVar3 = (uintptr_t)&vtableCallResult >> 8 & 0xFFFFFF; // high 3 bytes of address
                uint32_t combined = (uVar3 << 8) | checkType;

                if (checkType == 2 || checkType == 3) {
                    return 1;
                } else {
                    // Return combined value with low byte cleared
                    return combined & 0xFFFFFF00;
                }
            }
        }

        // Default: return the original vtableCallResult (if any) with low byte cleared
        // (or return 0 if pEntity was null)
        return (uintptr_t)&vtableCallResult & 0xFFFFFF00; // Actually this is stack address garbage; see comments
        // Note: The decompiled code suggests a final return of (uint)puVar2 & 0xffffff00,
        // where puVar2 might hold different values depending on path. This is likely
        // a decompilation artifact; the actual logic probably returns 0 when no entity is found.
    }
};