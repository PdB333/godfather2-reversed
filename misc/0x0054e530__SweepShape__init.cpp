// FUNC_NAME: SweepShape::init
void __thiscall SweepShape::init(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                                  float param_5, undefined4 param_6, float* param_7, undefined4 param_8, char param_9)
{
    float fVar1;
    float fVar2;
    float fVar3;
    undefined8 uVar4;
    undefined4* puVar5;
    undefined4 uVar6;
    int iVar7;
    float10 fVar8;
    float fVar9;
    undefined4 local_7c;
    undefined4 local_78;
    undefined4 local_70;
    undefined4 local_6c;
    float local_68;
    undefined4 local_64;
    undefined4 local_60;
    undefined4 local_5c;
    undefined4 local_58;
    undefined4 local_54;
    float local_50;
    undefined4 local_4c;
    float local_40;
    float local_3c;
    float local_38;
    float local_34;
    undefined4 local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined4 local_24;
    float local_20;
    undefined4 local_1c;
    char local_18;

    // Release existing child shapes if any
    if (*(int*)(param_1 + 0x18) != 0) {
        releaseShape(*(int*)(param_1 + 0x18)); // FUN_009e7530
    }
    *(undefined4*)(param_1 + 0x18) = 0;

    // Release and free child at mShape1
    if (*(int*)(param_1 + 0x1c) != 0) {
        puVar5 = *(undefined4**)(*(int*)(param_1 + 0x1c) + 0x10); // ref count structure?
        if ((*(short*)(puVar5 + 1) != 0) &&
            (*(short*)((int)puVar5 + 6) = *(short*)((int)puVar5 + 6) - 1,
             *(short*)((int)puVar5 + 6) == 0)) {
            (**(code**)*puVar5)(1); // call virtual destructor?
        }
        freeMemory(); // FUN_009f01a0
    }

    // Release and free child at mShape2
    if (*(int*)(param_1 + 0x20) != 0) {
        puVar5 = *(undefined4**)(*(int*)(param_1 + 0x20) + 0x10);
        if ((*(short*)(puVar5 + 1) != 0) &&
            (*(short*)((int)puVar5 + 6) = *(short*)((int)puVar5 + 6) - 1,
             *(short*)((int)puVar5 + 6) == 0)) {
            (**(code**)*puVar5)(1);
        }
        freeMemory(); // FUN_009f01a0
    }

    // Copy direction from param_7[4..6] and normalize
    fVar1 = param_7[6];
    fVar2 = param_7[5];
    *(float*)(param_1 + 0x90) = param_7[4];
    *(float*)(param_1 + 0x94) = fVar2;
    fVar2 = 1.0f; // DAT_00e2b1a4 (likely 1.0)
    *(float*)(param_1 + 0x98) = fVar1;
    *(float*)(param_1 + 0x9c) = fVar2;

    fVar2 = *(float*)(param_1 + 0x90);
    fVar3 = *(float*)(param_1 + 0x94);
    fVar8 = (float10)squareRoot(fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1); // FUN_00414a80
    fVar9 = 1.0f / (float)fVar8; // DAT_00e2b1a4 is 1.0
    *(float*)(param_1 + 0x90) = fVar2 * fVar9;
    *(float*)(param_1 + 0x94) = fVar3 * fVar9;
    *(float*)(param_1 + 0x98) = fVar1 * fVar9;
    *(float*)(param_1 + 0x9c) = *(float*)(param_1 + 0x9c) * fVar9; // scale the 4th component (was 1.0)

    fVar1 = param_7[2];
    fVar2 = param_7[1];
    uVar4 = *(undefined8*)(param_7 + 0xc); // extra data from param_7[3..4]? double?
    fVar9 = param_7[0xe]; // param_7[14]? Actually offset 0xe * 4 = 56 bytes? Decompiled shows param_7[0xe] (index 14)
    fVar3 = *param_7;

    // Store lengths of three axis vectors from param_7
    *(float*)(param_1 + 0x84) = (float)fVar8; // length of direction
    *(float*)(param_1 + 0x80) = squareRoot(fVar1 * fVar1 + fVar2 * fVar2 + fVar3 * fVar3); // length of first axis
    *(float*)(param_1 + 0x88) = squareRoot(param_7[10] * param_7[10] + param_7[9] * param_7[9] + param_7[8] * param_7[8]); // length of second axis

    *(undefined4*)(param_1 + 0xd4) = param_8; // extra user data

    // Create two child shapes
    uVar6 = createShape(param_2, param_3, param_5, param_8); // FUN_0054dd80
    *(undefined4*)(param_1 + 0x1c) = uVar6; // mShape1

    uVar6 = createShape(param_2, param_4, param_6, param_8); // FUN_0054dd80
    *(undefined4*)(param_1 + 0x20) = uVar6; // mShape2

    *(undefined4*)(param_1 + 0x18) = *(undefined4*)(param_1 + 0x1c); // mShape0 = mShape1 (primary)

    attachShape(*(undefined4*)(param_1 + 0x1c)); // FUN_009e7450

    // Prepare a local stack buffer for constructing a node
    local_28 = *(undefined4*)(param_1 + 0x18);
    local_50 = 1.0f; // DAT_00e2b1a4
    local_20 = *(float*)(param_1 + 0x80) * param_5; // size scaled by param_5
    local_24 = 0; // DAT_00e2e780 (likely 0 or a constant)
    local_7c = (undefined4)uVar4;
    local_70 = local_7c;
    local_78 = (undefined4)((ulonglong)uVar4 >> 0x20);
    local_6c = local_78;
    local_60 = 0;
    local_5c = 0;
    local_58 = 0;
    local_54 = 0;
    local_30 = 0;
    local_2c = 0;
    local_4c = 0;
    local_64 = 0;
    local_40 = 0.0f - *(float*)(param_1 + 0x90); // DAT_00e44564 is 0.0
    local_3c = 0.0f - *(float*)(param_1 + 0x94);
    local_38 = 0.0f - *(float*)(param_1 + 0x98);
    local_34 = 0.0f - *(float*)(param_1 + 0x9c);
    local_1c = 4; // some flag
    local_18 = param_9;
    local_68 = fVar9;

    if (*(int*)(param_1 + 0x14) == 0) {
        TlsGetValue(/*some index*/);
        iVar7 = allocateMemory(0xa0, 0x34); // FUN_00aa2680
        *(undefined2*)(iVar7 + 4) = 0xa0;
        iVar7 = constructNode(&local_70); // FUN_00552280
        *(int*)(param_1 + 0x14) = iVar7; // mNode

        if (*(uint*)(iVar7 + 0x74) == (*(uint*)(iVar7 + 0x78) & 0x3fffffff)) {
            growArray((int*)(iVar7 + 0x70), 4); // FUN_00aa4190
        }
        *(int*)(*(int*)(iVar7 + 0x70) + *(int*)(iVar7 + 0x74) * 4) = param_1 + 0xbc; // store link
        *(int*)(iVar7 + 0x74) = *(int*)(iVar7 + 0x74) + 1; // increment count
        *(int*)(param_1 + 0xc0) = param_1; // self-pointer
    } else {
        updateNode(); // FUN_005523c0
    }

    // Reset some flags and velocities
    *(char*)(param_1 + 0x31) = 0;
    *(char*)(param_1 + 0x30) = 0;
    *(undefined4*)(param_1 + 0x7c) = 0;
    *(undefined4*)(param_1 + 0x78) = 0;
    *(undefined4*)(param_1 + 0x74) = 0;
    *(undefined4*)(param_1 + 0x70) = 0;
    *(undefined4*)(param_1 + 0x6c) = 0;
    *(undefined4*)(param_1 + 0x68) = 0;
    *(undefined4*)(param_1 + 100) = 0; // +0x64
    *(undefined4*)(param_1 + 0xe8) = 0;

    // Set shape0's user data
    *(undefined4*)(*(int*)(param_1 + 0x18) + 0x2c) = *(undefined4*)(param_1 + 0xd4);
    activateShape(*(undefined4*)(param_1 + 0x18), 1); // FUN_009e9c50

    return;
}