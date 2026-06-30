// FUNC_NAME: initializeResourceManagerData
// Address: 0x004f9410
// Initializes a global resource manager data structure with magic, sizes and pointers.
// Returns a pointer to the static data at 0x01219050.

struct ResourceManagerData {
    void* vtableOrString;  // +0x00
    void* anotherPointer;   // +0x04
    uint32_t magic;         // +0x08 (".efe" as little-endian 0x2e656665)
    uint32_t field0C;       // +0x0C = 1
    uint32_t field10;       // +0x10 = 4
    uint32_t field14;       // +0x14 = 0
    uint32_t field18;       // +0x18 = 0x800 (2048)
    uint32_t field1C;       // +0x1C = 0
    uint32_t field20;       // +0x20 = 0
    uint32_t field24;       // +0x24 = 0
};

// Global instance pointer (static data at 0x01219050)
ResourceManagerData* const gResourceManagerData = reinterpret_cast<ResourceManagerData*>(0x01219050);

ResourceManagerData* initializeResourceManagerData() {
    gResourceManagerData->vtableOrString = reinterpret_cast<void*>(0x00e37a18);
    gResourceManagerData->anotherPointer = reinterpret_cast<void*>(0x00e379bc);
    gResourceManagerData->magic = 0x2e656665;   // little-endian: 'e','f','e','.' -> ".efe"
    gResourceManagerData->field0C = 1;
    gResourceManagerData->field10 = 4;
    gResourceManagerData->field14 = 0;
    gResourceManagerData->field18 = 0x800;
    gResourceManagerData->field1C = 0;
    gResourceManagerData->field20 = 0;
    gResourceManagerData->field24 = 0;
    return gResourceManagerData;
}