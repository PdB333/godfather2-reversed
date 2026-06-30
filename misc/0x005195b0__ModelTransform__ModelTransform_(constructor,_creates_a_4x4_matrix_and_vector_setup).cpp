// FUNC_NAME: ModelTransform::ModelTransform (constructor, creates a 4x4 matrix and vector setup)
// Address: 0x005195b0
// This is a constructor that initializes a transformation structure containing a 4x4 matrix, a 4-element vector, and several additional fields.
// The matrix can be provided via a pointer in EAX (or null for identity). The vector is passed via stack. Two integer fields and a pointer field are also set.
// After calling an internal sub‑constructor (FUN_00424470), two 8‑byte values from a global (unaff_ESI) are copied into the object, and several fields are zeroed.

#include <cstdint>

// Forward declaration of internal sub‑constructor
int __fastcall SubConstructor(void* self); // FUN_00424470, returns self in EDX

// Global vtable pointer for ModelTransform (from ghidra label PTR_LAB_00e381a0)
extern void* ModelTransform_vtable;

// Global constant 1.0f (from DAT_00e2b1a4)
extern const float IDENTITY_VAL;

// Global pointer to source of two 8‑byte values (e.g., some parent transform data)
extern const uint64_t* gUnknGlobal; // unaff_ESI

// Structure offsets (relative to this):
// +0x00: vtable pointer
// +0x10: int32 field (field_10)
// +0x18: uint64_t field (field_18)
// +0x20: uint64_t field (field_20)
// +0x28: int32 field (field_28)
// +0x2C: int32 field (field_2C)
// +0x30: float[4] vector4
// +0x40: float[4][4] matrix (16 floats, total 64 bytes)
// +0xC0: int32 field (field_C0)
// +0xC4: int32 field (field_C4)
// +0xC8: int32 field (field_C8)

struct ModelTransform {
    void* vtable;          // +0x00
    int32_t field_10;      // +0x10
    uint64_t field_18;     // +0x18
    uint64_t field_20;     // +0x20
    int32_t field_28;      // +0x28
    int32_t field_2C;      // +0x2C
    float vector4[4];      // +0x30
    float matrix[4][4];    // +0x40
    int32_t field_C0;      // +0xC0
    int32_t field_C4;      // +0xC4
    int32_t field_C8;      // +0xC8
};

// Constructor: returns 'this' (as int for legacy reasons)
// Parameters:
//   srcMatrix (EAX): pointer to 16 floats forming a 4x4 matrix, or null for identity
//   param_3: value to store at field_C0
//   srcVector: pointer to 4 floats to copy into vector4
//   param_5: value to store at field_28
//   param_6: value to store at field_2C
int __fastcall ModelTransform_constructor(
    ModelTransform* this_,          // param_1 (ECX) – unused, actual this is param_2
    ModelTransform* thisObj,        // param_2 (EDX) – the object to initialize
    int param_3,                    // stack +4
    float* srcVector,               // stack +8
    int param_5,                    // stack +12
    int param_6                     // stack +16
) {
    // Note: this_ is a dummy from the fastcall convention; actual this is thisObj.
    ModelTransform* self = thisObj;
    float f5, f6, f7, f8;

    // Set vtable
    self->vtable = &ModelTransform_vtable;

    // Get the optional source matrix pointer from EAX (passed in register, not in prototype)
    float* srcMatrix = reinterpret_cast<float*>(this_); // actually EAX is stored in param_1, but we rename for clarity

    if (srcMatrix == nullptr) {
        // Identity matrix: diagonal = IDENTITY_VAL, others = 0
        self->matrix[0][0] = IDENTITY_VAL;
        self->matrix[0][1] = 0.0f;
        self->matrix[0][2] = 0.0f;
        self->matrix[0][3] = 0.0f;
        self->matrix[1][0] = 0.0f;
        self->matrix[1][1] = IDENTITY_VAL;
        self->matrix[1][2] = 0.0f;
        self->matrix[1][3] = 0.0f;
        self->matrix[2][0] = 0.0f;
        self->matrix[2][1] = 0.0f;
        self->matrix[2][2] = IDENTITY_VAL;
        self->matrix[2][3] = 0.0f;
        // The fourth row will be set later
        f5 = 0.0f;
        f6 = 0.0f;
        f7 = 0.0f;
        f8 = IDENTITY_VAL;
    } else {
        // Copy full 4x4 matrix from source
        self->matrix[0][0] = srcMatrix[0];
        self->matrix[0][1] = srcMatrix[1];
        self->matrix[0][2] = srcMatrix[2];
        self->matrix[0][3] = srcMatrix[3];
        self->matrix[1][0] = srcMatrix[4];
        self->matrix[1][1] = srcMatrix[5];
        self->matrix[1][2] = srcMatrix[6];
        self->matrix[1][3] = srcMatrix[7];
        self->matrix[2][0] = srcMatrix[8];
        self->matrix[2][1] = srcMatrix[9];
        self->matrix[2][2] = srcMatrix[10];
        self->matrix[2][3] = srcMatrix[11];
        f5 = srcMatrix[12];
        f6 = srcMatrix[13];
        f7 = srcMatrix[14];
        f8 = srcMatrix[15];
    }
    // Set the fourth row of the matrix
    self->matrix[3][0] = f5;
    self->matrix[3][1] = f6;
    self->matrix[3][2] = f7;
    self->matrix[3][3] = f8;

    // Copy 4 floats from srcVector into vector4 at +0x30
    self->vector4[0] = srcVector[0];
    self->vector4[1] = srcVector[1];
    self->vector4[2] = srcVector[2];
    self->vector4[3] = srcVector[3];

    // If first three components of vector4 equal IDENTITY_VAL (1.0f), set the fourth to 1.0f, else 0
    if (self->vector4[0] == IDENTITY_VAL &&
        self->vector4[1] == IDENTITY_VAL &&
        self->vector4[2] == IDENTITY_VAL) {
        self->vector4[3] = IDENTITY_VAL;
    } else {
        self->vector4[3] = 0.0f;
    }

    // Store integers at offsets 0x28 and 0x2C
    self->field_28 = param_5;
    self->field_2C = param_6;

    // Call internal sub‑constructor (likely initializes other engine‑specific fields)
    int ret_edx = SubConstructor(self); // returns self in EDX

    // After sub‑constructor, set additional fields using the returned pointer (should be self)
    ModelTransform* obj = reinterpret_cast<ModelTransform*>(ret_edx);
    obj->field_C0 = param_3;
    obj->field_18 = gUnknGlobal[0];   // copy 8 bytes from global
    obj->field_20 = gUnknGlobal[1];   // copy next 8 bytes
    obj->field_10 = 0;
    obj->field_C8 = 0;               // offset 0xC8 (200 decimal)
    obj->field_C4 = 0;

    return reinterpret_cast<int>(obj);
}