// FUNC_NAME: SimObjectManager::registerObject
#include <cstdint>

// Forward declarations
struct SimObjectHeader;
struct SimObjectVTable;

// Global symbols (from game data)
extern SimObjectVTable* g_SimObjectVTable; // PTR_FUN_00e37ae0
extern uint32_t g_GlobalValue;              // DAT_00e2b1a4
extern void* g_EngineContext;              // DAT_01223398

// Memory allocation (size, mode array)
void* engineAlloc(uint32_t size, uint32_t* modeFlags);

// Hash table insert (key, pointer to object pointer, bucket index)
void hashTableInsert(uint32_t key, void** objPtr, uint32_t bucketIndex);

// Structure of the allocated object (40 bytes)
struct SimObject {
    SimObjectVTable* vtable;  // +0x00
    uint32_t field_04;        // +0x04  param2
    uint32_t field_08;        // +0x08  param4
    uint32_t field_0C;        // +0x0C  param5
    uint32_t field_10;        // +0x10  param3
    uint32_t field_14;        // +0x14  param6
    uint32_t field_18;        // +0x18  g_GlobalValue
    uint32_t field_1C;        // +0x1C  zero
    uint32_t field_20;        // +0x20  zero
    uint32_t field_24;        // +0x24  zero
};

// Static method: create and register a SimObject with given key and data
void SimObjectManager::registerObject(uint32_t key,
                                      uint32_t param2,
                                      uint32_t param3,
                                      uint32_t param4,
                                      uint32_t param5,
                                      uint32_t param6)
{
    // Allocation mode: flags = {2, 0x10, 0}
    uint32_t allocFlags[3] = {2, 0x10, 0};

    // Allocate memory for the object (size 0x28 = 40 bytes)
    SimObject* obj = static_cast<SimObject*>(engineAlloc(sizeof(SimObject), &allocFlags[1]));

    if (obj != nullptr) {
        // Initialize the object
        obj->vtable   = g_SimObjectVTable;
        obj->field_04 = param2;
        obj->field_08 = param4;
        obj->field_0C = param5;
        obj->field_10 = param3;
        obj->field_14 = param6;
        obj->field_18 = g_GlobalValue;
        obj->field_1C = 0;
        obj->field_20 = 0;
        obj->field_24 = 0;
    }

    // Compute bucket index for hash table
    uint32_t* contextBase = *reinterpret_cast<uint32_t**>(static_cast<uint8_t*>(g_EngineContext) + 8);
    uint32_t bucketCount  = *(contextBase + 2); // offset 8 from contextBase (since contextBase is uint32*, +2 = 8 bytes)
    uint32_t bucketIndex  = key % bucketCount;

    // Insert the object pointer into the hash table, keyed by 'key'
    void* objPtr = obj;
    hashTableInsert(key, &objPtr, bucketIndex);
}