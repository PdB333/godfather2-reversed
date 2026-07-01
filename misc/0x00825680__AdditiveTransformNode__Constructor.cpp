// FUNC_NAME: AdditiveTransformNode::Constructor
// Function address: 0x00825680
// Reconstructed C++: Constructor for combined additive transform node

#include <cstdint>

// Forward declaration of base class initialization (unknown function)
extern void __stdcall sub_8334A0(); // FUN_008334a0

// Known globals (likely constants)
extern const float DAT_00d5780c;  // zero constant
extern const float DAT_00d5d7b8;  // translation X identity
extern const float DAT_00e44620;  // translation Y identity
extern const float DAT_00d5ef88;  // translation Z identity
extern const float DAT_00e44980;  // translation W identity

// Input transform layout (three 4-float vectors at offsets 0x50, 0x60, 0x70)
struct InputTransform {
    // offset 0x50
    float vec0[4]; // e.g., translation
    // offset 0x60
    float vec1[4]; // e.g., rotation part 1
    // offset 0x70
    float vec2[4]; // e.g., rotation part 2 or scale
};

// Resulting combined transform
class AdditiveTransformNode {
public:
    void* vtable;   // offset 0x00 (set to &AdditiveTransformNode_VTABLE)
    // ... base fields (0x04-0x13) from base class
    // offset 0x14
    float resultVec0[4]; // combined translation
    // offset 0x18
    float resultVec1[4]; // combined rotation part 1
    // offset 0x1c
    float resultVec2[4]; // combined rotation part 2
};

// __thiscall constructor: this in ecx, base and additive in param_2 and param_3
AdditiveTransformNode* __thiscall Constructor(AdditiveTransformNode* this,
                                              const InputTransform* base,
                                              const InputTransform* additive)
{
    // Call base class initialization (likely sets vtable and some fields)
    sub_8334A0();

    // Set vtable for this class
    this->vtable = (void*)0x00d73454; // PTR_LAB_00d73454

    // Zero out resultVec1 and resultVec2 (8 floats at offset 0x18-0x1f)
    float zero = DAT_00d5780c; // typically 0.0f
    this->resultVec1[0] = zero;
    this->resultVec1[1] = zero;
    this->resultVec1[2] = zero;
    this->resultVec1[3] = zero;
    this->resultVec2[0] = zero;
    this->resultVec2[1] = zero;
    this->resultVec2[2] = zero;
    this->resultVec2[3] = zero;

    // Placeholder initialisation for resultVec0 (later overwritten)
    this->resultVec0[0] = DAT_00d5d7b8;
    this->resultVec0[1] = DAT_00e44620;
    this->resultVec0[2] = DAT_00d5ef88;
    this->resultVec0[3] = DAT_00e44980;

    // Combine translation vectors (vec0 from input)
    this->resultVec0[0] = base->vec0[0] + additive->vec0[0];
    this->resultVec0[1] = base->vec0[1] + additive->vec0[1];
    this->resultVec0[2] = base->vec0[2] + additive->vec0[2];
    this->resultVec0[3] = base->vec0[3] + additive->vec0[3];

    // Combine first rotation/scale vector (vec1)
    this->resultVec1[0] = base->vec1[0] + additive->vec1[0];
    this->resultVec1[1] = base->vec1[1] + additive->vec1[1];
    this->resultVec1[2] = base->vec1[2] + additive->vec1[2];
    this->resultVec1[3] = base->vec1[3] + additive->vec1[3];

    // Combine second rotation/scale vector (vec2)
    this->resultVec2[0] = base->vec2[0] + additive->vec2[0];
    this->resultVec2[1] = base->vec2[1] + additive->vec2[1];
    this->resultVec2[2] = base->vec2[2] + additive->vec2[2];
    this->resultVec2[3] = base->vec2[3] + additive->vec2[3];

    return this;
}