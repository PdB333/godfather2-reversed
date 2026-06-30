// FUNC_NAME: ObjectFactory::createAndRegister

void ObjectFactory::createAndRegister(uint32_t key, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6, uint32_t param7)
{
    uint32_t allocInfo[4]; // local_10
    allocInfo[1] = 2;      // alignment?
    allocInfo[2] = 0x10;   // size hint?
    allocInfo[3] = 0;

    // Allocate 0x34 (52) bytes from memory pool (likely EARS allocator)
    uint32_t* newObj = (uint32_t*)FUN_009c8ed0(0x34, allocInfo + 1);
    if (newObj == nullptr)
    {
        newObj = nullptr;
    }
    else
    {
        // Initialize object fields (vtable pointer at offset 0)
        newObj[0] = &PTR_FUN_00e37e0c;   // vtable pointer
        newObj[1] = param2;               // +0x04
        newObj[2] = param6;               // +0x08
        newObj[3] = param7;               // +0x0C
        newObj[4] = param3;               // +0x10
        newObj[5] = param4;               // +0x14
        newObj[6] = param5;               // +0x18
        newObj[7] = 0;                    // +0x1C (unused/reserved)
    }

    // Calculate hash table bucket index
    // DAT_01223398 points to a global structure; at offset +8 is a pointer,
    // then deref +8 gives the hash table size.
    uint32_t bucketIndex = key % *(uint32_t*)(*(int32_t*)(DAT_01223398 + 8) + 8);

    // Insert object into hash table: key is the original param_1 (now local_10[0]),
    // second param is address of newObj pointer, third is bucket index.
    uint32_t keyLocal = key; // local_10[0] = key
    FUN_00423cf0(&keyLocal, &newObj, bucketIndex);
}