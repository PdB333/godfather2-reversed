// FUNC_NAME: Vector3::Normalize
void __fastcall Vector3::Normalize(float *outVector)
{
    float x = *in_EAX;                        // Input vector X component (this.x)
    float y = in_EAX[1];                      // Input vector Y component (this.y)
    float z = in_EAX[2];                      // Input vector Z component (this.z)
    float lengthSq = x * x + y * y + z * z;   // Squared length
    float invLen;

    // Avoid division by zero; use small epsilon (likely 0.0f)
    if (lengthSq <= 1e-8f)   // DAT_00e2cbe0 (probably epsilon)
    {
        invLen = 0.0f;
    }
    else
    {
        invLen = 1.0f / sqrtf(lengthSq);   // DAT_00e2b1a4 is 1.0f
    }

    outVector[0] = x * invLen;   // Write normalized components to output
    outVector[1] = y * invLen;
    outVector[2] = z * invLen;
}