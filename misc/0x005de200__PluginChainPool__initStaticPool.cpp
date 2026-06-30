// FUNC_NAME: PluginChainPool::initStaticPool
// Address: 0x005de200 (EA EARS Engine Pool Initialization)

struct PluginChainPoolHeader {
    void** vtbl;           // +0x00
    void*  nextPool;       // +0x04 (linked list pointer)
    char*  name;           // +0x08
    int    elementSize;    // +0x0C (0x2C for first pool, 0x2C for second)
    int    alignment;      // +0x10 (4 or 1)
    int    numElements;    // +0x14 (8 for first, 0x1E for second)
    int    elementsPerBlock;// +0x18 (0x2C?)
    int    poolSize;       // +0x1C (0x50)
    int    blockSize;      // +0x20 (0x2C)
    int    flags;          // +0x24 (1 = initialized? )
    void*  poolData;       // +0x28 (self pointer for first block)
    char*  name2;          // +0x2C (same string)
    int    field30;        // +0x30 (0)
    int    field34;        // +0x34 (0)
    int    field38;        // +0x38 (0)
    int    elementCount;   // +0x3C (30 for second)
    int    field40;        // +0x40 (0)
    int    elementAlignment;//+0x44 (4)
    int    field48;        // +0x48 (0)
    int    field4C;        // +0x4C (0)
    void** vtbl2;          // +0x50 (second vtable, &PTR_FUN_00e3f2d0)
    int    poolSize2;      // +0x54 (0x50)
    int    poolSize3;      // +0x58 (0x50)
};

// Global static pointer used for pool chaining
extern PluginChainPoolHeader* g_pPluginChainPoolHeader; // DAT_012054b8

void PluginChainPool::initStaticPool(void) {
    PluginChainPoolHeader* pool = g_pPluginChainPoolHeader; // In reality unaff_EDI comes from some global or static allocation

    // Initialize first pool (PluginChainPool instance 1)
    pool->vtbl           = &PTR_FUN_00e3f2c8;            // +0x00
    pool->nextPool       = DAT_012054b8;                  // +0x04 (store previous global value)
    pool->name           = "PluginChainPool";              // +0x08
    pool->elementSize    = 0x2C;                           // +0x0C
    pool->alignment      = 4;                              // +0x10
    pool->numElements    = 8;                              // +0x14
    pool->elementsPerBlock = 0x2C;                         // +0x18
    pool->poolSize       = 0x2C;                           // +0x1C? Actually offset 0x0C? Let's re-align...
    // But the decompiled offsets are based on int* indexing. We'll use correct struct offsets below.

    // In the original code, assignments are done with int* increments.
    // To match exactly, we reinterpret as int array:
    int* data = (int*)pool;

    data[0]  = (int)&PTR_FUN_00e3f2c8;      // vtbl
    data[1]  = DAT_012054b8;                 // next pool pointer
    data[2]  = (int)"PluginChainPool";       // name
    data[6]  = 8;                            // element count (8)
    data[8]  = 4;                            // alignment
    data[3]  = 0;                            // ?
    data[4]  = 0;
    data[5]  = 0;
    data[7]  = 0;                            // ?
    data[0xC]= 0;
    data[0xD]= 0;
    data[0xB]= 0x2C;                         // element size (44)
    data[10] = 0x2C;                         // block size (44)
    data[9]  = 1;                            // initialized flag
    data[0x17]= 1;                           // another flag
    data[0xF]= (int)pool;                    // self pointer
    data[0x10]= (int)"PluginChainPool";      // name copy
    data[0x11]= 0;
    data[0x12]= 0;
    data[0x13]= 0;
    data[0x14]= 0x1E;                        // 30 (element count for second pool)
    data[0x15]= 0;
    data[0x16]= 4;                           // alignment for second pool
    data[0x1A]= 0;
    data[0x1B]= 0;
    data[0xE] = (int)&PTR_FUN_00e3f2d0;     // second vtable (pointer to vtable)
    data[0x19]= 0x50;                        // 80 (pool size?)
    data[0x18]= 0x50;                        // 80

    // Update global pointer to point to the second pool (after first 0x1C ints = 0x70 bytes)
    g_pPluginChainPoolHeader = &data[0x1C];  // DAT_012054b8 = unaff_EDI + 0x1c

    // Set up second pool's fields (at offset 0x1C)
    data[0x1D] = (int)(pool + 0xE);          // pointer to element 0xE of first pool
    data[0x25] = 1;                          // flag
    data[0x1E] = (int)"PluginChainPool";     // name
    data[0x1F] = 0;
    data[0x20] = 0;
    data[0x21] = 0;
    data[0x22] = 100;                        // maybe max allocations
    data[0x23] = 0;
    data[0x24] = 4;                          // alignment
    data[0x27] = 0x30;                       // 48
    data[0x28] = 0;
    data[0x29] = 0;
    data[0x26] = 0x30;                       // 48

    // Set vtable for second pool
    *(void**)g_pPluginChainPoolHeader = (void*)&PTR_FUN_00e3f2d8; // *DAT_012054b8 = &PTR_FUN_00e3f2d8

    data[0x2A] = 0;
    data[0x2B] = 0;
    data[0x2C] = 0;

    // Call additional initialization (might register pools, etc.)
    FUN_005e1730();
}