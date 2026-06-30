// FUNC_NAME: SomeGraphicsResource::createHandle
// Function at 0x005627a0 - Initializes a graphics resource handle with reference counting and scaling.
// Allocates a shared object, sets a 1.0f scaling factor, then allocates a 512-byte memory block and returns a processed handle.

#include <cstdint>

// Forward declarations of called functions (not implemented here)
void* allocateGraphicsObject(); // FUN_00562880
void initializeFramework(); // FUN_009f9620
void setObjectScaling(void* obj, float scale, float* outScaling); // FUN_009e44f0
uint32_t processScalingToUint(float* scaling); // FUN_009f4640
void* allocateMemory(uint32_t size, uint32_t tag); // FUN_00aa2680 (tag 0x2d = 45)
// TlsGetValue from windows.h

// External globals (likely screen dimensions or engine globals)
extern uint32_t DAT_00e2b118; // some constant
extern uint32_t DAT_00e2b1a4; // some other constant
extern uint32_t DAT_01139810; // TLS index

uint32_t createGraphicsResource(void)
{
    // Structure of the shared object (offset-based):
    // +0x00: pointer to a cleanup function (vtable or custom)
    // +0x04: short flag (maybe reference count or "has parent")
    // +0x06: short counter (decremented and triggers cleanup when zero)
    
    uint32_t* sharedObj = static_cast<uint32_t*>(allocateGraphicsObject());
    initializeFramework();
    
    // Store global constants (seemingly unused in this function)
    uint32_t local_34 = DAT_00e2b118;
    uint32_t local_40 = DAT_00e2b1a4;
    
    // Setup scaling operation buffer
    float scalingBuffer[1]; // 4 bytes
    // Will be filled by setObjectScaling
    
    // Copy constants to local variables (possibly for later extension)
    uint32_t local_c0 = 0;
    uint32_t local_bc = DAT_00e2b1a4;
    uint32_t local_b8 = 0;
    uint32_t local_b4 = 0;
    
    // Set scaling factor to 1.0f on the shared object
    setObjectScaling(sharedObj, 1.0f, scalingBuffer);
    
    // Placeholder for thread-local storage (TlsGetValue called but result unused)
    // Likely getting per-thread render state
    TlsGetValue(DAT_01139810);
    
    // Allocate a 512-byte block with tag 0x2d (45)
    void* memoryBlock = allocateMemory(0x200, 0x2d);
    *static_cast<uint16_t*>(memoryBlock) = 0x200; // store size at offset 0
    // Actually storing size at offset 4: reinterpret_cast<uint16_t*>(static_cast<char*>(memoryBlock) + 4) = 0x200
    *reinterpret_cast<uint16_t*>(static_cast<char*>(memoryBlock) + 4) = 0x200;
    
    // Process the scaling buffer into a return value (likely hash or handle)
    uint32_t returnValue = processScalingToUint(scalingBuffer);
    
    // Reference count / lifecycle management on sharedObj
    // Offset 4: short (maybe flag for "active")
    // Offset 6: short (counter - decremented, if becomes zero calls cleanup)
    int16_t* flagAtOffset4 = reinterpret_cast<int16_t*>(sharedObj + 1); // offset 4
    if (*flagAtOffset4 != 0)
    {
        int16_t* counterAtOffset6 = reinterpret_cast<int16_t*>(static_cast<char*>(sharedObj) + 6);
        *counterAtOffset6 -= 1;
        if (*counterAtOffset6 == 0)
        {
            // Call cleanup function from vtable / function pointer at offset 0
            void (*cleanupFunc)(int) = reinterpret_cast<void (*)(int)>(sharedObj[0]);
            cleanupFunc(1); // argument 1 might signal type of cleanup
        }
    }
    
    return returnValue;
}