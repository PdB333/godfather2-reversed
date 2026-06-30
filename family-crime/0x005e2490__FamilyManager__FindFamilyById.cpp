// FUNC_NAME: FamilyManager::FindFamilyById
// Function at 0x005e2490: Searches the family array (up to 5 families) for a matching family ID and retrieves a value.
// FamilyManager class layout:
//   +0x000: vtable pointer
//   +0x004: FamilyData[5] array of size 0x4A4 each (total 0x18A4)
// FamilyData structure:
//   +0x000 to 0x48B: unknown data
//   +0x1CC: some object pointer (used as argument to a global vtable function)
//   +0x484: flag (non-zero indicates valid/can retrieve value)
//   +0x48C: family ID (int)

#include <cstdint>

// Global singleton used for calling a vtable function at offset 0x68
extern void* g_pEngine;  // DAT_01223510

// FamilyData structure (size 0x4A4)
struct FamilyData {
    uint8_t unknown[0x1CC];                // +0x000
    void*   pSomeObject;                   // +0x1CC
    uint8_t pad[0x484 - 0x1CC - 4];        // padding
    uint32_t flag;                         // +0x484
    uint32_t familyId;                     // +0x48C
};

// FamilyManager class
class FamilyManager {
public:
    // +0x000: vtable
    // +0x004: FamilyData families[5];
    FamilyData families[5];
    
    // Searches for a family with the given ID.
    // Returns 1 if found, 0 otherwise.
    // If found and flag is non-zero, outValue receives the result of calling
    //   (*(*g_pEngine)->vtable[0x68])(pSomeObject)
    // If flag is zero, outValue receives -1 (0xFFFFFFFF).
    int __thiscall FindFamilyById(int familyId, uint32_t* outValue) {
        uint32_t uVar1 = 0;
        
        if (familyId != 0) {
            int index = 0;
            int* pID = (int*)((uint8_t*)this + offsetof(FamilyData, familyId)); // this + 0x490
            while (familyId != *pID) {
                index++;
                pID = (int*)((uint8_t*)pID + sizeof(FamilyData)); // stride 0x4A4
                if (index > 4) {
                    return uVar1; // 0
                }
            }
            
            // Calculate base address of the found FamilyData
            FamilyData* pFamily = &this->families[index];
            if (pFamily != nullptr) {
                uVar1 = 0xFFFFFFFF;
                if (pFamily->flag != 0) {
                    // Call vtable function at offset 0x68 on global object g_pEngine
                    uint32_t (*func)(void*) = (uint32_t (*)(void*))(*((void***)g_pEngine)[0x68]);
                    uVar1 = func(pFamily->pSomeObject);
                }
                *outValue = uVar1;
                uVar1 = 1;
            }
        }
        return uVar1;
    }
};