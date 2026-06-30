// FUNC_NAME: Character::updateRotationTarget
void Character::updateRotationTarget(void)
{
    float deltaTime;
    int configPtr;
    float* targetQuat;
    float* ptrVar1;
    float speed;
    float diff[4];
    float result[3];

    // Virtual call to update something (e.g., animation state)
    (*(void (__thiscall**)(void))(*(int*)(*(int*)(this + 0x2e8) + 0xd0) + 0x14))();

    deltaTime = (float)FUN_009efd10(); // Get time delta

    configPtr = *(int*)(this + 0x2e8); // +0x2e8 points to character config
    targetQuat = *(float**)(this + 0x368); // +0x368 points to transform's rotation quaternion? Or transform object with euler angles at +0x74

    // Compute difference between current and target quaternion (stored in config at +0x160)
    diff[0] = targetQuat[0] - *(float*)(configPtr + 0x160);
    diff[1] = targetQuat[1] - *(float*)(configPtr + 0x164);
    diff[2] = targetQuat[2] - *(float*)(configPtr + 0x168);
    diff[3] = targetQuat[3] - *(float*)(configPtr + 0x16c);

    // Convert difference to a rotation vector (angle-axis) scaled by deltaTime
    FUN_009df220(&diff, deltaTime, result); // result is likely a 3-component Euler angle vector

    // Normalize the target quaternion (optional step)
    FUN_009f4400(targetQuat);

    // Convert the result to Euler angles (or get angles from previous call)
    FUN_009f3dc0(result); // Now result[0], result[1], result[2] hold the rotation for each axis

    // Apply rotation speed factor from config (+0x19c)
    speed = *(float*)(configPtr + 0x19c);
    *(float*)(*(int*)(this + 0x368) + 0x7c) = result[2] * speed; // z
    *(float*)(*(int*)(this + 0x368) + 0x74) = result[0] * speed; // x
    *(float*)(*(int*)(this + 0x368) + 0x78) = result[1] * speed; // y
}