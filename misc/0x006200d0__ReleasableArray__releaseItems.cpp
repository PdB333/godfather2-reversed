// FUNC_NAME: ReleasableArray::releaseItems
// This function iterates over an array of 0x10-byte elements, calls a release method (at vtable offset 0xC) 
// on each element's pointer (+8), then releases the array itself and resets the container.
// Used for clearing a dynamic container where each element is a 16-byte struct with a pointer at offset +8.
// Structure of the container (ESI):
//   +0x00: count (uint32)
//   +0x14: dataArray (void*) – pointer to array of 16-byte entries
// Object pointed by EDI supplies the release method (vtable index 3).

struct ReleaseableElement {
    uint32_t field_0;         // +0x0
    uint32_t field_4;         // +0x4
    void*    itemPtr;         // +0x8  – pointer to be released
    uint32_t field_C;         // +0xC
};

struct ContainerStruct {
    uint32_t count;           // +0x00
    uint32_t field_4;         // +0x04
    uint32_t field_8;         // +0x08
    uint32_t field_C;         // +0x0C
    uint32_t field_10;        // +0x10
    ReleaseableElement* dataArray; // +0x14
};

class IReleaser {
public:
    // vtable +0x0C = Release method (index 3)
    virtual void Release(void* obj, int extra) = 0;
};

void releaseArrayItems(IReleaser* releaser, ContainerStruct* container) {
    if (container->count != 0 && releaser != nullptr) {
        uint32_t cnt = container->count;
        if (cnt != 0) {
            uint32_t idx = 0;
            int byteOffset = 0; // increments by 0x10 per element
            do {
                void* item = *(void**)((uint8_t*)container->dataArray + 8 + byteOffset);
                releaser->Release(item, 0);
                idx++;
                byteOffset += 0x10;
            } while (idx < cnt);
        }
        releaser->Release(container->dataArray, 0);
        container->dataArray = nullptr;
        container->count = 0;
    }
}