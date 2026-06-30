// FUNC_NAME: BaseVehicle::applyForcesToVelocity
int __thiscall BaseVehicle::applyForcesToVelocity(BaseVehicle* this, Vector3* outVelocity, int unused, const VehicleForceInput* input)
{
    float fVar1, fVar2, fVar5;
    Vector3 localAccel;   // local_18, local_14, local_10
    Vector3 crossResult;  // local_c, local_8, (stack)

    // Get global environment data (gravity, wind, etc.)
    EnvironmentData* env = reinterpret_cast<EnvironmentData*>(FUN_00471610());

    // Copy initial velocity offset from environment (e.g., wind or base velocity)
    outVelocity->x = reinterpret_cast<float*>(env)[0x30 / 4];       // +0x30
    outVelocity->y = reinterpret_cast<float*>(env)[0x34 / 4];       // +0x34
    outVelocity->z = reinterpret_cast<float*>(env)[0x38 / 4];       // +0x38

    // Apply gravity scaled by input->gravityScale (at input+0x38)
    EnvironmentData* env2 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    float gravityScale = input->gravityScale;                       // +0x38
    outVelocity->x += env2->gravity.x * gravityScale;              // +0x10
    outVelocity->y += env2->gravity.y * gravityScale;              // +0x14
    outVelocity->z += env2->gravity.z * gravityScale;              // +0x18

    // Compute local acceleration from object's orientation and stored force
    EnvironmentData* env3 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    float thrustFactor = this->thrustFactor;                        // +0x234
    float globalThrustMult = DAT_00e445c8;                          // global constant
    FUN_004a0370(&localAccel, &this->orientationMatrix,             // this+0x200
                 &env3->gravity, thrustFactor * globalThrustMult);

    // Apply local acceleration scaled by input->localAccelScale (at input+0x40)
    float localAccelScale = input->localAccelScale;                 // +0x40
    outVelocity->x += localAccel.x * localAccelScale;
    outVelocity->y += localAccel.y * localAccelScale;
    outVelocity->z += localAccel.z * localAccelScale;

    // Compute cross product contributions (torque-induced velocity)
    EnvironmentData* env4 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    EnvironmentData* env5 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    crossResult.x = env4->gravity.y * localAccel.z - env5->gravity.z * localAccel.y;  // +0x14, +0x18
    EnvironmentData* env6 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    EnvironmentData* env7 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    crossResult.y = env6->gravity.z * localAccel.x - env7->gravity.x * localAccel.z;  // +0x18, +0x10
    EnvironmentData* env8 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    EnvironmentData* env9 = reinterpret_cast<EnvironmentData*>(FUN_00471610());
    float cx = env8->gravity.x;    // +0x10
    float cy = env9->gravity.y;    // +0x14
    float antiGravity = DAT_00e44564 - input->antiGravityFactor;    // input+0x3c
    outVelocity->x += antiGravity * crossResult.x;
    outVelocity->y += antiGravity * crossResult.y;
    outVelocity->z += antiGravity * (cx * localAccel.y - cy * localAccel.x);

    // Return pointer to something (likely a result structure)
    return reinterpret_cast<int>(env9) + 0x10;
}