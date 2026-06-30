// FUNC_NAME: CharacterPhysics::computeGravityEffect
// Address: 0x006c3ad0
// This function computes a gravity effect factor based on the character's orientation
// and stores the result in a member variable. It uses global gravity and clamp constants.
// The result is used to scale gravity influence on the character (e.g., for sloped surfaces).

void __thiscall CharacterPhysics::computeGravityEffect(
    CharacterPhysics *this,
    const EARS::Math::Quaternion *pOrientation) // param_2
{
    float vec1[3]; // local_18, local_14, local_10
    float vec2[3]; // local_24, local_20, local_1c
    float fVar1, fVar2;
    double dVar3, dVar4, dVar5;
    float tempX, tempY, tempZ;
    float result;

    // Copy vectors from orientation quaternion
    // Likely extracts forward and up vectors
    copyVector(vec1, pOrientation);           // FUN_00424fb0
    fVar1 = getLength(pOrientation);          // FUN_00425190 - returns length of some component
    copyVector(vec2, pOrientation);           // FUN_00425060

    // Compute dot products or something with global gravity value
    dVar3 = (double)vec2[1];                  // local_20 is second component of vec2
    sinApprox();                               // FUN_00b99fcb - maybe fsin
    dVar4 = (double)vec2[1];                  // after sin
    cosApprox();                               // FUN_00b99e20 - maybe fcos
    dVar5 = (double)vec2[0];                  // local_24 is first component of vec2

    // Global gravity acceleration constant
    float kGravity = DAT_00e44564;

    // Compute intermediate values
    tempZ = kGravity - (float)(dVar3 * dVar5); // fVar6
    tempX = kGravity - (float)fVar1;            // fVar2
    tempY = kGravity - (float)(dVar4 * dVar5); // fVar7

    // Combine with first vector to compute initial direction
    vec1[0] = tempX * tempZ + vec1[0];           // local_30
    vec1[1] = tempX * (float)dVar3 + vec1[1];   // local_2c
    vec1[2] = tempX * tempY + vec1[2];           // local_28

    // Get another scaling factor (maybe player speed or something)
    fVar1 = computeGravityScale(0, 0, 0);        // FUN_006c3910
    fVar2 = (float)fVar1;

    // Apply second pass
    float v1[3];
    v1[0] = fVar2 * tempZ + vec1[0];             // local_c
    v1[1] = fVar2 * (float)dVar3 + vec1[1];      // local_8
    v1[2] = fVar2 * tempY + vec1[2];             // local_4

    // Compute final result using dot product/distance check
    result = computeClampedFactor(vec1, v1, 0, 0); // FUN_006c9b00

    if (result <= 0.0f) {
        *(int*)(this + 0x298) = 0; // store integer 0 (maybe as boolean)
        return;
    }

    // Clamp result to max allowed global constant
    float kMaxGravity = _DAT_00d5780c;
    if (result > kMaxGravity) {
        result = kMaxGravity;
    }

    // Store the final gravity factor (as float) at offset 0x298
    *(float*)(this + 0x298) = result;
}