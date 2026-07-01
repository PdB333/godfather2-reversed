// FUNC_NAME: UIElement::UIElement

// Base class constructor call at 0x0046c590
// This is likely a UI control/element with boolean flags and pointer data

class UIElement {
public:
    // vtable pointer at offset 0x00
    // Additional pointers at +0x3C (0xF*4) and +0x48 (0x12*4)
    // Flags/state fields at +0x50, +0x54, +0x58, +0x5C, +0x60

    // Constructor
    // param_2 is passed to base constructor (likely parent or ID)
    __thiscall UIElement(void* param_2) {
        // Call base class constructor
        FUN_0046c590(param_2);  // BaseUIElement constructor

        // Set vtable pointer
        this->vtable = &PTR_FUN_00d6fd40;

        // Set additional interface/data pointers
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00d6fd30;  // +0x3C
        *(void**)((char*)this + 0x48) = &PTR_LAB_00d6fd2c;  // +0x48

        // Clear flags and state fields
        *(uint32_t*)((char*)this + 0x50) = 0;  // +0x50 (0x14*4)
        *(uint16_t*)((char*)this + 0x54) = 0;  // +0x54 (0x15*4, 2 bytes)
        *(uint16_t*)((char*)this + 0x56) = 0;  // +0x56 (2 bytes)
        *(uint32_t*)((char*)this + 0x58) = 0;  // +0x58 (0x16*4)
        *(uint16_t*)((char*)this + 0x5C) = 0;  // +0x5C (0x17*4, 2 bytes)
        *(uint16_t*)((char*)this + 0x5E) = 0;  // +0x5E (2 bytes)
        *(uint8_t*)((char*)this + 0x60) = 0;   // +0x60 (0x18*4, 1 byte)

        return this;
    }
};