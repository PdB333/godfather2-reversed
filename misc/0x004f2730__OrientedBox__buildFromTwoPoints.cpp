// FUNC_NAME: OrientedBox::buildFromTwoPoints
void __thiscall OrientedBox::buildFromTwoPoints(int this, int other)
{
    // Compute vectors from 'other' position to 'this' position and 'this' secondary point
    float dx1 = *(float *)(this + 0x70) - *(float *)(other + 0x70);
    float dy1 = *(float *)(this + 0x74) - *(float *)(other + 0x74);
    float dz1 = *(float *)(this + 0x78) - *(float *)(other + 0x78);
    
    float dx2 = *(float *)(this + 0x80) - *(float *)(other + 0x70);
    float dy2 = *(float *)(this + 0x84) - *(float *)(other + 0x74);
    float dz2 = *(float *)(this + 0x88) - *(float *)(other + 0x78);

    // Cross product to get normal vector
    float nx = dz2 * dy1 - dy2 * dz1;
    float ny = dx2 * dz1 - dz2 * dx1;
    float nz = dy2 * dx1 - dx2 * dy1;

    float lenSq = nx * nx + ny * ny + nz * nz;
    float invLen;
    if (lenSq <= DAT_00e2cbe0) {
        invLen = 0.0f;
    } else {
        invLen = DAT_00e2b1a4 / __SQRT(lenSq);
    }

    // Scale directions
    int transformPtr = *(int *)(this + 0x24);
    float scale1 = *(float *)(this + 0x60);   // Primary scale
    float scale2 = *(float *)(this + 0x64);   // Secondary scale

    float ox1 = scale1 * nx * invLen;
    float oy1 = scale1 * ny * invLen;
    float oz1 = scale1 * nz * invLen;
    
    float ox2 = scale2 * nx * invLen;
    float oy2 = scale2 * ny * invLen;
    float oz2 = scale2 * nz * invLen;

    // Get base scaling from transform (if any)
    float baseScaleX = *(float *)(transformPtr + 0x14);
    float baseScaleY = *(float *)(transformPtr + 0x18);
    float baseScaleZ = *(float *)(transformPtr + 0x1c);
    float baseScaleW = DAT_00e2b1a4;  // 1.0f

    int allocator = *(int *)(*(int *)(this + 4) + 0x20);
    if (allocator != 0) {
        // Increment reference count
        *(int *)(allocator + 4) = *(int *)(allocator + 4) + 1;
    }
    int scaleData = FUN_004f2ce0(allocator);
    if (scaleData != 0) {
        // Apply additional scaling from scaleData
        baseScaleX *= *(float *)(scaleData + 0x30);
        baseScaleY *= *(float *)(scaleData + 0x34);
        baseScaleZ *= *(float *)(scaleData + 0x38);
        baseScaleW *= *(float *)(scaleData + 0x3c);
    }

    // Build the oriented box corners (two ends, each with front/back face)
    float corners[13]; // Actually 12 coordinates + 2 flags + 4 alignment? We'll use a struct
    corners[0] = baseScaleX;
    corners[1] = baseScaleY;
    corners[2] = baseScaleZ;
    corners[3] = baseScaleW;

    corners[4]  = *(float *)(this + 0x70) + ox1;  // Front face center X
    corners[5]  = *(float *)(this + 0x74) + oy1;
    corners[6]  = *(float *)(this + 0x78) + oz1;
    
    corners[7]  = *(float *)(this + 0x70) - ox1;  // Back face center X
    corners[8]  = *(float *)(this + 0x74) - oy1;
    corners[9]  = *(float *)(this + 0x78) - oz1;
    
    corners[10] = *(float *)(this + 0x80) + ox2;  // Secondary front
    corners[11] = *(float *)(this + 0x84) + oy2;
    corners[12] = *(float *)(this + 0x88) + oz2;
    
    corners[13] = *(float *)(this + 0x80) - ox2;  // Secondary back
    corners[14] = *(float *)(this + 0x84) - oy2;
    // Note: original code set local_24 = *(this+0x88); then subtracted oz2
    // But we handle by storing directly as -oz2 in the struct below

    // Build final structure with vtable pointer
    int *allocPtrPtr = (int *)(DAT_01206880 + 0x14);
    **(void ***)allocPtrPtr = (void *)&PTR_LAB_01124db4; // Set vtable
    *allocPtrPtr = (int)(*allocPtrPtr) + 4;  // Advance

    *(*((int **)*allocPtrPtr)) = this; // Store this pointer? No, original: *(int *)*piVar4 = param_1;
    *(int *) *allocPtrPtr = this;
    *allocPtrPtr = *allocPtrPtr + 4;

    // Copy the constructed data (80 bytes = 0x50) with alignment
    // The local data includes: 4 floats scale, 12 floats for 4 corners, 2 floats for flags (bytes expanded)
    // We'll pack into a contiguous block
    struct OrientedBoxData {
        float scale[4];
        float frontA[3];
        float backA[3];
        float frontB[3];
        float backB[3]; // Note: backB.z is computed from original this+0x88 minus oz2
        float flags[2]; // bytes reinterpreted as floats
    } data;

    data.scale[0] = baseScaleX;
    data.scale[1] = baseScaleY;
    data.scale[2] = baseScaleZ;
    data.scale[3] = baseScaleW;
    
    data.frontA[0] = *(float *)(this + 0x70) + ox1;
    data.frontA[1] = *(float *)(this + 0x74) + oy1;
    data.frontA[2] = *(float *)(this + 0x78) + oz1;
    
    data.backA[0]  = *(float *)(this + 0x70) - ox1;
    data.backA[1]  = *(float *)(this + 0x74) - oy1;
    data.backA[2]  = *(float *)(this + 0x78) - oz1;
    
    data.frontB[0] = *(float *)(this + 0x80) + ox2;
    data.frontB[1] = *(float *)(this + 0x84) + oy2;
    data.frontB[2] = *(float *)(this + 0x88) + oz2;
    
    data.backB[0]  = *(float *)(this + 0x80) - ox2;
    data.backB[1]  = *(float *)(this + 0x84) - oy2;
    data.backB[2]  = *(float *)(this + 0x88) - oz2; // computed as local_24 - oz2
    
    data.flags[0]  = (float)*(char *)(this + 0x5c);
    data.flags[1]  = (float)*(char *)(this + 0x5d);

    void *dest = (void *)((*allocPtrPtr + 0x13) & 0xFFFFFFF0); // align to 16 bytes
    *allocPtrPtr = (int)dest;
    memcpy(dest, &data, 0x50); // copy 80 bytes
    *allocPtrPtr = *allocPtrPtr + 0x50;
}
```