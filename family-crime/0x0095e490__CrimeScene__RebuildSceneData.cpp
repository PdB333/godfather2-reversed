// FUNC_NAME: CrimeScene::RebuildSceneData
#include <cstdint>

// Global manager pointer (used to access entities by index)
extern int* g_pEntityManager; // DAT_0112b9b4

// Global dynamic array of pairs (each 8 bytes)
extern uint32_t* g_pGlobalList;      // DAT_011307f8
extern uint32_t g_globalListCount;   // DAT_011307fc
extern uint32_t g_globalListCapacity; // DAT_01130800

// External functions
void* __fastcall GetDefaultTemplate();    // FUN_008a30d0
void __fastcall FreeMemory(void* ptr);    // FUN_009c8f10
void __fastcall GrowGlobalArray(uint32_t newCapacity); // FUN_0095c7f0

class CrimeScene {
public:
    // Fields (offsets from this):
    // +0x00 : first 0x1c uint32s copied from template (112 bytes)
    // +0x10 : m_targetPointer (param_1[4])
    // +0x70 : m_index (param_1[0x1c])
    // +0x74 : m_anotherCount (param_1[0x1d])
    // +0x78 : m_flagB (byte)
    // +0x79 : m_flagC (byte)
    // +0x7A : m_flagA (byte)
    
    uint32_t m_index; // offset +0x70
    void* m_targetPointer; // offset +0x10
    uint32_t m_anotherCount; // offset +0x74
    bool m_flagB; // offset +0x78
    bool m_flagC; // offset +0x79
    bool m_flagA; // offset +0x7A

    void RebuildSceneData(); // 0x0095e490
};

void __fastcall CrimeScene::RebuildSceneData()
{
    // Reset index and copy default template
    this->m_index = 0;
    uint32_t* pTemplate = (uint32_t*)GetDefaultTemplate();
    uint32_t* pDest = (uint32_t*)this;
    for (int i = 0x1c; i != 0; i--) {
        *pDest++ = *pTemplate++;
    }

    // Attempt to resolve target data from global manager
    this->m_targetPointer = nullptr;
    if (g_pEntityManager != nullptr) {
        if (this->m_index < *(uint32_t*)(g_pEntityManager + 2)) { // manager->count
            int* pEntity = *(int**)(*(int*)(g_pEntityManager + 1) + this->m_index * 4);
            if (pEntity != nullptr && *pEntity != 0) {
                this->m_targetPointer = (void*)*(uint32_t*)(*pEntity + 0x70);
            }
        }
    }

    // Set flags
    this->m_flagA = true;          // +0x7A
    this->m_anotherCount = 0;      // +0x74
    this->m_flagB = false;         // +0x78
    this->m_flagC = false;         // +0x79

    // Free existing global list
    if (g_pGlobalList != nullptr) {
        FreeMemory(g_pGlobalList);
    }
    g_pGlobalList = nullptr;
    g_globalListCapacity = 0;

    // Rebuild global list from sub-objects of the referenced entity
    if (g_pEntityManager != nullptr) {
        uint32_t subCount = 0;
        int* pEntity = *(int**)(*(int*)(g_pEntityManager + 1) + this->m_index * 4);
        if (pEntity != nullptr) {
            subCount = *(uint32_t*)(pEntity + 2); // pEntity->subCount at +8
        }

        uint32_t currentCount = g_globalListCount; // initially 0
        uint32_t capacity = g_globalListCapacity;

        for (uint32_t i = 0; i < subCount; i++) {
            if (this->m_index < *(uint32_t*)(g_pEntityManager + 2)) {
                pEntity = *(int**)(*(int*)(g_pEntityManager + 1) + this->m_index * 4);
                if (pEntity != nullptr) {
                    int* pSub = *(int**)(*(int*)(pEntity + 1) + i * 4); // pEntity->subArray[i]
                    if (pSub != nullptr) {
                        uint32_t val1 = *(uint32_t*)(pSub + 0x17c / 4); // offset 0x17c
                        uint32_t val2 = *(uint32_t*)(pSub + 0x180 / 4); // offset 0x180

                        // Grow array if needed
                        if (currentCount == capacity) {
                            uint32_t newCapacity = capacity * 2;
                            if (newCapacity == 0) newCapacity = 1;
                            GrowGlobalArray(newCapacity);
                            capacity = g_globalListCapacity;
                        }

                        // Store pair
                        uint32_t idx = currentCount;
                        currentCount++;
                        uint32_t* pEntry = (uint32_t*)(g_pGlobalList + idx * 2); // each 8 bytes
                        if (pEntry != nullptr) {
                            *pEntry = val1;
                            pEntry[1] = val2;
                            capacity = g_globalListCapacity;
                        }
                    }
                }
            }
        }
    }
}