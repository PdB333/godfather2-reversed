// FUNC_NAME: SimObject::SimObject

// Class constructor (initializer) for a base EARS engine SimObject.
// Sets vtable pointers and initializes all fields to default values.
// Offset field comments in bytes.

class SimObject {
public:
    // +0x00: vtable pointer
    void *vtable;
    
    // +0x04: some flag, initialized to 1
    int field_04;
    
    // +0x08: some counter or ID, initialized to 0
    int field_08;
    
    // +0x0C: second vtable or function pointer, initially set to PT_FUN_00e32808, then overwritten to PTR_LAB_00e35f58
    void *field_0C;
    
    // +0x10: some handle or pointer, initialized to 0
    int field_10;
    
    // +0x14: unknown, initialized to 0
    int field_14;
    
    // +0x18: unknown, initialized to 0
    int field_18;
    
    // +0x1C: unknown, initialized to 0
    int field_1C;
    
    // +0x20: unknown, initialized to 1? Actually param_1+8 = field at 0x20, set to 0? Wait: param_1[2] is at +0x08, param_1[3] at +0x0C, param_1[4] at +0x10, etc.
    // Let's map correctly:
    // param_1[0] = +0x00 (vtable)
    // param_1[1] = +0x04 (field_04)
    // param_1[2] = +0x08 (field_08)
    // param_1[3] = +0x0C (field_0C)
    // param_1[4] = +0x10 (field_10)
    // param_1[5] = +0x14 (field_14)
    // param_1[6] = +0x18 (field_18)
    // param_1[7] = +0x1C (field_1C)
    // param_1[8] = +0x20 (field_20)
    // param_1[9] = +0x24 (field_24)
    // param_1[10] = +0x28 (field_28)
    // Then at param_1+0xB? Actually param_1+0xb is pointer arithmetic on dword pointer, so +0x2C bytes.
    // *(undefined2 *)(param_1 + 0xb) = 0  -> writes a short at +0x2C
    // *(undefined2 *)((int)param_1 + 0x2e) = 0 -> writes a short at +0x2E
    // param_1[0xc] = +0x30
    // param_1[0xd] = +0x34
    // param_1[0xe] = +0x38

    // +0x20: unknown
    int field_20;
    
    // +0x24: unknown
    int field_24;
    
    // +0x28: unknown
    int field_28;
    
    // +0x2C: short (2 bytes)
    short field_2C;
    
    // +0x2E: short (2 bytes)
    short field_2E;
    
    // +0x30: unknown
    int field_30;
    
    // +0x34: unknown
    int field_34;
    
    // +0x38: unknown
    int field_38;
};

// Constructor at 0x004c01e0
void __thiscall SimObject::SimObject(SimObject *this) {
    // Set vtable pointer to primary vtable (0x00e35f48)
    this->vtable = (void*)0x00e35f48;
    
    // Initialize first flag to 1
    this->field_04 = 1;
    
    // Clear fields 0x08 through 0x10
    this->field_08 = 0;
    this->field_10 = 0; // Actually field_10 at +0x10
    
    // Set field_0C initially to a function pointer (0x00e32808)
    this->field_0C = (void*)0x00e32808;
    
    // Then override field_0C to another pointer (0x00e35f58) - maybe a secondary vtable or offset table
    this->field_0C = (void*)0x00e35f58;
    
    // Clear remaining fields
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0;
    
    // Write zero shorts at offsets 0x2C and 0x2E
    this->field_2C = 0;
    this->field_2E = 0;
    
    // Clear last three dwords
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0;
}