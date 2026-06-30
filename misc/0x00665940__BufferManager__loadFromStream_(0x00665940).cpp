// FUNC_NAME: BufferManager::loadFromStream (0x00665940)
#include <cstdlib> // for calloc

struct BufferDescriptor {
    void* buffer;    // +0x00
    int capacity;    // +0x04
    int flags;       // +0x08
};

int BufferManager::loadFromStream(void* stream) // param_3: input stream
{
    // Allocate internal buffer (4 * 0x40 = 256 bytes)
    void* internalBuffer = calloc(4, 0x40);
    if (!internalBuffer) {
        return -2; // Allocation failure
    }

    // Prepare descriptor for data reading
    BufferDescriptor desc;
    desc.buffer = nullptr;
    desc.capacity = 0x40;   // Expected size?
    desc.flags = 0;

    int result = init(); // FUN_006657c0 – initialize this object
    if (result == 0) {
        result = readData(&desc, stream); // FUN_00668850 – read from stream into desc
    }

    finalize(); // FUN_00665b40 – post-processing
    return result;
}