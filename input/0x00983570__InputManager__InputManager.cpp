// FUNC_NAME: InputManager::InputManager

// Constructor for InputManager (singleton manager for input devices)
// Allocates two 128-byte buffers for device state storage
// Sets global singleton pointer _DAT_01130904 to this instance

#include <cstdint>

class InputManager {
public:
    // Base class constructor call
    void __thiscall baseConstructor(); // FUN_005bf9b0

    // Constructor
    void* __thiscall InputManager(uint32_t param_2) {
        // Call base class constructor
        baseConstructor();

        // +0x4C (offset 0x13) - set to vtable/interface pointer
        *(void**)(this + 0x4C) = &PTR_LAB_00d90860; // temporary assignment

        // Global singleton pointer
        _DAT_01130904 = this;

        // +0x00 - first vtable pointer (main vtable)
        *(void**)(this + 0x00) = &PTR_FUN_00d90890;

        // +0x10 (offset 0x04) - second vtable pointer
        *(void**)(this + 0x10) = &PTR_LAB_00d90868;

        // +0x4C (offset 0x13) - final assignment (overwrites previous)
        *(void**)(this + 0x4C) = &PTR_LAB_00d90864;

        // +0x50 (offset 0x14) - store the input parameter
        *(uint32_t*)(this + 0x50) = param_2;

        // +0x5C (offset 0x17) - copy global data value
        *(uint32_t*)(this + 0x5C) = DAT_00d9085c;

        // Allocate two 128-byte buffers (0x80 bytes each)
        // +0x54 (offset 0x15) - buffer A
        unsigned char* bufferA = (unsigned char*)FUN_009c8e80(0x80); // malloc/new
        *(unsigned char**)(this + 0x54) = bufferA;
        bufferA[0] = 0; // Clear first byte

        // +0x58 (offset 0x16) - buffer B
        unsigned char* bufferB = (unsigned char*)FUN_009c8e80(0x80);
        *(unsigned char**)(this + 0x58) = bufferB;
        bufferB[0] = 0;

        return this;
    }

private:
    // Vtable pointers, data members, etc.
    // Offsets:
    // +0x00: vtable pointer
    // +0x04: vtable pointer (maybe secondary)
    // +0x13*4 = +0x4C: another vtable/interface
    // +0x14*4 = +0x50: stored param_2 (input type flag?)
    // +0x15*4 = +0x54: pointer to 128-byte buffer A
    // +0x16*4 = +0x58: pointer to 128-byte buffer B
    // +0x17*4 = +0x5C: some global constant DAT_00d9085c
};