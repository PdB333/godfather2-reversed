// FUN_00508a70: addVectorPartToQuaternion
// This function adds the first three components of two 4D vectors (stored in param_2 and param_3)
// into the first three components of the output vector (in_EAX), leaving the fourth component unchanged.
// This is a common operation for applying a 3D delta to the vector part of a quaternion.
void __fastcall addVectorPartToQuaternion(float* outResult, const float* vecA, const float* vecB)
{
    float aw = outResult[3]; // preserve original w component

    // sum the first three components (x, y, z)
    outResult[0] = vecA[0] + vecB[0];
    outResult[1] = vecA[1] + vecB[1];
    outResult[2] = vecA[2] + vecB[2];

    // restore w – it is not affected by the addition
    outResult[3] = aw;
}