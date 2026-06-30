// FUNC_NAME: Quaternion::transformAndAddVector
void Quaternion::transformAndAddVector(const float* inVec, float* outAccum) {
    // inVec is param_1, outAccum is in ESI (unaff_ESI)
    // this (quaternion) is in ECX (in_EAX)
    float local_30, local_2c, local_28, local_24;
    // DAT_00e44564 is likely 0.0f (constant zero)
    local_30 = 0.0f - this[0];  // -x
    local_2c = 0.0f - this[1];  // -y
    local_28 = 0.0f - this[2];  // -z
    local_24 = this[3];         // w (conjugate)

    // Initialize temporary quaternion buffer (likely identity)
    float tempQuat[7]; // local_20 is unused; just a placeholder
    FUN_0056cba0();
    FUN_0056cba0(tempQuat, &local_30); // multiply: conjugate * something?

    float vx = inVec[0], vy = inVec[1], vz = inVec[2];
    outAccum[0] += vx;
    outAccum[1] += vy;
    outAccum[2] += vz;
    outAccum[3] = 0.0f; // ensure w=0 for 3D vector
}