// FUNC_NAME: StaticMeshPacker::packGeometry

#include <cstring>

// Structure of source object (starting at param_1)
// +0x34: int numEntries
// +0x50: int* entriesArray (pointer to array of SourceEntry of size 0xB0)
struct SourceObject {
    int numEntries; // 0x34
    char pad[0x1C]; // 0x38-0x4F
    SourceEntry* entries; // 0x50
};

// Structure of a single source entry (0xB0 bytes each)
// +0x06: char enabled (non-zero if active)
// +0x25: u8 vertexCountFlags (LSB + full value used for data size)
// +0x38: u16 someWidth? (stored as ushort)
// +0x3A: u16 someHeight? (stored as ushort)
// +0x3F (0x64 from base?): int filterId
// +0x84: int someData
// +0x4C: void* backPointer (set to header address)
struct SourceEntry {
    char pad0[6];
    char enabled; // 0x06
    char pad1[0x1E]; // 0x07-0x24
    uint8_t vertexCountFlags; // 0x25
    char pad2[0x12]; // 0x26-0x37
    uint16_t width; // 0x38
    uint16_t height; // 0x3A
    char pad3[0x28]; // 0x3C-0x63
    int filterId; // 0x64 (same as +0x3F from offset 0x25)
    char pad4[0x1C]; // 0x68-0x83
    int someData; // 0x84
    char pad5[0xC4]; // 0x88-0xAF? Actually up to 0xB0 - but 0x4C is used for back pointer
    void* headerPtr; // 0x4C
};

// Header in the packed buffer (48 bytes per matched entry)
struct PackedHeader {
    PackedHeader* next; // 0x00
    void* bufferBase; // 0x04: pointer to start of buffer (_Dst)
    SourceEntry* sourceEntry; // 0x08
    uint32_t field0x0C; // unknown
    uint16_t width; // 0x10
    uint8_t flags; // 0x14
    char pad[3]; // 0x15-0x17
    void* dataPointer; // 0x18? Actually offset 0x2C (0xB words after start) but we'll define fields sequentially.
    // Better: use an array of 12 uint32_t
    uint32_t data[12];
};

// The packed buffer layout:
// offset 0x00: overall struct
// +0x04: size_t totalAllocatedSize
// +0x08: PackedHeader* head (linked list)
// +0x14: SourceEntry* lastMatchedEntry? (set to last matched)
// +0x18: SourceObject* sourceObject
// +0x30: PackedHeader entries[] (array of 48-byte headers)
// then after headers, the variable data chunks.

void* StaticMeshPacker::packGeometry(SourceObject* sourceObj, int filterId)
{
    if (!sourceObj || sourceObj->numEntries <= 0) {
        return nullptr;
    }

    int numMatched = 0;
    int totalDataSize = 0; // sum of data per matched entry

    int count = sourceObj->numEntries;
    byte* cursor = (byte*)sourceObj->entries + 0x25; // start at vertexCountFlags field

    // First pass: count matching entries and compute data size
    for (int i = 0; i < count; i++) {
        if ((*(int*)(cursor + 0x3F) == filterId) && (*(cursor - 0x1F) != 0)) { // -0x1F = +0x06 (enabled)
            int vertexFlags = *cursor; // u8
            numMatched++;
            totalDataSize += vertexFlags + (vertexFlags & 1); // (*pbVar2 & 1) + (uint)*pbVar2
        }
        cursor += 0xB0; // stride
    }

    // Compute allocation size: headers (aligned) + data
    int headerSizeAligned = (numMatched * 0x30 + 0xAF) & ~0x7F; // align to 128
    int totalAllocSize = totalDataSize * 0x40 + headerSizeAligned; // each data unit is 64 bytes

    // Allocate buffer
    void* buffer = (*(void*(*)(int, void*))*gAllocFunc)(totalAllocSize, &gMemoryTag);
    if (!buffer) return nullptr;
    memset(buffer, 0, totalAllocSize);

    // Fill buffer header
    *(size_t*)((int)buffer + 4) = totalAllocSize;
    *(int*)((int)buffer + 0x18) = (int)sourceObj;

    // Second pass: build headers and copy data
    PackedHeader* prevHeader = nullptr;
    PackedHeader* currentHeader = (PackedHeader*)((int)buffer + 0x30);
    char* dataPtr = (char*)((int)buffer + headerSizeAligned);
    int idx = 0;

    for (int i = 0; i < sourceObj->numEntries; i++) {
        SourceEntry* entry = &sourceObj->entries[i];

        if ((entry->filterId == filterId) && (entry->enabled != 0)) {
            // Initialize header
            currentHeader->next = nullptr;
            currentHeader->bufferBase = buffer;
            currentHeader->sourceEntry = entry;
            entry->headerPtr = (void*)currentHeader; // back pointer

            if (prevHeader == nullptr) {
                *(PackedHeader**)((int)buffer + 8) = currentHeader; // head of list
            } else {
                prevHeader->next = currentHeader;
            }

            // Set data pointer for this header
            currentHeader->data[0xB] = (uint32_t)(size_t)dataPtr;

            // Copy fields from source entry
            uint8_t flags = entry->vertexCountFlags;
            currentHeader->data[0x5] = flags;
            currentHeader->data[0x7] = *(uint16_t*)((int)entry + 0x3A); // height
            currentHeader->data[0x6] = *(uint32_t*)((int)entry + 0x84); // someData
            currentHeader->data[0x4] = *(uint16_t*)((int)entry + 0x38); // width

            // Advance data pointer by size of this entry's data
            dataPtr += (flags + (flags & 1)) * 0x40;

            // Store last matched entry (for convenience)
            *(int*)((int)buffer + 0x14) = (int)entry;

            prevHeader = currentHeader;
            currentHeader = (PackedHeader*)((int)currentHeader + 0x30); // sizeof(PackedHeader) = 0x30
        }
    }

    return buffer;
}