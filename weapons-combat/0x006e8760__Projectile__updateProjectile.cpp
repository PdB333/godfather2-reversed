// FUNC_NAME: Projectile::updateProjectile
void __thiscall Projectile::updateProjectile(void* thisPtr, float deltaTime) {
    // Structure offsets (relative to thisPtr):
    // +0x20: velocity (Vector3: x,y,z)
    // +0x44: currentPosition (Vector3)
    // +0x68: outputPosition (Vector3)
    // +0x74: secondOutputPosition (Vector3) // used when mode == 8
    // +0x88: mode (byte) – bit0 = frozen, 4 = backward, 8 = dual output

    float vx = *(float*)((char*)thisPtr + 0x20);
    float vy = *(float*)((char*)thisPtr + 0x24);
    float vz = *(float*)((char*)thisPtr + 0x28);
    float px = *(float*)((char*)thisPtr + 0x44);
    float py = *(float*)((char*)thisPtr + 0x48);
    float pz = *(float*)((char*)thisPtr + 0x4c);

    float dx = vx * deltaTime;
    float dy = vy * deltaTime;
    float dz = vz * deltaTime;

    byte mode = *(byte*)((char*)thisPtr + 0x88);

    if (mode & 1) {
        // Frozen: copy current position to output, add special gravity only to output y
        *(float*)((char*)thisPtr + 0x68) = px;
        *(float*)((char*)thisPtr + 0x6c) = py + DAT_00d5fb68; // +0x6c is y of output, add constant
        *(float*)((char*)thisPtr + 0x70) = pz;
        // Copy unchanged current position to second output (no gravity added)
        *(float*)((char*)thisPtr + 0x74) = px;
        *(float*)((char*)thisPtr + 0x78) = py;
        *(float*)((char*)thisPtr + 0x7c) = pz;
        return;
    }

    if (mode == 4) {
        // Backward motion (subtract velocity * dt)
        *(float*)((char*)thisPtr + 0x68) = px - dx;
        *(float*)((char*)thisPtr + 0x6c) = py - dy;
        *(float*)((char*)thisPtr + 0x70) = pz - dz;
    } else {
        // Default forward motion
        *(float*)((char*)thisPtr + 0x68) = px + dx;
        *(float*)((char*)thisPtr + 0x6c) = py + dy;
        *(float*)((char*)thisPtr + 0x70) = pz + dz;
        if (mode == 8) {
            // Second output also set to forward motion (same as first output)
            *(float*)((char*)thisPtr + 0x74) = px + dx;
            *(float*)((char*)thisPtr + 0x78) = py + dy;
            *(float*)((char*)thisPtr + 0x7c) = pz + dz;
        }
    }

    // Apply gravity (standard) to y-component of output only
    *(float*)((char*)thisPtr + 0x6c) = *(float*)((char*)thisPtr + 0x6c) + DAT_00d5ca18;
}