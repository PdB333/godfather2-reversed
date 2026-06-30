// FUNC_NAME: MathUtils::initVec4FromXYZ
// Function at 0x00551260: Initializes a Vector4 on the stack from three source values and a global constant (likely 1.0f for w).
// Used when constructing a homogeneous vector from XYZ with a fixed W component.
// Called from at least two locations (0x00809330, 0x007fab60).

void __cdecl MathUtils::initVec4FromXYZ(const float* sourceXYZ) // param_1 points to 3 floats
{
    // Stack-based temporary Vector4 (offset 0x00=x, 0x04=y, 0x08=z, 0x0C=w)
    float local_x = sourceXYZ[0];   // +0x00
    float local_y = sourceXYZ[1];   // +0x04
    float local_z = sourceXYZ[2];   // +0x08
    // w set from global constant (likely 1.0f for homogeneous coordinates)
    float local_w = *(float*)0x00e2b1a4; // DAT_00e2b1a4, constant from data section

    // Call internal function to perform final initialization/copy (e.g., store or normalize)
    FUN_009f1820(&local_x, 0); // 0 flag indicates no extra processing
}