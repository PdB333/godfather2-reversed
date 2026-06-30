// FUNC_NAME: flattenPacketList
// Function address: 0x004eb4b0
// Role: Serializes a linked list of packet nodes (each with data pointer) into a contiguous buffer.
// The linked list node structure:
//   +0x00: flags (24-bit) and length (8-bit) combined (as uint32)
//   +0x04: dataSize (uint32, byte count)
//   +0x08: data pointer (void*)
//   +0x0C: next (PacketNode*)
// Output buffer layout: [count (int32)] [record0 header (uint32)] [record0 data...] [record1...]

#include <cstdint>

struct PacketNode {
    uint32_t flagsAndLength;  // +0x00: low 24 bits = flags, high 8 bits = length of data
    uint32_t dataSize;        // +0x04: size of data buffer in bytes
    void* data;               // +0x08: pointer to data (non-null means valid)
    PacketNode* next;         // +0x0C: next node in chain
};

// Allocator descriptor used for memory allocation
struct AllocDescriptor {
    uint32_t type;      // 0x2 (likely Memory::Type::GameData or similar)
    int32_t alignment;  // 0x4 (4-byte alignment)
    void* parent;       // nullptr
};

// Forward declaration of external allocator singleton accessor
void* GetAllocator();  // returns pointer to allocator vtable (similar to FUN_009c8f80)

// External helper to copy memory (likely memcpy)
void copyData(void* dest, const void* src, size_t size); // FUN_004eb3f0

// Flatten a chain of PacketNode into a single allocated buffer.
// inList: pointer to head of the chain (passed in ECX via __fastcall or similar)
// outBuffer: pointer to output pointer (will be set to allocated buffer)
void flattenPacketList(PacketNode* inList, int** outBuffer) {
    // If there is an existing buffer, free it
    if (*outBuffer != nullptr) {
        void* allocator = GetAllocator();
        // Call allocator->free(ptr, 0)
        (*(void(__thiscall**)(void*, void*))(*((uint32_t*)allocator) + 4))(*outBuffer, nullptr);
        *outBuffer = nullptr;
    }

    // Calculate total size needed (in 4-byte words)
    int totalWords = 1; // room for count at start
    PacketNode* current = inList;
    while (current != nullptr) {
        if (current->data != nullptr) {
            // Each record: 1 word header + ceil(dataSize/4) words of data
            totalWords += 1 + ((current->dataSize + 3) >> 2);
        }
        current = current->next;
    }

    // Allocate buffer
    void* allocator = GetAllocator();
    AllocDescriptor allocDesc;
    allocDesc.type = 2;
    allocDesc.alignment = 4;
    allocDesc.parent = nullptr;
    int* newBuffer = (int*)(*(void*(__thiscall**)(void*, int, AllocDescriptor*))(*((uint32_t*)allocator) + 0))(allocator, totalWords * 4, &allocDesc);
    *outBuffer = newBuffer;

    if (newBuffer != nullptr) {
        int* writePtr = newBuffer + 1; // skip count slot
        int recordCount = 0;
        PacketNode* node = inList;
        while (node != nullptr) {
            if (node->data != nullptr) {
                // Write header: low 24 bits from node->flagsAndLength, high 8 bits from node->dataSize
                *writePtr = (node->flagsAndLength & 0xFFFFFF) | (node->dataSize << 24);
                // Copy data after header
                uint8_t* dataDest = (uint8_t*)(writePtr + 1);
                copyData(dataDest, node->data, node->dataSize);
                // Advance past header + rounded data
                writePtr += 1 + ((node->dataSize + 3) >> 2);
                recordCount++;
                // Note: outBuffer is reassigned to null in the loop? That might be a decompiler artifact.
                // We ignore that and keep recordCount.
            }
            node = node->next;
        }
        // Write record count at the beginning of the buffer
        newBuffer[0] = recordCount;
    }
}