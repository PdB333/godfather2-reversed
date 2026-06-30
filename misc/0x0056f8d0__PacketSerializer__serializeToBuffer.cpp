// FUNC_NAME: PacketSerializer::serializeToBuffer
// This function serializes the object into a flat buffer with a fixed header and optional sub-blocks.
// It checks that the buffer size is >= required size (from offset +0x0A), writes the header,
// then for each present sub-object, calls its serialization function and stores the sub-block offset in the header.
// Returns 1 on success, 0 on failure (insufficient space or sub-object serialization failure).

typedef unsigned char __bool8;
typedef unsigned short __uint16;
typedef unsigned int __uint32;

class PacketSerializer {
public:
    // The base size of this object's serialized header (bytes)
    // +0x0A: __uint16 m_baseSize;
    // +0x0C: __uint32 m_someId; // copied into header
    // +0x34: SubObject* m_sub1;
    // +0x38: SubObject* m_sub2;
    // +0x3C: SubObject* m_sub3;
    // +0x40: SubObject* m_sub4;
    // +0x44: SubObject* m_sub5;

    // Global constant (maybe a sentinel or magic number)
    static const __uint32 kMagic = DAT_00e2b1a4; // placeholder

    // Serialize the entire object into the output buffer.
    // @param buffer: output buffer (passed in EAX via __thiscall convention)
    // @param bufferSize: total available size in the buffer
    // @return true on success, false on failure
    __bool8 serialize(void* buffer, __uint32 bufferSize) {
        // The fixed header size must fit
        if (bufferSize < *(__uint16*)((uintptr_t)this + 0x0A)) {
            return 0;
        }

        // Write header fields
        *(__uint32*)buffer = 0;                                 // +0x00: some header field (size/type?)
        *((__uint8*)buffer + 2) = 1;                            // +0x02: flag byte
        *(__uint32*)((uintptr_t)buffer + 4) = 0;                // +0x04: another field
        *((__uint8*)buffer + 9) = 0;                            // +0x09: flag byte
        *(__uint16*)((uintptr_t)buffer + 0x0A) = *(__uint16*)((uintptr_t)this + 0x0A); // +0x0A: base size
        *(__uint32*)((uintptr_t)buffer + 0x0C) = *(__uint32*)((uintptr_t)this + 0x0C); // +0x0C: some ID

        // Initialize sub-block offset fields to 0
        *(__uint32*)((uintptr_t)buffer + 0x10) = 0; // +0x10: offset for sub1 (if present)
        *(__uint32*)((uintptr_t)buffer + 0x14) = 0; // +0x14: offset for sub2
        *(__uint32*)((uintptr_t)buffer + 0x18) = 0; // +0x18: offset for sub3
        *(__uint32*)((uintptr_t)buffer + 0x1C) = kMagic; // +0x1C: reserved/magic
        *(__uint32*)((uintptr_t)buffer + 0x20) = 0; // +0x20: offset for sub4? (maybe padding)
        *(__uint32*)((uintptr_t)buffer + 0x24) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x28) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x2C) = kMagic; // +0x2C: another magic
        *((__uint8*)buffer + 0x30) = 0; // +0x30: flag byte
        *((__uint8*)buffer + 0x31) = 0;
        *((__uint8*)buffer + 0x32) = 0;
        *((__uint8*)buffer + 0x33) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x34) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x38) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x3C) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x40) = 0;
        *(__uint32*)((uintptr_t)buffer + 0x44) = 0;

        // Current write offset starts after the fixed header
        __uint32 currentOffset = *(__uint16*)((uintptr_t)this + 0x0A);
        __uint32 remainingSize = bufferSize - currentOffset;

        // Serialize sub-objects if present, storing their offsets in the header
        if (*(void**)((uintptr_t)this + 0x34) != 0) {
            __bool8 result = FUN_0056f080(remainingSize); // sub1 serialization
            if (!result) return 0;
            *(__uint32*)((uintptr_t)buffer + 0x0D * 4) = currentOffset; // store offset at +0x34
            __uint32 subSize = *(__uint16*)(*(uintptr_t*)((uintptr_t)this + 0x34) + 0x0A);
            currentOffset += subSize;
            remainingSize -= subSize;
        }
        if (*(void**)((uintptr_t)this + 0x38) != 0) {
            __bool8 result = FUN_0056ed10(remainingSize);
            if (!result) return 0;
            *(__uint32*)((uintptr_t)buffer + 0x0E * 4) = currentOffset;
            __uint32 subSize = *(__uint16*)(*(uintptr_t*)((uintptr_t)this + 0x38) + 0x0A);
            currentOffset += subSize;
            remainingSize -= subSize;
        }
        if (*(void**)((uintptr_t)this + 0x3C) != 0) {
            __bool8 result = FUN_005805f0(remainingSize);
            if (!result) return 0;
            *(__uint32*)((uintptr_t)buffer + 0x0F * 4) = currentOffset;
            __uint32 subSize = *(__uint16*)(*(uintptr_t*)((uintptr_t)this + 0x3C) + 0x0A);
            currentOffset += subSize;
            remainingSize -= subSize;
        }
        if (*(void**)((uintptr_t)this + 0x40) != 0) {
            __bool8 result = FUN_00580960(remainingSize);
            if (!result) return 0;
            *(__uint32*)((uintptr_t)buffer + 0x10 * 4) = currentOffset;
            __uint32 subSize = *(__uint16*)(*(uintptr_t*)((uintptr_t)this + 0x40) + 0x0A);
            currentOffset += subSize;
            remainingSize -= subSize;
        }
        if (*(void**)((uintptr_t)this + 0x44) != 0) {
            __bool8 result = FUN_0056e900(remainingSize);
            if (!result) return 0;
            *(__uint32*)((uintptr_t)buffer + 0x11 * 4) = currentOffset;
        }
        return 1;
    }
};