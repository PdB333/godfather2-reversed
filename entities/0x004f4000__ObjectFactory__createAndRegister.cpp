// FUNC_NAME: ObjectFactory::createAndRegister
// Reconstructed from 0x004f4000: Factory function that allocates an object (0x28 bytes) from a pool, initializes its vtable and fields from parameters, then inserts it into a hash table keyed by param_1 (likely a resource ID).

#include <cstdint>

// Forward declarations of external helper functions
void* eaAlloc(uint32_t size, uint32_t* allocParams);    // FUN_009c8ed0
void hashTableInsert(uint32_t* keyRef, void** objRef, uint32_t hashIndex); // FUN_00423cf0

// Global data referenced (addresses from binary)
extern uint32_t DAT_00e2b1a4;                    // some global constant or pointer
extern uint32_t DAT_01223398;                    // pointer to hash table metadata
extern void* PTR_LAB_00e37704;                  // vtable pointer for the created object

// Structure fields for the object (size 0x28 = 40 bytes)
struct CreatedObject {
    void* vtable;                                // +0x00
    uint32_t field_04;                           // +0x04 (from param_3)
    uint32_t field_08;                           // +0x08 (from param_4)
    uint32_t field_0C;                           // +0x0C (from param_5)
    void* sourceObj;                             // +0x10 (param_2)
    uint32_t field_14;                           // +0x14 (initialized to 0)
    uint32_t field_18;                           // +0x18 (initialized to 0)
    uint32_t field_1C;                           // +0x1C (from DAT_00e2b1a4)
    uint32_t field_20;                           // +0x20 (from sourceObj+0x20)
};

void ObjectFactory::createAndRegister(uint32_t key, void* sourceObj, uint32_t param3, uint32_t param4, uint32_t param5)
{
    // Allocation flags: type = 2, alignment = 0x10, unknown = 0
    uint32_t allocParams[3] = {2, 0x10, 0};

    // Allocate memory for the object
    CreatedObject* obj = (CreatedObject*)eaAlloc(0x28, allocParams + 1); // note: allocParams+1? actually the decompiled shows &local_10[1] = allocParams+1

    if (obj == nullptr) {
        // Allocation failed — the original code sets puVar2 to null, but still proceeds? Probably a no-op
        obj = nullptr;
    } else {
        // Initialize object fields
        obj->vtable    = &PTR_LAB_00e37704;
        obj->field_04  = param3;
        obj->field_08  = param4;
        obj->field_0C  = param5;
        obj->sourceObj = sourceObj;
        obj->field_14  = 0;
        obj->field_18  = 0;
        obj->field_1C  = DAT_00e2b1a4;          // some global value
        obj->field_20  = *(uint32_t*)((uint8_t*)sourceObj + 0x20); // read offset 0x20 from source object
    }

    // Compute hash index from the key (param_1)
    // Hash table metadata: DAT_01223398 contains a pointer to a struct; offset 8 contains pointer to size; offset 8 of that size is the table size divisor
    uint32_t tableSize = *(uint32_t*)(*(uint32_t*)(DAT_01223398 + 8) + 8);
    uint32_t hashIndex = key % tableSize;

    // Insert the object into the hash table keyed by param_1
    // keyRef = local_10 (which is address of key on stack)
    uint32_t keyCopy = key;
    void* objPtr = obj;                         // address of the object pointer (not the object itself)
    hashTableInsert(&keyCopy, &objPtr, hashIndex);
}