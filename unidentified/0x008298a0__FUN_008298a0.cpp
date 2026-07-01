// FUNC_NAME: UnknownClass::constructor

// Reconstructed C++ for constructor at 0x008298a0
// This function initializes an object of an unknown class,
// setting its vtable pointer and several member fields from global data.

// Forward declaration of base class constructor called
void __fastcall baseClassConstructor(void* this);

// Global constants (likely vtable pointer and some configuration values)
extern void* g_unknownVtable;            // PTR_LAB_00d736c0
extern uint32_t g_someConstant1;        // _DAT_00d5780c
extern uint32_t g_someConstant2;        // _DAT_00d735f0
extern uint32_t g_someConstant3;        // _UNK_00d735f4
extern uint32_t g_someConstant4;        // _UNK_00d735f8
extern uint32_t g_someConstant5;        // _UNK_00d735fc

class UnknownClass {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Unknown fields (offsets based on param_1[x])
    // +0x4C (param_1[0x13])
    uint32_t field_0x4C;
    // +0x50 (param_1[0x14])
    uint32_t field_0x50;
    // +0x54 (param_1[0x15])
    uint32_t field_0x54;
    // +0x60 (param_1[0x18])
    uint32_t field_0x60;
    // +0x64 (param_1[0x19])
    uint32_t field_0x64;
    // +0x68 (param_1[0x1A])
    uint32_t field_0x68;
    // +0x6C (param_1[0x1B])
    uint32_t field_0x6C;
    // ... other members may exist beyond these offsets

    // Constructor (__fastcall, this in ECX, no other explicit params)
    // Returns this pointer
    void* __fastcall constructor(UnknownClass* this);
};

void* __fastcall UnknownClass::constructor(UnknownClass* this) {
    // Step 1: Call base class constructor (likely from derived hierarchy)
    baseClassConstructor(this);

    // Step 2: Set vtable pointer
    this->vtable = &g_unknownVtable;

    // Step 3: Initialize fields at offset 0x4C and 0x50 with same global constant
    this->field_0x4C = g_someConstant1;
    this->field_0x50 = g_someConstant1;  // Same value (probably copied identifier)

    // Step 4: Zero out field at offset 0x54
    this->field_0x54 = 0;

    // Step 5: Initialize vector-like members at offsets 0x60, 0x64, 0x68, 0x6C
    // These might be a 3D vector or quaternion, or four separate values
    this->field_0x60 = g_someConstant2;
    this->field_0x64 = g_someConstant3;
    this->field_0x68 = g_someConstant4;
    this->field_0x6C = g_someConstant5;

    // Return this pointer as per constructor convention
    return this;
}