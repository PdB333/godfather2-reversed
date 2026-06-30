// FUNC_NAME: AnimationBlendNode::lerpTransform
// Function address: 0x00582bf0
// Role: Interpolates a 4D vector (likely quaternion or position) from a source node to this node,
//        using a scaling factor. Calls an external quaternion interpolation helper and overrides the
//        fourth component with a global constant (possibly w-component of a unit quaternion).

#include <cstdint>

// Global constant (DAT_00e2b1a4) - appears to be a fixed value used for the 4th component
extern const float gBlendConstant;

// External interpolation function (FUN_0056cc80) - likely performs quaternion slerp/lerp
void interpolateQuaternion(float t, float outQuat[4]);

// Struct representing an animation blend node with a 4-float vector at offset +0x10
struct AnimationBlendNode {
    char pad[0x10];      // unknown fields before the vector
    float data[4];       // +0x10: 4-component data (e.g., position + scale, or quaternion)
};

// Member function: blends this node's vector toward 'other' using factor t
// ESI = this, EDI = other, param_1 = t (passed as float on stack)
void AnimationBlendNode::lerpTransform(float t, AnimationBlendNode* other) {
    // Local quaternion for interpolation (output not used further, likely for side-effects)
    float localQuat[4] = { 0.0f, 0.0f, 0.0f, gBlendConstant };
    interpolateQuaternion(t, localQuat);

    // Scale source vector components by t
    for (int i = 0; i < 4; ++i) {
        data[i] = t * other->data[i];
    }
    // Force the fourth component to the global constant (overwrites the scaled value)
    data[3] = gBlendConstant;
}