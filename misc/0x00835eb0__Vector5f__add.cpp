// FUNC_NAME: Vector5f::add

// 0x00835eb0: Member function of Vector5f class, adds the corresponding five floats from two source vectors into this vector.
// The class has a vtable pointer at offset 0, and five floats (position+rotation?) at offset 0x4c (0x13 * 4).
// Called from 0x0082b580.

class Vector5f {
public:
    void* vtable;                    // +0x00
    // ... other fields ...
    float elements[5];              // +0x4c (offsets 0x13, 0x14, 0x15, 0x16, 0x17)
};

// Initializer called first (likely sets up vtable and default values)
void __thiscall Vector5f_init(Vector5f* this); // FUN_008334a0

// Adds the five float components from a and b, stores in this.
// Returns this.
Vector5f* __thiscall Vector5f__add(Vector5f* this, Vector5f* param_2, Vector5f* param_3) {
    // Load globals (default values? these are overwritten below)
    float defaultVal1 = *(float*)0x00d5ef88;    // DAT_00d5ef88
    float defaultVal2 = *(float*)0x00d6471c;    // DAT_00d6471c
    float defaultVal3 = *(float*)0x00d5cf70;    // _DAT_00d5cf70
    float defaultVal4 = *(float*)0x00e44630;    // DAT_00e44630
    // Note: defaultVal3 used twice below

    // Initialize vtable
    this->vtable = (void*)0x00d7377c;           // &PTR_LAB_00d7377c

    // Write default values (these will be overwritten)
    this->elements[0] = defaultVal1;            // offset +0x4c
    this->elements[1] = defaultVal2;            // offset +0x50
    this->elements[2] = defaultVal3;            // offset +0x54
    this->elements[3] = defaultVal4;            // offset +0x58
    this->elements[4] = defaultVal3;            // offset +0x5c

    // Now compute sum of corresponding floats from param_2 and param_3
    this->elements[0] = *(float*)((char*)param_2 + 0x4c) + *(float*)((char*)param_3 + 0x4c);
    this->elements[1] = *(float*)((char*)param_2 + 0x50) + *(float*)((char*)param_3 + 0x50);
    this->elements[2] = *(float*)((char*)param_2 + 0x54) + *(float*)((char*)param_3 + 0x54);
    this->elements[3] = *(float*)((char*)param_2 + 0x58) + *(float*)((char*)param_3 + 0x58);
    this->elements[4] = *(float*)((char*)param_2 + 0x5c) + *(float*)((char*)param_3 + 0x5c);

    return this;
}