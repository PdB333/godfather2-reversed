// FUNC_NAME: getScaledVector
// Function address: 0x00836290
// Role: Scales a 4-component vector (stored at offsets +0x50..+0x5C) by a scalar factor (at +0xA0) and writes the result to an output array.

void __thiscall getScaledVector(float *outVector) const
{
    float scalar = *(float *)(this + 0xA0);   // +0xA0: scalar factor (e.g., speed, magnitude)
    float x = *(float *)(this + 0x50);        // +0x50: vector component X
    float y = *(float *)(this + 0x54);        // +0x54: vector component Y
    float z = *(float *)(this + 0x58);        // +0x58: vector component Z
    float w = *(float *)(this + 0x5C);        // +0x5C: vector component W (e.g., quaternion w or homogeneous coordinate)

    outVector[0] = scalar * x;
    outVector[1] = scalar * y;
    outVector[2] = scalar * z;
    outVector[3] = scalar * w;
}