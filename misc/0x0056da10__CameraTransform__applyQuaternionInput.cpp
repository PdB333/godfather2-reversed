// FUNC_NAME: CameraTransform::applyQuaternionInput
void __fastcall CameraTransform::applyQuaternionInput(float* inputQuat) // this in ECX, inputQuat in EDX
{
    float* thisQuat;    // unaff_ESI -> this (first 4 floats)
    float* thisVec;     // unaff_ESI + 4 (next 3 or 4 floats)
    float fVar2;        // constant from global
    float fVar3, fVar4, fVar5; // zeros?
    float fVar6;        // damping factor
    float local_30, local_2c, local_28, local_24; // temporary vector for rotation source

    fVar3 = 0.0f;
    fVar4 = 0.0f;
    fVar5 = 0.0f;

    // constants: likely 1.0 and something else
    fVar6 = DAT_00e44564 - DAT_00e2b1a4 / (inputQuat[0]*inputQuat[0] + inputQuat[1]*inputQuat[1] + inputQuat[2]*inputQuat[2] + inputQuat[3]*inputQuat[3]);

    fVar2 = DAT_00e44564; // e.g. 1.0

    // Call to internal state update (returns pointer via EDX)
    float* somePointer = static_cast<float*>(updateInternalState());

    // Access third float of something? (offset +0xC from pointer)
    thisQuat[3] = fVar2 - somePointer[3]; // [0xC/4 = 3]

    // Scale current quaternion by damping
    thisQuat[0] = fVar6 * thisQuat[0];
    thisQuat[1] = fVar6 * thisQuat[1];
    thisQuat[2] = fVar6 * thisQuat[2];
    thisQuat[3] = fVar6 * thisQuat[3];

    // Build a temporary vector from differences to constant
    local_30 = fVar2 - thisQuat[0];
    local_2c = fVar2 - thisQuat[1];
    local_28 = fVar2 - thisQuat[2];
    local_24 = thisQuat[3]; // keep as is

    // Second utility function: rotates or transforms the vector part
    float rotationResult[7]; // local_20 buffer (size 28 bytes = 7 floats)
    quaternionRotateVector(rotationResult, &local_30, thisVec);

    // Negate first component of the vector part
    thisVec[0] = 0.0f - thisVec[0];
    thisVec[1] = fVar3 - thisVec[1];
    thisVec[2] = fVar4 - thisVec[2];
    thisVec[3] = fVar5 - thisVec[3];

    // Force fourth component to 0 (keeping only 3D vector)
    thisVec[3] = 0.0f;
}