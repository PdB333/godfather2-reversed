// FUNC_NAME: Quaternion::lerp
// Address: 0x00583100
// This function linearly interpolates between two quaternions (stored as 4-float arrays) and writes the result to a third.
// Each Quaternion object has a pointer to its float data at offset +0x8 (after vtable pointer).

class Quaternion {
public:
    float* mData; // +0x8, pointer to 4 floats
    // ... other members likely at other offsets
};

void __thiscall Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& out) {
    // Note: The calling convention passes 'a' in EAX (this), 'b' in param_1, 'out' in param_2, t in param_3.
    // For clean reconstruction, we treat it as a static method.

    float* aData = a.mData;
    float* bData = b.mData;
    float* outData = out.mData;

    outData[0] = aData[0] + (bData[0] - aData[0]) * t;
    outData[1] = aData[1] + (bData[1] - aData[1]) * t;
    outData[2] = aData[2] + (bData[2] - aData[2]) * t;
    outData[3] = aData[3] + (bData[3] - aData[3]) * t;
}