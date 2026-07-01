// FUNC_NAME: EntityManager::findEntityByID
// Function at 0x00840160: Searches a container of entities by a string ID (at offset +4) and returns a pointer to the entity if found.
// The container is stored in 'this' with count at offset 0x50.
// Uses a debug/log call with hash 0xa5975eb2 (likely a debug marker).

#include <cstdint>

// Forward declarations of called functions (assumed from context)
uint32_t __fastcall FUN_008e9cb0(uint32_t hash);          // Debug/log function
uint32_t __fastcall FUN_006eb670(uint32_t count);         // Returns iterator base or index offset
void*    __fastcall FUN_008400d0(uint32_t index);         // Returns object pointer from index
bool     __fastcall FUN_008effa0(void* obj, uint32_t id); // Compares object's ID (at +4) with given id
void*    __fastcall FUN_0083fa50(uint32_t index);         // Returns something from index (maybe entity pointer)

uint32_t __fastcall EntityManager::findEntityByID(uint32_t thisPtr)
{
    uint32_t count = *(uint32_t*)(thisPtr + 0x50); // Number of entities in container
    if (count != 0) {
        FUN_008e9cb0(0xa5975eb2); // Debug/log call
        uint32_t baseIndex = FUN_006eb670(count); // Get starting index (maybe 0)
        uint32_t currentIndex = 0;
        uint32_t loopCount = 0;
        if (count != 0) {
            do {
                loopCount++;
                void* obj = FUN_008400d0(baseIndex); // Get object at current index
                if (obj != nullptr) {
                    uint32_t objID = *(uint32_t*)((uint8_t*)obj + 4); // ID field at offset +4
                    if (FUN_008effa0(obj, objID)) { // Check if ID matches (likely string comparison)
                        return FUN_0083fa50(baseIndex); // Return entity pointer
                    }
                }
                baseIndex++;
                if (count <= baseIndex) {
                    baseIndex = 0; // Wrap around (circular search)
                }
            } while (loopCount < count);
        }
    }
    return 0; // Not found
}