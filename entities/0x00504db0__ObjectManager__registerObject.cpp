// FUNC_NAME: ObjectManager::registerObject

// Address: 0x00504db0
// Registers an object with a given ID in a global hash table.
// Allocates memory (0xA0 bytes), constructs object via FUN_005047f0, then inserts into table keyed by ID.
// Uses global at DAT_01223398 (likely pointer to table descriptor +8 offset is pointer to bucket array, +8 offset is bucket count).
// param_1 (uint) is the ID key.
// param_2..param_9 are constructor arguments for the object.

void ObjectManager::registerObject(uint id, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    uint allocParams[4];         // local_18
    void *newObj;                // local_1c

    allocParams[1] = 0x2;        // allocation flags (e.g., use pool?)
    allocParams[2] = 0x10;       // alignment hint (16 bytes)
    allocParams[3] = 0;          // reserved

    // Allocate 0xA0 bytes for the object
    void *mem = FUN_009c8ed0(0xA0, &allocParams[1]); // allocation function
    if (mem == (void *)0x0)
    {
        newObj = (void *)0x0;
    }
    else
    {
        // Construct the object in the allocated memory
        newObj = FUN_005047f0(mem, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    allocParams[0] = id;                             // store the ID

    // Compute bucket index from global table's bucket count
    // DAT_01223398 points to a table descriptor; +0x8 pointer to bucket array; +0x8 bucket count (uint)
    uint bucketCount = *(uint *)(*(int *)(DAT_01223398 + 8) + 8);
    uint bucketIndex = id % bucketCount;

    // Insert the object pointer into the table keyed by ID
    FUN_00423cf0(allocParams, &newObj, bucketIndex);
}