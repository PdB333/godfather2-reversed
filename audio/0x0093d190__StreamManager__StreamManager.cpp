// FUNC_NAME: StreamManager::StreamManager
// Address: 0x0093d190
// Initializes the StreamManager singleton with vtable pointers, allocates multiple 128/256-byte buffers,
// copies global stream source paths (up to 0x8000 bytes each) into internal storage.

class StreamManager {
public:
    // +0x00: primary vtable
    void** vtable;
    // +0x04: secondary vtable (interface)
    void** vtable2;
    // +0x08-0x4B: other fields
    // +0x4C: (offset 0x13) vtable pointer
    void** m_vtable3;
    // +0x50: (offset 0x14) vtable pointer
    void** m_vtable4;
    // +0x54: count or index (initial 1)
    int m_counter;
    // +0x58: another count (initial 0)
    int m_otherCounter;
    // +0x5C: zero
    // ...
    // +0xD4: (offset 0x35) sentinel (-1)
    int m_sentinel;
    // +0xD8: zero
    // +0xDC: zero
    // ...
    // +0xE8: (offset 0x3A) zero
    // +0xEC: (offset 0x3B) initial 0xF (15)
    int m_maxStreams;
    // +0xF0: zero
    // +0xF4: (offset 0x3D) zero
    // +0x100: (offset 0x40) zero
    // ... up to offset 0x5F (0x17C)
    // +0xE0: (offset 0x38) allocated 128-byte buffer pointer
    char* m_buffer1;
    // +0xE4: (offset 0x39) allocated 128-byte buffer pointer
    char* m_buffer2;
    // +0xF8: (offset 0x3E) allocated 128-byte buffer pointer
    char* m_buffer3;
    // +0xFC: (offset 0x3F) allocated 128-byte buffer pointer
    char* m_buffer4;
    // +0x130: (offset 0x4C) allocated 128-byte buffer pointer
    char* m_buffer5;
    // +0xB8: (offset 0x2E) allocated 256-byte buffer pointer
    char* m_buffer6;
    // +0xBC: (offset 0x2F) allocated 128-byte buffer pointer
    char* m_buffer7;
    // +0x108: (offset 0x42) allocated 128-byte buffer pointer
    char* m_buffer8;
    // +0x10C: (offset 0x43) allocated 128-byte buffer pointer
    char* m_buffer9;
    // +0x50 (0x14 words): stream source data array (6 entries, each 0x8000 bytes)
    char streamSourceData[6][0x8000]; // Overlaps with vtable fields above, but likely union or large buffer

    // External functions called
    extern void __cdecl baseConstructor(void* this); // 0x005bf9b0
    extern void* __cdecl allocateMemory(int size); // 0x009c8e80
    extern void __cdecl copyData(void* dest, void* src, int size); // 0x00408900 (likely memcpy)
};

StreamManager* __thiscall StreamManager::ctor(StreamManager* this) {
    // Call base class constructor (likely EARSObject)
    baseConstructor(this);

    // Set up multiple vtable pointers (likely for multiple inheritance)
    this->m_vtable3 = &PTR_LAB_00d8a9e0; // initial
    // Remember offset 0x14 for later copies
    void** internalPtr = &this->m_vtable4; // param_1 + 0x14

    *internalPtr = &PTR_FUN_00e2f19c;
    this->m_counter = 1;
    this->m_otherCounter = 0;

    // Final vtable assignments (overwrites earlier)
    this->vtable = &PTR_FUN_00d8ae70;
    this->vtable2 = &PTR_LAB_00d8ae48;
    this->m_vtable3 = &PTR_LAB_00d8ae44;
    *internalPtr = &PTR_LAB_00d8ae34; // this->m_vtable4

    // Zero-initialize many fields
    this->m_sentinel = 0xFFFFFFFF;
    this->m_maxStreams = 0xF; // 15

    // Allocate 9 buffers
    // +0x38
    char* buf1 = (char*)allocateMemory(0x80);
    this->m_buffer1 = buf1;
    *buf1 = 0;
    // +0x39
    char* buf2 = (char*)allocateMemory(0x80);
    this->m_buffer2 = buf2;
    *buf2 = 0;
    // +0x3E
    char* buf3 = (char*)allocateMemory(0x80);
    this->m_buffer3 = buf3;
    *buf3 = 0;
    // +0x3F
    char* buf4 = (char*)allocateMemory(0x80);
    this->m_buffer4 = buf4;
    *buf4 = 0;
    // +0x4C
    char* buf5 = (char*)allocateMemory(0x80);
    this->m_buffer5 = buf5;
    *buf5 = 0;
    // +0x2E (size 0x100)
    char* buf6 = (char*)allocateMemory(0x100);
    this->m_buffer6 = buf6;
    *buf6 = 0;
    // +0x2F
    char* buf7 = (char*)allocateMemory(0x80);
    this->m_buffer7 = buf7;
    *buf7 = 0;
    // +0x42
    char* buf8 = (char*)allocateMemory(0x80);
    this->m_buffer8 = buf8;
    *buf8 = 0;
    // +0x43
    char* buf9 = (char*)allocateMemory(0x80);
    this->m_buffer9 = buf9;
    *buf9 = 0;

    // Copy global stream source data into internal array at offset 0x50 (6 sources)
    if (DAT_01130450 != 0) {
        copyData(internalPtr, &DAT_01130450, 0x8000);
    }
    if (DAT_011303b0 != 0) {
        copyData(internalPtr, &DAT_011303b0, 0x8000);
    }
    if (DAT_01130240 != 0) {
        copyData(internalPtr, &DAT_01130240, 0x8000);
    }
    if (DAT_01130348 != 0) {
        copyData(internalPtr, &DAT_01130348, 0x8000);
    }
    if (DAT_011301d0 != 0) {
        copyData(internalPtr, &DAT_011301d0, 0x8000);
    }
    if (DAT_01130498 != 0) {
        copyData(internalPtr, &DAT_01130498, 0x8000);
    }

    // Store this instance globally
    DAT_01129c4c = this;

    return this;
}

// External global data (likely string arrays or source descriptors)
extern void* DAT_01130450;
extern void* DAT_011303b0;
extern void* DAT_01130240;
extern void* DAT_01130348;
extern void* DAT_011301d0;
extern void* DAT_01130498;