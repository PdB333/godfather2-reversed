// FUNC_NAME: scale8FloatArray
// Function address: 0x005145e0
// Role: Scales the first 8 floats of an array by a scalar, likely for dual quaternion or matrix row scaling.
// Input: Array pointer passed implicitly via EAX, scalar on stack (__fastcall or custom convention).
// Returns: void

void scale8FloatArray(float scalar)
{
    // The array pointer is expected in EAX (not shown in signature).
    float* data = in_EAX; // Note: in_EAX is a Ghidra marker; actual register usage.

    // Scale the 8 floats (presumably two 4-component vectors or matrix rows).
    data[0] = data[0] * scalar;
    data[1] = data[1] * scalar;
    data[2] = data[2] * scalar;
    data[3] = data[3] * scalar;
    data[4] = scalar * data[4]; // Equivalent to data[4] *= scalar
    data[5] = scalar * data[5];
    data[6] = scalar * data[6];
    data[7] = scalar * data[7];
}