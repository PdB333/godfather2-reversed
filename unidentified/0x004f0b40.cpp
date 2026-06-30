// FUN_004f0b40: EventManager::insertEventObject
struct EventObject {
    void* vtable;               // +0x00 - pointer to vtable (PTR_LAB_00e37438)
    void* keyPtr;               // +0x04 - original param_1 pointer used as key
    uint32_t someValue1;        // +0x08 - param_6
    uint32_t someValue2;        // +0x0C - param_7
    void* someData1;            // +0x10 - param_3
    void* someData2;            // +0x14 - param_4
    void* someData3;            // +0x18 - param_5
};

// Allocation tags: 2 = type, 0x10 = alignment, 0 = flags
struct AllocTag {
    uint32_t type;
    uint32_t alignment;
    uint32_t flags;
};

// Function pointers for allocator and hash table insertion
extern EventObject* earAllocAligned(uint32_t size, AllocTag* tag);
extern void hashTableInsert(uint32_t* keyArray, EventObject** objectPtr, uint32_t bucketIndex);
// Global data for hash table bucket count
// DAT_01223398 + 8 points to an int containing the number of buckets
extern uint32_t DAT_01223398;

void __fastcall EventManager::insertEventObject(
    void* param_1,      // key pointer, cast to uint for hashing
    void* param_2,      // stored at +0x04
    void* param_3,      // stored at +0x10
    void* param_4,      // stored at +0x14
    void* param_5,      // stored at +0x18
    uint32_t param_6,   // stored at +0x08
    uint32_t param_7    // stored at +0x0C
)
{
    AllocTag tag = {2, 0x10, 0};      // allocation parameters: type=2, alignment=16, flags=0
    EventObject* obj = earAllocAligned(sizeof(EventObject), &tag);
    if (obj != nullptr) {
        obj->vtable = (void*)0x00e37438;    // vtable address (PTR_LAB_00e37438)
        obj->keyPtr = param_2;
        obj->someValue1 = param_6;
        obj->someValue2 = param_7;
        obj->someData1 = param_3;
        obj->someData2 = param_4;
        obj->someData3 = param_5;
    }

    uint32_t key = (uint32_t)param_1;
    uint32_t bucketCount = *(uint32_t*)(*(int32_t*)(DAT_01223398 + 8) + 8); // number of hash buckets
    uint32_t bucketIndex = key % bucketCount;

    hashTableInsert(&key, &obj, bucketIndex);
}