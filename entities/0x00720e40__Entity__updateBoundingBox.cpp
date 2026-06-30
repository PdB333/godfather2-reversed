// FUNC_NAME: Entity::updateBoundingBox
void __fastcall Entity::updateBoundingBox(int *this) {
    float fVar1;
    float tempX, tempY, tempZ;
    int *vtable;
    float velocity[3];
    float localVertices[8*3];
    int i;
    float minX, maxX, minY, maxY, minZ, maxZ;
    float translation[3];
    float scaledVelocity[3];

    // +0x08: flag indicating if bounding box needs update
    if (this[2] == 0) {
        return;
    }

    // Get current time (possibly frame delta)
    uint time = FUN_00471610();

    // Get local vertices (8 corners) into localVertices array
    // this+8 points to vertex data (offset 0x20)
    FUN_00720980(localVertices, this + 8, 8, time);

    // Copy first vertex to initialize min/max
    maxX = localVertices[0];
    minX = localVertices[0];
    maxY = localVertices[1];
    minY = localVertices[1];
    maxZ = localVertices[2];
    minZ = localVertices[2];

    // Get vtable pointer from this[0] (offset 0x00)
    if (this[0] != 0) {
        vtable = (int *)(this[0] - 0x48); // -0x48 to get vtable base
    } else {
        vtable = 0;
    }

    // Call virtual function at vtable+0x4c (likely "getVelocity")
    // Returns a vector (x,y,z) into output variables
    (*(code **)(*vtable + 0x4c))(&velocity[0]);

    // Zero velocity? Actually it's resetting some locals - likely decompiler artifact
    velocity[0] = 0.0f;
    velocity[1] = 0.0f;
    // velocity[2] is set from fStack_98 which came from the call

    // Normalize? Actually this function normalizes the input vector (identity)
    FUN_0056afa0(&velocity[0], &velocity[0]);

    // Scale velocity by time factor (DAT_00d61fec is some frame time constant)
    scaledVelocity[0] = velocity[0] * DAT_00d61fec;
    scaledVelocity[1] = velocity[1] * DAT_00d61fec;
    scaledVelocity[2] = velocity[2] * DAT_00d61fec;

    // Get current translation from this+0x2c (offset 0xB0)
    translation[0] = (float)this[0x2c];
    translation[1] = (float)this[0x2d];
    translation[2] = (float)this[0x2e];

    // Normalize translation vector
    FUN_0056afa0(&translation[0], &translation[0]);

    // Apply damping to translation (DAT_00d61fe8 is damping factor)
    this[0x2c] = (int)((float)this[0x2c] * DAT_00d61fe8);
    this[0x2d] = (int)((float)this[0x2d] * DAT_00d61fe8);
    this[0x2e] = (int)((float)this[0x2e] * DAT_00d61fe8);

    // Add velocity * dt to translation
    this[0x2c] = (int)((float)this[0x2c] + scaledVelocity[0]);
    this[0x2d] = (int)((float)this[0x2d] + scaledVelocity[1]);
    this[0x2e] = (int)((float)this[0x2e] + scaledVelocity[2]);

    // Recalculate bounding box from transformed local vertices
    for (i = 0; i < 8; i++) {
        float x = localVertices[i*3+0] + (float)this[0x2c];
        float y = localVertices[i*3+1] + (float)this[0x2d];
        float z = localVertices[i*3+2] + (float)this[0x2e];

        // Store specific vertices at fixed slots (index 1,7,4,6)
        if (i == 1) {
            // Store X,Y (two floats) as a 64-bit at this+0x80 (offset 0x80)
            *(ulonglong *)(this + 0x20) = CONCAT44(y, x);
            this[0x22] = (int)z; // this+0x88 (offset 0x88)
        } else if (i == 7) {
            *(ulonglong *)(this + 0x23) = CONCAT44(y, x); // this+0x8C
            this[0x25] = (int)z; // this+0x94
        } else if (i == 4) {
            *(ulonglong *)(this + 0x26) = CONCAT44(y, x); // this+0x98
            this[0x28] = (int)z; // this+0xA0
        } else if (i == 6) {
            *(ulonglong *)(this + 0x29) = CONCAT44(y, x); // this+0xA4
            this[0x2b] = (int)z; // this+0xAC
        }

        // Update min/max
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
        if (z < minZ) minZ = z;
        if (z > maxZ) maxZ = z;
    }

    // Finalize the bounding box (likely stores min/max vectors)
    FUN_009f5240((int)&minX);
}