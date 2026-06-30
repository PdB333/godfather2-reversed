//FUNC_NAME: BNKStreamManager::initialize

#include <cstring> // for memset

// Global allocator function pointer (likely from EARS memory system)
extern void* (*g_allocFunc)(size_t size, int flags);

// Constants
const uint32_t kDefaultValue = 0; // DAT_00e2b1a4

// Forward declarations of stream function callbacks
extern void FUN_005ad640(void);
extern void FUN_005ad970(void);
extern void FUN_005adb70(void);
extern void FUN_005adc90(void);
extern void FUN_005ade20(void);

// External initialization functions
extern void FUN_005a9870(void);
extern void FUN_0059c230(void* obj);
extern void FUN_005af060(void);

// Global state variables (renamed from DAT_*)
static uint32_t* g_smallMutex1;       // DAT_0119cbbc
static uint32_t* g_largeConfig;       // DAT_0119cbf0 (size 0x3c0)
static uint32_t* g_smallMutex2;       // DAT_0119cc0c
static uint32_t* g_streamBuffer1;     // DAT_0119cbb0 (size 0x4c)
static uint32_t* g_streamBuffer2;     // DAT_0119cbb8 (size 0x4c)
static uint32_t* g_streamObj1;        // DAT_0119cbc8 (size 0x50)
static uint32_t* g_streamObj2;        // DAT_0119cbc0 (size 0x50)
static uint32_t* g_streamObj3;        // DAT_0119cbc4 (size 0x50)
static void* g_streamObj4;            // DAT_0119cbcc (size 0x50)
static void* g_streamObj5;            // DAT_0119cbb4 (size 0x50)

// Additional globals set by this function
static float g_float1;                // _DAT_0119cbd0
static float g_float2;                // _DAT_0119cbd4
static float g_float3;                // _DAT_0119cbd8
static float g_float4;                // _DAT_0119cbdc
static int g_int1;                    // _DAT_0119cbe0
static int g_int2;                    // _DAT_0119cbe4
static int g_int3;                    // _DAT_0119cbe8
static int g_int4;                    // _DAT_0119cbec

// Structure for the 0x4c-byte stream buffer objects
struct StreamBuffer {
    uint32_t flags;      // +0x00
    uint16_t field4;     // +0x04
    uint16_t field6;     // +0x06
    uint32_t dataPtr;    // +0x08 (points to data area)
    char data[0x40];     // +0x0C (64 bytes)
};

// Structure for the 0x50-byte stream objects (with function pointer)
struct StreamObject {
    uint32_t flags;      // +0x00
    uint16_t field4;     // +0x04
    uint16_t field6;     // +0x06
    uint32_t dataPtr;    // +0x08
    char data[0x40];     // +0x0C
    void (*funcPtr)();   // +0x4C (callback)
};

// Helper to allocate and initialize a 4-byte mutex-like object
static uint32_t* allocateSmallMutex(uint32_t initialFlags, uint16_t field4Val, uint16_t field6Val, bool setBit15, bool setBit31)
{
    uint32_t* ptr = (uint32_t*)(*g_allocFunc)(4, 0);
    if (ptr) {
        *ptr = (*ptr & 0xffff8003) | initialFlags;
        *(uint16_t*)((int)ptr + 2) = 0;
        *ptr = *ptr & 0xffff7fff; // clear bit 15
        *(uint16_t*)((int)ptr + 2) = 0;
        if (setBit31) {
            *ptr = *ptr | 0x80000000;
        }
    }
    return ptr;
}

// Helper to allocate and initialize a 0x4c-byte stream buffer
static uint32_t* allocateStreamBuffer(uint32_t initialFlags, uint16_t field4Val, uint16_t field6Val, bool setBit15, bool setBit31)
{
    uint32_t* ptr = (uint32_t*)(*g_allocFunc)(0x4c, 0);
    if (ptr) {
        *ptr = (*ptr & 0xffff8017) | initialFlags;
        *(uint16_t*)((int)ptr + 2) = 0;
        *ptr = *ptr | 0x8000; // set bit 15
        *(uint16_t*)(ptr + 1) = field4Val; // offset 4
        *(uint16_t*)((int)ptr + 6) = field6Val; // offset 6
        ptr[2] = (uint32_t)(ptr + 3); // dataPtr points to data area
        memset(ptr + 3, 0, 0x40);
        *(uint16_t*)((int)ptr + 2) = 0;
        if (setBit31) {
            *ptr = *ptr | 0x80000000;
        }
    }
    return ptr;
}

// Helper to allocate and initialize a 0x50-byte stream object with a callback
static uint32_t* allocateStreamObject(uint32_t initialFlags, uint16_t field4Val, uint16_t field6Val, bool setBit15, bool setBit31, void (*callback)())
{
    uint32_t* ptr = (uint32_t*)(*g_allocFunc)(0x50, 0);
    if (ptr) {
        *ptr = (*ptr & 0xffff8009) | initialFlags;
        *(uint16_t*)((int)ptr + 2) = 0;
        *ptr = *ptr | 0x8000; // set bit 15
        *(uint16_t*)(ptr + 1) = field4Val; // offset 4
        *(uint16_t*)((int)ptr + 6) = field6Val; // offset 6
        ptr[2] = (uint32_t)(ptr + 3); // dataPtr
        memset(ptr + 3, 0, 0x40);
        ptr[0x13] = (uint32_t)callback; // store function pointer at offset 0x4c
    }
    *(uint16_t*)((int)ptr + 2) = 0;
    *ptr = *ptr | 0x80000000;
    return ptr;
}

void BNKStreamManager::initialize()
{
    // Allocate first small mutex (flags 0x3)
    g_smallMutex1 = allocateSmallMutex(3, 0, 0, false, true);

    // Allocate large configuration structure (0x3c0 bytes)
    g_largeConfig = (uint32_t*)(*g_allocFunc)(0x3c0, 0x10);
    if (g_largeConfig) {
        g_largeConfig[0] = kDefaultValue;
        g_largeConfig[1] = kDefaultValue;
        g_largeConfig[2] = kDefaultValue;
        g_largeConfig[3] = kDefaultValue;
        g_largeConfig[4] = 0;
        g_largeConfig[5] = 0;
        g_largeConfig[6] = 0;
        g_largeConfig[7] = 0;
        g_largeConfig[0x88] = kDefaultValue; // offset 0x220
        g_largeConfig[0x89] = 0;
        g_largeConfig[0x8a] = 0;
        g_largeConfig[0x8b] = kDefaultValue;
        g_largeConfig[0x8c] = 0;
        g_largeConfig[0x8d] = 0;
        g_largeConfig[0xee] = 0;
        g_largeConfig[0xef] = 0;
    }

    // Allocate second small mutex (flags 0xb)
    g_smallMutex2 = allocateSmallMutex(0xb, 0, 0, true, true);

    // Allocate first stream buffer (flags 0x17, field4=4)
    g_streamBuffer1 = allocateStreamBuffer(0x17, 4, 0, true, true);

    // Allocate second stream buffer (flags 0x19, field4=4)
    g_streamBuffer2 = allocateStreamBuffer(0x19, 4, 0, true, true);

    // Initialize some subsystem
    FUN_005a9870();

    // Set default float/int values
    g_float1 = kDefaultValue;
    g_float2 = kDefaultValue;
    g_float3 = kDefaultValue;
    g_float4 = kDefaultValue;
    g_int1 = 0;
    g_int2 = 0;
    g_int3 = 0;
    g_int4 = 0;

    // Initialize part of the large config (overlapping fields)
    // Note: These are likely part of a larger struct at g_largeConfig
    *(uint32_t*)((int)g_largeConfig + 0x00) = kDefaultValue;
    *(uint32_t*)((int)g_largeConfig + 0x04) = 0;
    *(uint32_t*)((int)g_largeConfig + 0x0C) = 0;
    *(uint32_t*)((int)g_largeConfig + 0x10) = kDefaultValue;
    *(uint32_t*)((int)g_largeConfig + 0x14) = 0;
    *(uint32_t*)((int)g_largeConfig + 0x18) = 0;

    // Allocate four stream objects with different callbacks
    g_streamObj1 = allocateStreamObject(9, 4, 0, true, true, FUN_005ad640);
    g_streamObj2 = allocateStreamObject(9, 4, 0, true, true, FUN_005ad970);
    g_streamObj3 = allocateStreamObject(9, 4, 0, true, true, FUN_005adb70);

    // Fourth stream object uses a different creation path (via FUN_005a86f0)
    {
        void* mem = (*g_allocFunc)(0x50, 0);
        if (mem) {
            g_streamObj4 = FUN_005a86f0(FUN_005adc90);
        } else {
            g_streamObj4 = 0;
        }
    }
    FUN_0059c230(g_streamObj4);

    // Fifth stream object
    {
        void* mem = (*g_allocFunc)(0x50, 0);
        if (mem) {
            g_streamObj5 = FUN_005a86f0(FUN_005ade20);
        } else {
            g_streamObj5 = 0;
        }
    }
    FUN_0059c230(g_streamObj5);

    // Set additional globals
    _DAT_01221f20 = 0;
    _DAT_01221f28 = 0;

    // Final initialization step
    FUN_005af060();
}