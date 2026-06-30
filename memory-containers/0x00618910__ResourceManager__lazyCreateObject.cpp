// FUNC_NAME: ResourceManager::lazyCreateObject
// Address: 0x00618910
// This function lazily creates a resource object from a pool. It takes an index in EAX (fastcall-like) and checks if the corresponding descriptor has a handle; if not, it calls the creation function.

// Global pool of resource descriptors, each 0x38 bytes.
// Base address: 0x011a0f28
struct ResourceDescriptor {
    uint8_t unknown_0[0x1];   // +0x00
    uint8_t flag;             // +0x01 (used as argument to creation)
    uint16_t subtype1;        // +0x02
    uint16_t subtype2;        // +0x04
    uint8_t pad_6[0x6];       // +0x06 to +0x0B
    uint32_t type;            // +0x0C
    uint8_t pad_10[0x10];     // +0x10 to +0x1B
    uint32_t handle;          // +0x1C (0 if not yet created)
};

// Forward declaration of the creation function (address 0x00606c80)
// Returns a handle (uint32) for the created object.
uint32_t createResource(uint32_t arg1, uint32_t type, uint16_t subtype1, uint16_t subtype2, uint8_t flag, int32_t parent);

void __fastcall lazyCreateObject(uint32_t index) {
    ResourceDescriptor* desc;

    // Validate index against pool size (0x1000 entries)
    if (index < 0x1000) {
        desc = (ResourceDescriptor*)((uint8_t*)0x011a0f28 + index * sizeof(ResourceDescriptor));
    } else {
        desc = nullptr;
    }

    // If descriptor is valid and handle not yet created, create it
    if (desc != nullptr && desc->handle == 0) {
        uint32_t newHandle = createResource(
            0x15,               // Constant argument (likely resource type ID)
            desc->type,         // +0x0C
            desc->subtype1,     // +0x02
            desc->subtype2,     // +0x04
            desc->flag,         // +0x01
            0xFFFFFFFF          // Parent handle (-1 = none)
        );
        desc->handle = newHandle;
    }
}