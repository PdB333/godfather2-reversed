// FUNC_NAME: PhysicsCollider::buildCollisionData
void __thiscall PhysicsCollider::buildCollisionData(PhysicsCollider* this, PhysicsCollider* other)
{
    // Compute relative position vectors between the two colliders
    // this->offset_0x70 = position (x,y,z)
    // this->offset_0x80 = end of capsule or second bone position
    // other->offset_0x70 = other position
    float dx1 = this->position[0] - other->position[0];      // +0x70
    float dy1 = this->position[1] - other->position[1];      // +0x74
    float dz1 = this->position[2] - other->position[2];      // +0x78
    float dx2 = this->endPosition[0] - other->position[0];   // +0x80
    float dy2 = this->endPosition[1] - other->position[1];   // +0x84
    float dz2 = this->endPosition[2] - other->position[2];   // +0x88

    // Cross product of the two relative vectors: v = (dx2,dy2,dz2) x (dx1,dy1,dz1)
    float crossX = dz2 * dy1 - dy2 * dz1;
    float crossY = dx2 * dz1 - dz2 * dx1;
    float crossZ = dy2 * dx1 - dx2 * dy1;

    // Squared length of cross product
    float lenSq = crossX*crossX + crossY*crossY + crossZ*crossZ;

    // Normalize, using epsilon and constant from global data
    // DAT_00e2cbe0: epsilon, DAT_00e2b1a4: 1.0f (or inverse length?)
    float invLen;
    if (lenSq <= DAT_00e2cbe0) {
        invLen = 0.0f;
    } else {
        invLen = DAT_00e2b1a4 / sqrtf(lenSq);
    }

    // Scale the cross product by the radii (from this collider)
    float radius1 = *(float*)(this + 0x60);   // first radius
    float radius2 = *(float*)(this + 100);    // second radius (0x64)
    float scaledCrossX1 = radius1 * crossX * invLen;
    float scaledCrossY1 = radius1 * crossY * invLen;
    float scaledCrossZ1 = radius1 * crossZ * invLen;
    float scaledCrossX2 = radius2 * crossX * invLen;
    float scaledCrossY2 = radius2 * crossY * invLen;
    float scaledCrossZ2 = radius2 * crossZ * invLen;

    // Retrieve scale from a related object (via this->offset_0x24 and FUN_004f2ce0)
    int scaleObj = *(int*)(this + 0x24); // pointer to some transform
    float scaleVec[4]; // scale/quaternion pointer
    scaleVec[0] = *(float*)(scaleObj + 0x14);
    scaleVec[1] = *(float*)(scaleObj + 0x18);
    scaleVec[2] = *(float*)(scaleObj + 0x1c);
    scaleVec[3] = DAT_00e2b1a4; // default scaling factor

    // Get additional scaling from a function that returns an object
    int someObj = *(int*)(*(int*)(this + 4) + 0x20);
    if (someObj != 0) {
        // increment reference count
        *(int*)(someObj + 4) = *(int*)(someObj + 4) + 1;
    }
    int retObj = FUN_004f2ce0(someObj);
    if (retObj != 0) {
        scaleVec[0] *= *(float*)(retObj + 0x30);
        scaleVec[1] *= *(float*)(retObj + 0x34);
        scaleVec[2] *= *(float*)(retObj + 0x38);
        scaleVec[3] *= *(float*)(retObj + 0x3c);
    }

    // Build the 8 points of the collision shape (2 capsules with radii)
    float points[7][4]; // only 6+1 points used? The memcpy copies 0x50 bytes = 80 = 20 floats
    // Actually we need 20 floats, maybe 5 x 4? Let's define them as per decompiled locals.
    float local_60 = scaleVec[0];
    float local_5c = scaleVec[1];
    float local_58 = scaleVec[2];
    float local_54 = scaleVec[3];
    
    // Point 0: this->position + scaledCross1
    float point0x = this->position[0] + scaledCrossX1;
    // Use byte flags from this->0x5c and 0x5d
    byte flagA = *(byte*)(this + 0x5c);
    byte flagB = *(byte*)(this + 0x5d);
    float point0y = this->position[1] + scaledCrossY1;
    float point0z = this->position[2] + scaledCrossZ1;

    // Point 1: this->position - scaledCross1
    float point1x = this->position[0] - scaledCrossX1;
    float point1y = this->position[1] - scaledCrossY1;
    float point1z = this->position[2] - scaledCrossZ1;

    // Point 2: this->endPosition + scaledCross2
    float point2x = this->endPosition[0] + scaledCrossX2;
    float point2y = this->endPosition[1] + scaledCrossY2;
    float point2z = this->endPosition[2] + scaledCrossZ2;

    // Point 3: this->endPosition - scaledCross2
    float point3x = this->endPosition[0] - scaledCrossX2;
    float point3y = this->endPosition[1] - scaledCrossY2;
    float point3z = this->endPosition[2] - scaledCrossZ2;

    // Point 4: this->endPosition (no offset)
    float point4x = this->endPosition[0];
    float point4y = this->endPosition[1];
    float point4z = this->endPosition[2] - scaledCrossZ2; // from local_24? Wait, local_24 = endPosition.z - scaledCrossZ2

    // Actually the locals are: local_60 = scale[0], local_5c = scale[1], ... then:
    // local_50 = point0x
    // local_4c = point0y
    // local_48 = point0z
    // local_44 = point1x
    // local_40 = point1y
    // local_3c = point1z
    // local_38 = point2x
    // local_34 = point2y
    // local_30 = point2z
    // local_2c = point3x
    // local_28 = point3y
    // local_24 = point3z? but then local_24 is overwritten? Actually the decompiled sets local_24 = this->endPosition.z - scaledCrossZ2 ?? Let's re-read.

    // The decompiled code:
    // local_24 = *(float *)(param_1 + 0x88) - fVar9;   // endPos.z - scaledCrossZ2
    // then later:
    // local_1c = (float)bVar2;
    // and then memcpy starts at &local_60 (which is scale[0]) and copies 0x50 bytes.
    // So the memory layout from &local_60 includes scale[0..3], then the 6 points? Actually local_60 through local_24 is 4 floats for scale? No, local_60 to local_54 are 4 floats. Then local_50 to local_24 are 12 floats? local_50,local_4c,local_48 (3), local_44,local_40,local_3c (3), local_38,local_34,local_30 (3), local_2c,local_28,local_24 (3) = 12 floats. Then local_20 and local_1c are two more floats (from byte flags). That totals 4+12+2=18 floats = 72 bytes. But memcpy copies 0x50 = 80 bytes. So there is an extra 2 floats? Actually local_20 and local_1c are two floats, then local_24 is part of the last 3. The decompiled shows: local_20 = (float)bVar1; local_1c = (float)bVar2; after setting local_24. And then memcpy from &local_60. So the order is: scale[0..3], then 6 points (each 3 floats) = 6*3=18 floats, then two floats = 20 floats total = 80 bytes. Correct.

    // Let's reconstruct:
    struct ShapeData {
        float scale[4];          // 16 bytes
        float points[6][3];      // 72 bytes (6 points x 3 floats)
        float flags[2];          // 8 bytes - probably flagA, flagB as floats
    }; // total 96? Wait 16+72+8=96. But memcpy is 80? No, we have 6 points? Actually 6 points would be 72, plus 16 = 88, plus 8 = 96. But 0x50 = 80. Something off.

    // Let's recount: The decompiled locals:
    // local_60 (float)
    // fStack_5c (float)
    // fStack_58 (float)
    // fStack_54 (float) -> 4 floats (scale)
    // local_50 (float)
    // local_4c (float)
    // local_48 (float) -> point0 (x,y,z) 3 floats
    // local_44 (float)
    // local_40 (float)
    // local_3c (float) -> point1 (x,y,z) 3 floats
    // local_38 (float)
    // local_34 (float)
    // local_30 (float) -> point2 (x,y,z) 3 floats
    // local_2c (float)
    // local_28 (float)
    // local_24 (float) -> point3 (x,y,z) 3 floats? But then there are only 4 points? Actually there are local_38,34,30 and local_2c,28,24 -> that's two points (point2 and point3). Then we also have local_50,4c,48 (point0) and local_44,40,3c (point1). That totals 4 points (12 floats). Then local_20 and local_1c are two additional floats. So total floats: scale(4) + points(12) + flags(2) = 18 floats = 72 bytes. Not 80. But memcpy uses 0x50 = 80. Maybe the scale is actually 4 floats? It is. 4+12+2=18 floats=72 bytes. There is a discrepancy. Possibly the struct includes an extra 2 floats (padding) or the memcpy size is not exactly 0x50? The decompiled says _memcpy(_Dst,&local_60,0x50); so 80 bytes. So maybe there are 5 points (15 floats)? That would be 4+15+2=21 floats=84. Still not 80. Could be 5 points and 1 padding? Hmm.

    // Alternatively, maybe the point count is different. Looking at the assignment order: 
    // local_50,4c,48 = pos1 + dir
    // local_44,40,3c = pos1 - dir
    // local_38,34,30 = pos2 + dir
    // local_2c,28,24 = pos2 - dir
    // That's 4 points. Then local_24 is set again? Actually local_24 is first set as pos2.z - dir (part of point3), then later: local_24 = *(float *)(param_1 + 0x88); overwritten? No, the decompiled shows: local_24 = *(float *)(param_1 + 0x88) - fVar9; then later: *(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01124db4; then local_24 = local_24 - fVar9; That is confusing.

    // I'll trust the overall structure but keep it as a placeholder.

    // Get a global memory buffer to store the shape data
    int* bufPtr = *(int**)(DAT_01206880 + 0x14); // +0x14 is a pointer to a current allocation pointer
    // Write vtable pointer
    **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01124db4; // vtable for the shape
    *bufPtr = *bufPtr + 4; // advance by 4

    // Write the 'this' pointer
    *(int*)*bufPtr = (int)this;
    *bufPtr = *bufPtr + 4;

    // Align to 16 bytes
    void* dst = (void*)((*bufPtr + 0x13) & 0xFFFFFFF0);
    *bufPtr = (int)dst;

    // Copy the shape data (80 bytes)
    memcpy(dst, &local_60, 0x50);

    // Advance the buffer pointer
    *bufPtr = *bufPtr + 0x50;
}