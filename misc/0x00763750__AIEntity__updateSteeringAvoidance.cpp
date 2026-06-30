// FUNC_NAME: AIEntity::updateSteeringAvoidance
float __thiscall AIEntity::updateSteeringAvoidance(int thisPtr, int obstacleOrTarget)
{
    float fVar1;           // +0xd4 - maxSpeed or threshold
    uint64_t uVar2;        // +0xc8 - packed velocity (two floats)
    float fVar3;           // combined time + offset
    char cVar4;            // boolean from line of sight
    float fVar5;           // temporary float10 (double)
    float fVar6;           // time delta from +0x78
    uint64_t uStack_50;    // copy of velocity
    float fStack_48;       // +0xd0 - z component of something
    float fStack_44;       // predicted x
    float fStack_40;       // predicted y
    float fStack_3c;       // predicted z
    float auStack_38[3];   // obstacle position (12 bytes)
    float auStack_2c[3];   // temporary vector for avoidance direction
    float local_20[6];     // 24 bytes, likely target position + other data
    float fStack_8;        // time from vtable call

    // Get target or obstacle position into local_20
    FUN_00763550(obstacleOrTarget, local_20);

    // Get current time (or delta) from a vtable at +0x58 -> +0x2c4
    fVar5 = (float10)(**(code **)(**(int **)(thisPtr + 0x58) + 0x2c4))();
    fVar1 = *(float *)(thisPtr + 0xd4);
    fVar3 = (float)(fVar5 + (float10)fStack_8 + (float10)*(float *)(thisPtr + 0xc4));
    cVar4 = FUN_00762f80(local_20, auStack_38);  // converts to obstacle position, returns true if valid
    if (cVar4 != '\0') {
        *(uint *)(thisPtr + 0xe8) = *(uint *)(thisPtr + 0xe8) & 0xfffffffd; // clear bit 1 (flag)

        fStack_48 = *(float *)(thisPtr + 0xd0);
        uVar2 = *(uint64_t *)(thisPtr + 200); // +0xc8 - packed velocity (x,y in low/high)
        fVar6 = *(float *)(*(int *)(thisPtr + 0x78) + 0xc4) -
                *(float *)(*(int *)(thisPtr + 0x78) + 0xc0); // time step from some component

        uStack_50._0_4_ = (float)uVar2;
        fStack_44 = *(float *)(thisPtr + 0xac) * fVar6 + (float)uStack_50; // predicted x = startX + velX*dt
        uStack_50._4_4_ = (float)((ulonglong)uVar2 >> 0x20);
        fStack_40 = *(float *)(thisPtr + 0xb0) * fVar6 + uStack_50._4_4_; // predicted y = startY + velY*dt
        fStack_3c = *(float *)(thisPtr + 0xb4) * fVar6 + fStack_48;       // predicted z = startZ + velZ*dt

        uStack_50 = uVar2; // restore original packed velocity

        // Compute squared distance between obstacle position and predicted position, store avoidance direction in auStack_2c
        fVar5 = (float10)FUN_0084cb90(auStack_38, &uStack_50, &fStack_44, auStack_2c, 0);
        if (SQRT(fVar5) < (float10)fVar3) {
            fVar5 = (float10)FUN_00762b20(auStack_38, auStack_2c, (float)SQRT(fVar5), fVar3);
            return fVar5;
        }
    }
    return (float10)fVar1; // return default threshold if no obstacle
}