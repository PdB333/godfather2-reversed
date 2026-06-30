// FUNC_NAME: Transform::isApproximatelyEqual
// Function at 0x0052d3b0: Compares two Transform structures for approximate equality.
// The transform contains an ID (int at +0x00) and 8 floats (+0x10 to +0x2C) representing
// position (3), quaternion (4), and scale (1). Uses global constants for absolute value mask
// and epsilon threshold.

#include <cstdint>

// Global constants (from memory addresses 0x00e44680 and 0x00e2e780)
constexpr uint32_t kFloatAbsMask = 0x7FFFFFFF;   // Masks sign bit for absolute value
constexpr float kEpsilon = 0.0001f;               // Threshold for float comparison

struct Transform {
    int32_t id;        // +0x00: Identifier (e.g., bone or object ID)
    // Padding or other fields at +0x04 to +0x0F (unused in this comparison)
    float data[8];     // +0x10: 8 floats: position (x,y,z), quaternion (x,y,z,w), scale
};

// __fastcall: first parameter (this) in ECX, second in EDX (but decompiler shows in_EAX as second?)
// Actually the decompiler shows param_1 (in ECX) and in_EAX (from EAX). For consistency, we treat
// as a member function comparing *this with *other (passed in some register). We'll assume
// the second pointer is passed via EAX (or EDX if __fastcall with two args). Since the original
// signature is ambiguous, we define as a static function with two parameters.
bool isTransformApproximatelyEqual(const Transform* a, const Transform* b) {
    // Compare IDs
    if (a->id != b->id) {
        return false;
    }

    // Compare all 8 floats using absolute difference with epsilon
    for (int i = 0; i < 8; ++i) {
        // Compute difference, mask sign bit to obtain absolute value via integer reinterpretation
        float diff = a->data[i] - b->data[i];
        uint32_t absDiffBits = reinterpret_cast<uint32_t&>(diff) & kFloatAbsMask;
        float absDiff = *reinterpret_cast<float*>(&absDiffBits);
        if (absDiff > kEpsilon) {
            return false;
        }
    }
    return true;
}