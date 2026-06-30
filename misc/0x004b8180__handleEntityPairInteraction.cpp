// FUNC_NAME: handleEntityPairInteraction

#include <cstdint>

// External globals
extern uint32_t DAT_01223398;
extern uint32_t DAT_012233a8;
extern void* PTR_FUN_00e35950;  // function pointer

// Forward declarations of called functions
void FUN_0042d2c0(void* context, uint32_t param);
void FUN_0049d0c0(void* callbackData, void* label);
void FUN_0049feb0();
void FUN_0042cfa0(void* context, uint32_t entity2, uint32_t valFromEntity1,
                  void* bufferFromEntity1, char* stackBuffer,
                  uint16_t shortFlag, uint32_t uintFlag);

// Entity data structure (partial, based on used offsets)
struct EntityData {
    uint8_t pad_0x00[0xa0];
    uint32_t field_0xa0;       // +0xa0
    uint8_t pad_0xa4[0x0e];   // up to +0xb2
    uint8_t flags_0xb2;        // +0xb2, bit0
    uint8_t pad_0xb3[0x09];    // +0xac for second entity
    uint8_t flags_0xac;        // +0xac, bit1 (second entity)
    uint8_t pad_0xad[0x03];    // +0xb0
    uint16_t short_0xb0;       // +0xb0
    uint32_t uint_0xb4;        // +0xb4
};

void handleEntityPairInteraction(uint32_t id1, uint32_t id2,
                                 uint32_t param3, uint32_t param4) {
    // Get the manager instance (assumed to be a global singleton)
    uint32_t managerBase = *(uint32_t*)(DAT_01223398 + 8);
    uint32_t *bucketArray = *(uint32_t**)(managerBase + 4);
    uint32_t bucketCount = *(uint32_t*)(managerBase + 8);

    // Lookup entity1 by id1
    uint32_t entity1Addr = 0;
    {
        uint32_t* entry = bucketArray + (id1 % bucketCount) * 4;
        while (*entry) {
            uint32_t* next = (uint32_t*)*entry;
            if (*next == id1) {
                if ((next != nullptr) && (next + 1 != nullptr)) {
                    entity1Addr = *(next + 1); // data pointer
                }
                break;
            }
            entry = (uint32_t*)next[2]; // next entry
        }
    }

    // Lookup entity2 by id2
    uint32_t entity2Addr = 0;
    {
        uint32_t* entry = bucketArray + (id2 % bucketCount) * 4;
        while (true) {
            if (*entry == 0) {
                entity2Addr = 0;
                break;
            }
            uint32_t* entryData = (uint32_t*)*entry;
            if (*entryData == id2) {
                if ((entryData != nullptr) && (entryData + 1 != nullptr)) {
                    entity2Addr = *(entryData + 1);
                }
                break;
            }
            entry = (uint32_t*)entryData[2];
        }
    }

    EntityData* ent1 = (EntityData*)entity1Addr;
    EntityData* ent2 = (EntityData*)entity2Addr;
    uint32_t valFromEnt1 = ent1->field_0xa0;

    // Determine whether to perform additional actions
    bool doTransition = false;
    if (((ent1->flags_0xb2 & 1) != 0) && ((ent2->flags_0xac & 2) != 0)) {
        doTransition = true;
        FUN_0042d2c0(*(void**)(DAT_012233a8 + 4), valFromEnt1);
    }

    // Setup callback data structure (pushed on stack)
    void* callbackData[3];
    callbackData[0] = PTR_FUN_00e35950;
    callbackData[1] = (void*)param3;
    callbackData[2] = (void*)param4;

    // Conditionally call the callback dispatcher
    if ((ent1->flags_0xb2 & 1) != 0) {
        // always call when bit0 set
        FUN_0049d0c0(callbackData, (void*)0x0049cd60);
    } else {
        // call only if the function pointer returns false
        bool (*funcPtr)() = (bool (*)())PTR_FUN_00e35950;
        if (!funcPtr()) {
            FUN_0049d0c0(callbackData, (void*)0x0049cd60);
        }
    }

    // If we entered transition mode, complete the operation
    if (doTransition) {
        FUN_0049feb0();
        char stackBuffer[28]; // auStack_20
        FUN_0042cfa0(
            *(void**)(DAT_012233a8 + 4),
            (uint32_t)ent2,
            valFromEnt1,
            (void*)((uint8_t*)ent1 + 0x10), // buffer from ent1
            stackBuffer,
            ent1->short_0xb0,
            ent2->uint_0xb4
        );
    }
}