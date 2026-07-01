// FUNC_NAME: StreamManager::constructor
// Function address: 0x008e7750
// Role: Constructor for a manager object with multiple virtual function tables.
// Sets up vtable pointers for base class and derived interfaces, and writes debug markers.

#include <cstdint>

extern void BaseClassInit(uint32_t param, uint32_t size); // FUN_0046e6b0

class StreamManager {
public:
    // Virtual function table pointers at various offsets (multi-inheritance)
    void* vtable;          // +0x00
    void* iface1_vtable;   // +0x04 (param_1[4])
    // ... other interface vtable pointers at offsets 0x4C, 0x58, 0x60, 0x64, 0x68
    // Debug markers at offsets 0x190, 0x194, 0x198, 0x19C, 0x1A0, 0x1A4
};

StreamManager* __thiscall StreamManager::StreamManager(StreamManager* this, uint32_t arg) {
    // Initialize base class fields
    this->iface1_vtable = nullptr;                 // param_1[1]=0
    this->vtable = (void*)0x00d80570;             // Base vtable pointer

    // Call base class initialization function with arg and buffer size 0x4000 (16384 bytes)
    BaseClassInit(arg, 0x4000);

    // Set interface vtable pointers (base versions)
    this->iface1_vtable = (void*)0x00d80008;      // param_1[4]
    ((void**)this)[0x13] = (void*)0x00d7fff8;     // +0x4C
    ((void**)this)[0x16] = (void*)0x00d7fff4;     // +0x58
    ((void**)this)[0x18] = (void*)0x00d7fff0;     // +0x60
    ((void**)this)[0x19] = (void*)0x00d7ff90;     // +0x64
    ((void**)this)[0x1A] = (void*)0x00d7ff28;     // +0x68

    // Override with derived class vtable pointers
    this->vtable = (void*)0x00d80834;
    this->iface1_vtable = (void*)0x00d806d8;
    ((void**)this)[0x13] = (void*)0x00d806c8;
    ((void**)this)[0x16] = (void*)0x00d806c4;
    ((void**)this)[0x18] = (void*)0x00d806c0;
    ((void**)this)[0x19] = (void*)0x00d80660;
    ((void**)this)[0x1A] = (void*)0x00d805f8;

    // Write debug markers to detect memory corruption
    ((uint32_t*)this)[100] = 0xBADBADBA;   // +0x190
    ((uint32_t*)this)[0x65] = 0xBEEFBEEF; // +0x194
    ((uint32_t*)this)[0x66] = 0xEAC15A55; // +0x198
    ((uint32_t*)this)[0x67] = 0x91100911; // +0x19C
    ((uint32_t*)this)[0x68] = 0;          // +0x1A0
    ((uint32_t*)this)[0x69] = 0;          // +0x1A4

    return this;
}