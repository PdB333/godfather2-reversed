// Xbox PDB: EARS_Modules_BaseServiceManager_BaseServiceManager
// FUNC_NAME: TickSource::TickSource
// Function address: 0x008f7260
// Role: Constructor for a tick source object that registers for linked and unlinked tick messages.
// Allocates memory for tick data (elementCount * 16 bytes), stores the count, and calls initialization.

#include <cstdint>

// Forward declarations for functions called (placeholder names)
extern void* AllocateMemory(uint32_t size);                          // FUN_009c8e80
extern void InitializeTickData(int32_t elementCount);                // FUN_008f71d0
extern void RegisterStringMessage(void* messageManager, const char* str); // FUN_00408240

// Global message manager pointer (likely singleton)
extern void* gMessageManager; // DAT_0112a580

// VTable symbol (set by linker)
extern void* TICK_SOURCE_VTABLE; // PTR_FUN_00d81218

// Offset definitions
// +0x00: vtable pointer
// +0x04: pointer to allocated tick data array
// +0x08: current index / state (initialized to 0)
// +0x0C: number of elements (elementCount)

class TickSource {
public:
    // __thiscall constructor
    TickSource* __thiscall TickSource(int32_t elementCount) {
        // Store this instance as global tick source
        gMessageManager = this; // DAT_0112a580 = param_1

        // Set vtable
        this->vtable = &TICK_SOURCE_VTABLE; // *param_1 = &PTR_FUN_00d81218

        // Allocate memory for tick data: each element is 16 bytes
        this->tickData = (uint8_t*)AllocateMemory(elementCount << 4); // param_1[1] = uVar1

        // Initialize tick index to 0
        this->currentIndex = 0; // param_1[2]

        // Store element count
        this->elementCount = elementCount; // param_1[3]

        // Initialize tick data (implementation details unknown)
        InitializeTickData(elementCount);

        // Register for linked and unlinked tick messages
        RegisterStringMessage(&gMessageManager, "iMsgTickLinked");   // DAT_0112fe5c
        RegisterStringMessage(&gMessageManager, "iMsgTickUnLinked"); // DAT_0112fe54

        return this;
    }

private:
    // Member variables (based on offsets from this pointer)
    void** vtable;         // +0x00
    uint8_t* tickData;     // +0x04
    int32_t currentIndex;  // +0x08
    int32_t elementCount;  // +0x0C
};