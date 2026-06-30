// FUNC_NAME: multiply4DComponentWiseWithFixedW
// Function address: 0x00582d80
// Role: Performs component-wise multiplication of two 4-element float vectors (e.g. quaternions or homogeneous coordinates)
// and then forces the fourth component to a global constant (DAT_00e2b1a4).
// This appears to be a debug or specialized operation; note the overwrite of the computed w value.

// Standard EA EARS engine utility, likely part of a math library (EARS::Math or similar)
// Calling convention: __fastcall (output pointer in EAX, inputs in ECX/EDX? decompiler shows EAX as first param)

void __fastcall multiply4DComponentWiseWithFixedW(float* out, float* a, float* b)
{
    float w_a = a[3]; // store fourth component of a (though unused in final assignment)
    float x_a = a[0];
    float y_a = a[1];
    float z_a = a[2];

    float w_b = b[3];
    float x_b = b[0];
    float y_b = b[1];
    float z_b = b[2];

    out[0] = x_a * x_b;
    out[1] = y_a * y_b;
    out[2] = z_a * z_b;
    out[3] = w_a * w_b; // computed product (temporary)

    // Overwrite with global constant - purpose unknown
    // DAT_00e2b1a4 is a float value set elsewhere; may be related to identity or special state
    out[3] = DAT_00e2b1a4;
}