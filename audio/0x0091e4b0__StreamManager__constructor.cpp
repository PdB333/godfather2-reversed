// FUNC_NAME: StreamManager::constructor

#include <cstdint>

class StreamManager {
public:
    // vtable at +0x00
    void* vtable1;          // +0x00
    // +0x04 possibly another vtable pointer (base class)
    void* vtable2;          // +0x04
    // ... other vtables at offsets 0x10, 0x4C, 0x50, 0x60
    void* vtable3;          // +0x10
    void* vtable4;          // +0x4C (index 0x13)
    void* vtable5;          // +0x50 (index 0x14)
    void* vtable6;          // +0x60 (index 0x18)

    uint32_t field_0x9C;    // +0x9C (index 0x27)
    uint32_t field_0xA0;    // +0xA0 (index 0x28)
    uint32_t field_0xA4;    // +0xA4 (index 0x29)
    void** arrayPtr;        // +0xA8 (index 0x2A)
    uint32_t arraySize;     // +0xAC (index 0x2B)
    uint32_t field_0xB0;    // +0xB0 (index 0x2C)
    uint32_t field_0xB4;    // +0xB4 (index 0x2D)
    uint32_t field_0xB8;    // +0xB8 (index 0x2E)
    uint8_t  byte1;         // +0xBC (index 0x2F)
    uint8_t  byte2;         // +0xBD
    uint8_t  byte3;         // +0xBE
    uint32_t field_0xC0;    // +0xC0 (index 0x30)
    char*    buffer1;       // +0xC4 (index 0x31), allocated 0x80 bytes
    uint32_t field_0xC8;    // +0xC8 (index 0x32)
    char*    buffer3;       // +0xCC (index 0x33), allocated 0x80 bytes
    uint32_t field_0xD0;    // +0xD0 (index 0x34)
    uint32_t maxClients;    // +0xD4 (index 0x35), default 10
    uint32_t field_0xD8;    // +0xD8 (index 0x36)
    uint32_t field_0xDC;    // +0xDC (index 0x37)
    uint32_t maxSomething;  // +0xE0 (index 0x38), default 9
    uint32_t field_0xE4;    // +0xE4 (index 0x39)
    char*    buffer2;       // +0xE8 (index 0x3A), allocated 0x80 bytes
    uint32_t field_0xEC;    // +0xEC (index 0x3B)
    char*    extraBuffers[7]; // +0xF0 to +0x10C (indices 0x3C-0x42), each 0x80 bytes
    uint32_t maxChannels;   // +0x10C (index 0x43), default 6

    // constructor
    StreamManager() {
        // first base class initialisation
        baseClassConstructor();  // FUN_005bf9b0

        // set up vtables
        vtable1 = (void*)0x00d851ec;      // PTR_LAB_00d851ec
        vtable2 = (void*)0x00d85838;      // PTR_FUN_00d85838  (often virtual function pointer)
        vtable3 = (void*)0x00d85810;      // PTR_LAB_00d85810
        vtable4 = (void*)0x00d8580c;      // PTR_LAB_00d8580c
        vtable5 = (void*)0x00d85be8;      // PTR_FUN_00d85be8
        vtable6 = (void*)0x00d85bc4;      // PTR_LAB_00d85bc4

        // second base class initialisation (derived class)
        baseClassConstructor();  // FUN_005bf9b0

        // initialise all fields to zero
        field_0x9C = 0;
        field_0xA0 = 0;
        field_0xA4 = 0;
        arrayPtr = nullptr;
        arraySize = 0;
        field_0xB0 = 0;
        field_0xB4 = 0;
        field_0xB8 = 0;
        byte1 = 0;
        byte2 = 0;
        byte3 = 0;
        field_0xC0 = 0;

        // allocate three main 128‑byte buffers
        buffer1 = new char[0x80];
        *buffer1 = '\0';
        buffer2 = new char[0x80];
        *buffer2 = '\0';
        buffer3 = new char[0x80];
        *buffer3 = '\0';

        field_0xC8 = 0;
        field_0xD0 = 0;
        maxClients = 10;
        field_0xD8 = 0;
        field_0xDC = 0;
        maxSomething = 9;
        field_0xE4 = 0;
        field_0xEC = 0;

        // allocate extra 7 buffers (indices 0x3C to 0x42)
        for (int i = 0; i < 7; ++i) {
            extraBuffers[i] = new char[0x80];
            *extraBuffers[i] = '\0';
        }

        maxChannels = 6;

        // resize the dynamic array to 45 elements, zeroing new ones
        uint32_t oldSize = arraySize;
        if (oldSize < 0x2d) {
            resizeArray(0x2d);   // FUN_00917b10
        }
        // ensure arraySize becomes 45
        arraySize = 0x2d;

        // zero‐fill any newly allocated elements
        for (uint32_t i = oldSize; i < arraySize; ++i) {
            arrayPtr[i] = 0;
        }

        // global pointer to this instance
        g_streamManager = this;
    }

private:
    void baseClassConstructor();  // placeholder for FUN_005bf9b0
    void resizeArray(uint32_t newSize);  // placeholder for FUN_00917b10
};

// global singleton
StreamManager* g_streamManager;  // corresponds to DAT_01130044