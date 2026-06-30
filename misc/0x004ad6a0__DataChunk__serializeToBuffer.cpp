// FUNC_NAME: DataChunk::serializeToBuffer
#include <cstring>

// Serializes a DataChunk into a buffer. The buffer must be large enough.
// Writes header (12 bytes) then payload based on type.
// Returns total size written via outSize.
// Type constants: 0x3afd3141, 0x3e55ddf1 indicate inline value (4 bytes).
// Other types: payload is copied from data pointer of given size, then 4-byte aligned.
void __thiscall DataChunk::serializeToBuffer(void* buffer, int* outSize) {
    // this->fields (offsets from this pointer):
    // +0x04 : uint64_t headerField1 (8 bytes)
    // +0x0C : uint32_t headerField2 (4 bytes)
    // +0x10 : uint32_t payloadSize   (4 bytes) - size of data for variable payload
    // +0x18 : uint32_t typeID        (4 bytes) - magic number identifying payload kind
    // +0x1C : union {
    //            uint32_t value;            // if type is inline
    //            void*    dataPtr;          // if type is variable
    //         }

    uint8_t* buf = (uint8_t*)buffer;

    // Write first 8 bytes from this+4
    *(uint64_t*)buf = *(uint64_t*)((uint8_t*)this + 4);
    // Write next 4 bytes from this+0xC
    *(uint32_t*)(buf + 8) = *(uint32_t*)((uint8_t*)this + 0xC);

    uint32_t type = *(uint32_t*)((uint8_t*)this + 0x18);

    // If type is not one of the two special inline types, and the payload pointer is null, write a minimal header (12 bytes) and return.
    if (type != 0x3AFD3141 && type != 0x3E55DDF1 && *(uint32_t*)((uint8_t*)this + 0x1C) == 0) {
        *outSize = 12;
        // The original code also zeros buf+8? Actually it does *(unaff_EDI+1)=0, which is buf[8..11] set to 0.
        // But that would overwrite the header field we already wrote? Possibly the requirement is to clear it.
        // Ghidra shows it after the check, so we'll set the second header field to 0.
        *(uint32_t*)(buf + 8) = 0;
        return;
    }

    // Set the pointer to the next section (offset 0x0C from buffer start)
    uint32_t* nextFieldPtr = (uint32_t*)(buf + 12);
    // Write the type ID at that location
    *nextFieldPtr = type;

    if (type == 0x3AFD3141 || type == 0x3E55DDF1) {
        // Inline value: write the 4-byte value at buffer+16
        *(uint32_t*)(buf + 16) = *(uint32_t*)((uint8_t*)this + 0x1C);
        *outSize = 20;  // 12 header + 4 type + 4 value
        return;
    }

    // Variable-length payload: data from this+0x1C (pointer) of size this+0x10
    uint32_t payloadSize = *(uint32_t*)((uint8_t*)this + 0x10);
    void* dataPtr = *(void**)((uint8_t*)this + 0x1C);
    uint8_t* dest = (uint8_t*)(buf + 16);  // start of payload after header+type
    memcpy(dest, dataPtr, payloadSize);

    // Align to 4-byte boundary after payload
    uint8_t* alignedEnd = (uint8_t*)(((uint32_t)(dest + payloadSize) + 3) & ~3);
    // Zero pad between end of payload and aligned boundary
    uint32_t padSize = alignedEnd - (dest + payloadSize);
    if (padSize > 0) {
        memset(dest + payloadSize, 0, padSize);
    }

    // Total size is from buffer start to aligned end
    *outSize = (int)(alignedEnd - buf);
}