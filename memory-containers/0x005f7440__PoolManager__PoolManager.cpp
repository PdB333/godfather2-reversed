// FUNC_NAME: PoolManager::PoolManager
// Address: 0x005f7440
// Role: Constructor for a dual-pool manager with two arrays of fixed-size elements.
// Initializes sub-objects at offsets +0x34 and +0x54, allocates two pools (element sizes 0x14 and 0x50),
// and stores a lookup structure. Sets a global singleton pointer.

#include <cstdint>

// Forward declarations of external functions
extern void* FUN_004265d0(void* buffer, void* allocator); // Reads data from allocator?
extern void FUN_005f8f90(void* subObj); // Initialize sub-object at +0x34
extern void FUN_005f9190(void* subObj); // Initialize sub-object at +0x54
extern void* FUN_004abe90(void* base, uint32_t size, uint32_t elemSize, uint32_t alignment); // Allocate/initialize array
extern void* FUN_005f73d0(uint32_t count); // Create lookup structure for second pool

// Global singleton pointer
extern void* g_poolManager; // DAT_01223520

// Vtable for PoolManager (external symbol)
extern void* PTR_FUN_00e407bc;

class PoolManager {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Unknown fields at +0x04, +0x08, +0x0C (initialized to 0)
    uint32_t field_04;
    uint32_t field_08;
    uint32_t field_0C;

    // Allocator interface (pointer to object with virtual functions)
    void* allocator; // +0x10 (param_1[4])

    // Pool sizes
    uint32_t pool1Count; // +0x14 (param_1[5])
    uint32_t pool2Count; // +0x18 (param_1[6])

    // Additional parameters
    uint32_t param6; // +0x1C (param_1[7])
    uint32_t param5; // +0x20 (param_1[8])
    uint32_t param7; // +0x24 (param_1[9])

    // Allocated arrays
    void* pool1Array; // +0x28 (param_1[10])
    void* pool2Array; // +0x2C (param_1[11])

    // Lookup structure for pool2
    void* pool2Lookup; // +0x30 (param_1[12])

    // Sub-objects (size unknown, likely classes)
    // Offset +0x34 (param_1+0xd) - initialized by FUN_005f8f90
    uint8_t subObj1[12]; // placeholder size (3 * 4 bytes from local_14 usage)
    // Offset +0x54 (param_1+0x15) - initialized by FUN_005f9190
    uint8_t subObj2[12]; // placeholder size

    // Constructor
    PoolManager(void* alloc, uint32_t count1, uint32_t count2,
                uint32_t p5, uint32_t p6, uint32_t p7) {
        // Set global singleton
        g_poolManager = this;

        // Set vtable
        vtable = &PTR_FUN_00e407bc;

        // Initialize unknown fields to 0
        field_04 = 0;
        field_08 = 0;
        field_0C = 0;

        // Temporary buffer for reading from allocator
        uint32_t buffer[3] = {0, 0, 0};

        // First sub-object initialization
        {
            void* tempPtr = alloc;
            // Call virtual function at offset 8 on allocator (likely beginRead?)
            (*(void (**)(void*))(*(uint32_t*)alloc + 8))(alloc);
            int32_t result = (int32_t)FUN_004265d0(buffer, alloc);
            FUN_005f8f90(&subObj1);
            if (result != 0) {
                // Call virtual function at offset 4 on allocator (likely free?)
                (*(void (**)(void*, int32_t))(*(uint32_t*)alloc + 4))(alloc, result);
            }
            // Call virtual function at offset 12 on allocator (likely endRead?)
            (*(void (**)(void*))(*(uint32_t*)alloc + 12))(alloc);
        }

        // Second sub-object initialization
        {
            void* tempPtr = alloc;
            (*(void (**)(void*))(*(uint32_t*)alloc + 8))(alloc);
            int32_t result = (int32_t)FUN_004265d0(buffer, alloc);
            FUN_005f9190(&subObj2);
            if (result != 0) {
                (*(void (**)(void*, int32_t))(*(uint32_t*)alloc + 4))(alloc, result);
            }
            (*(void (**)(void*))(*(uint32_t*)alloc + 12))(alloc);
        }

        // Store parameters
        allocator = alloc;
        pool1Count = count1;
        pool2Count = count2;
        param7 = p7;
        param6 = p6;
        param5 = p5;

        // Allocate first pool (element size 0x14)
        {
            uint32_t size = count1 * 0x14 + 0x20;
            uint32_t localBuffer[3] = {2, 4, 0}; // alignment? flags?
            void* mem = (*(void* (*)(void*, uint32_t, uint32_t*))(*(uint32_t*)alloc + 0))(alloc, size, localBuffer);
            if (mem != 0) {
                pool1Array = FUN_004abe90((uint8_t*)mem + 0x20, count1 * 0x14, 0x14, 4);
            } else {
                pool1Array = 0;
            }
        }

        // Allocate second pool (element size 0x50)
        {
            uint32_t size = count2 * 0x50 + 0x20;
            uint32_t localBuffer[3] = {2, 4, 0}; // alignment? flags?
            void* mem = (*(void* (*)(void*, uint32_t, uint32_t*))(*(uint32_t*)alloc + 0))(alloc, size, localBuffer);
            if (mem != 0) {
                pool2Array = FUN_004abe90((uint8_t*)mem + 0x20, count2 * 0x50, 0x50, 4);
            } else {
                pool2Array = 0;
            }
        }

        // Create lookup structure for second pool
        pool2Lookup = FUN_005f73d0(pool2Count);
    }
};