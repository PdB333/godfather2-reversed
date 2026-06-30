// FUNC_NAME: createObjectAndRegisterInHashTable

// Structure for the registered object (size 0x2c = 44 bytes)
struct RegisteredObject
{
    void** vtable;          // +0x00
    uint field1;            // +0x04
    uint field2;            // +0x08
    uint field3;            // +0x0C
    uint field4;            // +0x10 (always 0)
    uint field5;            // +0x14
    uint field6;            // +0x18
    uint field7;            // +0x1C
    uint field8;            // +0x20 (always 0)
    uint field9;            // +0x24 (always 0)
    uint field10;           // +0x28 (always 0)
};

// Forward declarations for helper functions (Ghidra symbols)
extern void* AllocEaMemory(uint size, uint* tag);              // FUN_009c8ed0
extern void InsertIntoHashTable(uint* key, void** value, uint bucketIndex); // FUN_00423cf0

// Global hash table manager pointer (DAT_01223398)
extern uint8* g_pHashTableManager;

void createObjectAndRegisterInHashTable(uint id, uint param2, uint param3, uint param4,
                                         uint param5, uint param6, uint param7)
{
    // Allocation tag: {poolType=2, poolSize=0x10, flags=0}
    uint allocTag[3] = {2, 0x10, 0};

    // Allocate object memory (0x2c bytes)
    RegisteredObject* obj = (RegisteredObject*)AllocEaMemory(0x2c, allocTag);

    if (obj != nullptr)
    {
        // Initialize object fields
        // Set vtable pointer (class-specific virtual method table)
        obj->vtable = (void**)&PTR_FUN_00e37798;
        obj->field1 = param3;
        obj->field2 = param4;
        obj->field3 = param5;
        obj->field5 = param2;
        obj->field4 = 0;
        obj->field6 = param6;
        obj->field7 = param7;
        obj->field8 = 0;
        obj->field9 = 0;
        obj->field10 = 0;
    }

    // Hash table entry: key = id, value = obj pointer
    uint key = id;
    void* value = obj;

    // Compute bucket index from global hash table structure
    // Structure at g_pHashTableManager + 0x08 points to a sub-structure
    // whose offset +0x08 contains the bucket count
    uint bucketCount = *(uint*)(*(uint*)(g_pHashTableManager + 0x08) + 0x08);
    uint bucketIndex = id % bucketCount;

    // Insert (key, value) into the hash table
    InsertIntoHashTable(&key, &value, bucketIndex);
}