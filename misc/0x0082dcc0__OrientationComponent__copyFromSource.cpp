// FUNC_NAME: OrientationComponent::copyFromSource
#include <cstdint>

// External functions
extern void __fastcall FUN_0081f9f0(int param);
extern void* PTR_LAB_00d73688;  // VTable for OrientationComponent

class OrientationComponent {
public:
    void* vtable;                                     // +0x00
    // ... other fields (size up to 0x4c) ...
    float rotationX;                                  // +0x4c
    float rotationY;                                  // +0x50
    float rotationZ;                                  // +0x54
    float rotationW;                                  // +0x58

    // Copies rotation quaternion from source at offset 0x4c-0x58
    OrientationComponent* copyFromSource(uint32_t source) {
        FUN_0081f9f0(source);                         // base initialization
        this->vtable = &PTR_LAB_00d73688;             // set vtable
        // Copy 4 floats (quaternion) from source
        this->rotationX = *(float*)(source + 0x4c);
        this->rotationY = *(float*)(source + 0x50);
        this->rotationZ = *(float*)(source + 0x54);
        this->rotationW = *(float*)(source + 0x58);
        return this;
    }
};