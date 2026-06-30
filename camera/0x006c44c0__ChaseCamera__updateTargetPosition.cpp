// FUNC_NAME: ChaseCamera::updateTargetPosition
void __thiscall ChaseCamera::updateTargetPosition(int thisPtr, Vector3* outPos, Vector3* inPos) {
    // Offsets: +0x214 = target position (Vector3?), +0x220 = lookAt position (Vector3?), +0x2c0 = distance
    int targetPos = thisPtr + 0x214;
    int lookAtPos = thisPtr + 0x220;
    float dist = (float)FUN_006c3e70(lookAtPos, targetPos); // Compute distance between target and lookAt
    *(float*)(thisPtr + 0x2c0) = dist; // Store distance

    if ((float)DAT_00e44598 < dist) { // If distance exceeds threshold (e.g., max follow distance)
        Vector3 diffVec; // local_c, 12 bytes
        FUN_006c4390(&diffVec, lookAtPos, targetPos, inPos); // Compute difference vector from target to lookAt? Possibly world to local?

        int somePtr = FUN_00471610(); // Get some global object (e.g., player vehicle or camera manager)
        float scale = DAT_00d5eea0; // Frame-time scaling factor

        Vector3 scaledVelocity;
        scaledVelocity.x = *(float*)(somePtr + 0x20) * scale;
        scaledVelocity.y = *(float*)(somePtr + 0x24) * scale;
        scaledVelocity.z = *(float*)(somePtr + 0x28) * scale;

        FUN_006c0b10(outPos, &diffVec, &scaledVelocity, *(float*)(thisPtr + 0x2c0)); // Apply velocity/projection with distance
        return;
    }
    // Otherwise just copy input to output (or do identity transform)
    FUN_006c4390(outPos, lookAtPos, targetPos, inPos);
}