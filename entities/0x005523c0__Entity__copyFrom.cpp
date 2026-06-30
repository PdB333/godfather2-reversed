// FUNC_NAME: Entity::copyFrom
void __thiscall Entity::copyFrom(Entity *this, Entity *source)
{
    // +0x30: pointer to manager/some system
    // +0x10-0x1c: quaternion rotation (16 bytes)
    // +0x40-0x48: direction vector (x,y,z)
    // +0x4c: w component (maybe magnitude or dot)
    // +0x20-0x2c: another rotation or quaternion (cleared later)
    // +0x80, +0x8c: counts for attachment lists at +0x8 and +0xc
    // +0x68: some flag
    // manager structure: +0x8: some bool, +0x74: array of message IDs, +0x78: count

    float x, y, z, w;
    float lenSq;
    float invLen;

    // Lock or begin operation
    FUN_009f0190();
    if (*(int *)(this + 0x30) != 0) {
        FUN_009f01a0(); // unlock or end operation
    }

    // Copy quaternion / rotation
    *(float *)(this + 0x10) = *(float *)(source + 0x10);
    *(float *)(this + 0x14) = *(float *)(source + 0x14);
    *(float *)(this + 0x18) = *(float *)(source + 0x18);
    *(float *)(this + 0x1c) = *(float *)(source + 0x1c);

    // Copy another pair of floats
    *(float *)(this + 0x34) = *(float *)(source + 0x20);
    *(float *)(this + 0x38) = *(float *)(source + 0x24);

    // Copy direction vector and w from source offset 0x40-0x4c? No, source offsets are 0x30-0x3c for these.
    // Actually source mapping: direction vector from source+0x30 to this+0x40, w from source+0x3c to this+0x4c
    // Then also copy something from source+0x40-0x4c to this+0x50-0x60?
    // The decompiler shows: *(this+0x50)=*(source+0x40),*(this+0x54)=*(source+0x44),*(this+0x58)=*(source+0x4c),*(this+0x30)=*(source+0x48)
    // That seems like a different layout. Let's follow the exact copy order.
    // I'll preserve the original field assignments:

    *(float *)(this + 0x40) = *(float *)(source + 0x30);
    *(float *)(this + 0x44) = *(float *)(source + 0x34);
    *(float *)(this + 0x48) = *(float *)(source + 0x38);
    *(float *)(this + 0x4c) = *(float *)(source + 0x3c);
    *(float *)(this + 0x50) = *(float *)(source + 0x40);
    *(float *)(this + 0x54) = *(float *)(source + 0x44);
    *(float *)(this + 0x58) = *(float *)(source + 0x4c);
    *(float *)(this + 0x30) = *(float *)(source + 0x48);
    *(float *)(this + 0x5c) = *(float *)(source + 0x50);
    *(float *)(this + 0x60) = *(float *)(source + 0x54);
    *(byte *)(this + 0x94) = *(byte *)(source + 0x58);

    // Copy rotation matrix or orientation part (4x4?)
    *(float *)(this + 0x40) = *(float *)(source + 0x30);
    *(float *)(this + 0x44) = *(float *)(source + 0x34);
    *(float *)(this + 0x48) = *(float *)(source + 0x38);
    *(float *)(this + 0x4c) = *(float *)(source + 0x3c);

    // Now normalize the (x,y,z) vector at +0x40,+0x44,+0x48 and scale w at +0x4c
    x = *(float *)(this + 0x40);
    y = *(float *)(this + 0x44);
    z = *(float *)(this + 0x48);
    w = *(float *)(this + 0x4c);
    lenSq = x * x + y * y + z * z;
    if (lenSq == 0.0f) {
        invLen = 0.0f;
    } else {
        invLen = 1.0f / sqrtf(lenSq);
    }
    *(float *)(this + 0x40) = x * invLen;
    *(float *)(this + 0x44) = y * invLen;
    *(float *)(this + 0x48) = z * invLen;
    *(float *)(this + 0x4c) = w * invLen;

    // If the manager has a non-zero flag at +8, release/detach source from parent?
    if (*(int *)(*(int *)(this + 0x30) + 8) != 0) {
        FUN_009f1820(source, 0); // detach?
    }

    // Clear rotation/quaternion at +0x20-0x2c (16 bytes)
    *(int *)(this + 0x20) = 0;
    *(int *)(this + 0x24) = 0;
    *(int *)(this + 0x28) = 0;
    *(int *)(this + 0x2c) = 0;

    // Clear attachment list at +0x8 (each element freed by FUN_009f2410)
    int count = *(int *)(this + 0x80);
    if (count > 0) {
        int i = 0;
        do {
            FUN_009f2410(this + 8);
            i++;
        } while (i < count);
    }
    *(int *)(this + 0x80) = 0; // reset count

    // Clear second attachment list at +0xC
    int count2 = *(int *)(this + 0x8c);
    if (count2 > 0) {
        int i = 0;
        do {
            FUN_00a0dec0(this + 0xC);
            i++;
        } while (i < count2);
    }
    *(int *)(this + 0x8c) = 0;
    *(int *)(this + 0x68) = 0; // clear some flag

    // Check if message 0x1300 is already in manager's registered message list
    int msgCount = *(int *)(*(int *)(this + 0x30) + 0x78);
    int *msgList = *(int **)(*(int *)(this + 0x30) + 0x74);
    for (int i = 0; i < msgCount; i++) {
        if (msgList[i] == 0x1300) {
            return; // already registered, do nothing
        }
    }
    // Otherwise send message 0x1300 to this entity
    FUN_009f01f0(0x1300, this, 0);
    return;
}