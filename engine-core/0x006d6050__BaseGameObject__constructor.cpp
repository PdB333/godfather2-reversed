// FUNC_NAME: BaseGameObject::constructor
// Function address: 0x006d6050
// This is a constructor for a class that inherits from at least one base class (via FUN_0046c590)
// and has multiple vtable pointers (at offsets 0x0, 0x3C, 0x48).
// Fields are initialized to zero.

class BaseGameObject {
public:
    // Vtable pointer at +0x00
    // Additional vtable pointer at +0x3C (offset 0xF * 4)
    // Additional vtable pointer at +0x48 (offset 0x12 * 4)

    // Constructor takes a parameter (likely a pointer or ID) passed to base class constructor
    __thiscall BaseGameObject(void* param1) {
        // Call base class constructor (likely a base class that initializes common fields)
        FUN_0046c590(param1);

        // Set primary vtable (class-specific)
        *(void**)this = &PTR_FUN_00d5f45c;

        // Set secondary vtable pointers for additional interfaces (multiple inheritance)
        *(void**)((int)this + 0x3C) = &PTR_LAB_00d5f44c;  // +0x3C
        *(void**)((int)this + 0x48) = &PTR_LAB_00d5f448;  // +0x48

        // Initialize fields to zero
        *(int*)((int)this + 0x50) = 0;  // param_1[0x14] -> offset 0x50
        *(short*)((int)this + 0x54) = 0; // *(undefined2 *)(param_1 + 0x15) -> +0x54 (2 bytes)
        *(short*)((int)this + 0x56) = 0; // *(undefined2 *)((int)param_1 + 0x56) -> +0x56 (2 bytes)
        *(int*)((int)this + 0x58) = 0;  // param_1[0x16] -> offset 0x58
        *(int*)((int)this + 0x5C) = 0;  // param_1[0x17] -> offset 0x5C
        *(int*)((int)this + 0x60) = 0;  // param_1[0x18] -> offset 0x60
        *(int*)((int)this + 0x64) = 0;  // param_1[0x19] -> offset 0x64
        *(int*)((int)this + 0x68) = 0;  // param_1[0x1A] -> offset 0x68

        return this;
    }
};