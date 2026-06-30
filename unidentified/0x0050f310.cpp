// FUN_NAME: AnimBlendNode::computeWorldMatrix
// Address: 0x0050f310
// Role: Computes a 4x3 transformation matrix from an input transform and modifies based on animation state flags and scale.

#include <cstring> // for memcpy

// External globals (constants)
extern float DAT_00e2b1a4; // likely 0.0f or identity default
extern float DAT_00e2b05c; // falloff threshold
extern int DAT_01206880;   // some global memory stack pointer

// Forward declarations of called functions (prototypes assumed)
void FUN_004eb6a0(int base, int flags); // sets some state
void FUN_0056b230(float* outMatrix, const float* srcMatrix, const float* transform, int param); // matrix operation
void FUN_00509710(); // debug/log
int FUN_00513f70(int obj); // resource lookup, returns pointer to data

void __thiscall AnimBlendNode::computeWorldMatrix(int thisPtr, int inputTransform)
{
    // Offsets from thisPtr:
    // +0x04 : pointer to some component (Component*)
    // +0x10 : offset for matrix storage base
    // +0x24 : pointer to state object (AnimationState*)
    // +0x2c : some float (stored in local_5c)
    // +0x48 : some float (stored in local_58)
    // +0x70 : stores inputTransform pointer
    // +0x74 : some float used later

    float local_80; // matrix[0]
    float fStack_7c; // matrix[1]
    float fStack_78; // matrix[2]
    float fStack_74; // matrix[3]
    float local_70; // matrix[4]
    float local_6c; // matrix[5]
    float local_68; // matrix[6]
    float local_64; // matrix[7]
    float local_60; // matrix[8]
    float local_5c; // matrix[9]
    float local_58; // matrix[10]
    // implicit float at offset 44 (matrix[11]) is part of the block

    // Local variables used for transformation
    float local_50; // matrix row0 part
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 local_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    float local_30; // matrix row2 part
    float fStack_2c;
    float fStack_28;
    undefined4 uStack_24;

    // Check animation state flags (bits 0x18 set)
    int statePtr = *(int*)(thisPtr + 0x24);
    if ((*(unsigned char*)(statePtr + 0x10c) & 0x18) != 0)
    {
        int* fsBase = *(int**)(*(int*)(__readfsdword(0x2c)) + 8); // thread local storage
        *(int*)(thisPtr + 0x70) = inputTransform;

        int base = *(int*)(thisPtr + 0x10) + 0x80 + fsBase[2];
        int flags = (*(unsigned int*)(statePtr + 0x10c) >> 4) & 0xffffff01;
        FUN_004eb6a0(base, flags);

        int iVar2 = *(int*)(thisPtr + 0x10) + fsBase[2];
        FUN_0056b230(&local_50, iVar2 + 0x10, iVar2 + 0x50, 3);

        // Zero out some fields
        *(int*)(iVar2 + 0x5c) = 0;
        *(int*)(iVar2 + 0x6c) = 0;
        *(int*)(iVar2 + 0x7c) = 0;
    }

    // Initialize local matrix with default value (probably 0 or identity)
    local_80 = DAT_00e2b1a4;
    fStack_7c = DAT_00e2b1a4;
    fStack_78 = DAT_00e2b1a4;
    fStack_74 = DAT_00e2b1a4;
    local_6c = DAT_00e2b1a4;
    local_68 = DAT_00e2b1a4;
    local_64 = DAT_00e2b1a4;
    float fVar4 = DAT_00e2b1a4;
    local_60 = DAT_00e2b1a4;

    // Load some additional values from this
    local_70 = *(float*)(thisPtr + 0x74);
    local_5c = *(float*)(thisPtr + 0x2c);
    local_58 = *(float*)(thisPtr + 0x48);

    FUN_00509710(); // unknown debug/log

    // If there is a referenced object, get its transform data
    int refObj = *(int*)(*(int*)(thisPtr + 4) + 0x20);
    if (refObj != 0)
    {
        if (refObj != 0)
        {
            *(int*)(refObj + 4) += 1; // reference counting?
        }
        int dataPtr = FUN_00513f70(refObj);
        if (dataPtr != 0)
        {
            // Copy 4 floats from offset 0x10 and 3 floats from offset 0x2c
            local_80 = *(float*)(dataPtr + 0x10);
            fStack_7c = *(float*)(dataPtr + 0x14);
            fStack_78 = *(float*)(dataPtr + 0x18);
            fStack_74 = *(float*)(dataPtr + 0x1c);
            local_6c = *(float*)(dataPtr + 0x2c);
            local_68 = *(float*)(dataPtr + 0x30);
            local_64 = *(float*)(dataPtr + 0x34);
        }
    }

    // Check if special flag (0x8000) is set on state
    if ((*(unsigned int*)(statePtr + 0x104) & 0x8000) != 0)
    {
        // Copy input transform's matrix (12 floats from offset 0x40) into local variables
        local_50 = *(float*)(inputTransform + 0x40);
        uStack_4c = *(unsigned int*)(inputTransform + 0x44);
        uStack_48 = *(unsigned int*)(inputTransform + 0x48);
        uStack_44 = *(unsigned int*)(inputTransform + 0x4c);
        local_40 = *(unsigned int*)(inputTransform + 0x50);
        uStack_3c = *(unsigned int*)(inputTransform + 0x54);
        uStack_38 = *(unsigned int*)(inputTransform + 0x58);
        uStack_34 = *(unsigned int*)(inputTransform + 0x5c);
        local_30 = *(float*)(inputTransform + 0x60);
        fStack_2c = *(float*)(inputTransform + 0x64);
        fStack_28 = *(float*)(inputTransform + 0x68);
        uStack_24 = *(unsigned int*)(inputTransform + 0x6c);

        // Compute dot product and possibly scale local_6c
        int basePtr = *(int*)(*(int*)(__readfsdword(0x2c)) + 8); // thread local
        float* pfVar1 = (float*)(basePtr + 0x80 + *(int*)(thisPtr + 0x10));
        float dx = pfVar1[0] - *(float*)(inputTransform + 0x70);
        float dy = pfVar1[1] - *(float*)(inputTransform + 0x74);
        float dz = pfVar1[2] - *(float*)(inputTransform + 0x78);
        float dot = local_30 * dx + fStack_2c * dy + fStack_28 * dz;

        float fVar4 = *(float*)(*(int*)(*(int*)(thisPtr + 4) + 0x10) + 0x24);
        if (fVar4 < dot && DAT_00e2b05c < fVar4)
        {
            local_6c = (dot / fVar4) * local_6c;
        }
    }

    // If a flag (0x80000) is set on some global structure, scale some matrix rows
    int fsOff = __readfsdword(0x2c);
    if ((*(unsigned int*)(*(int*)(fsOff) + 8) + *(int*)(thisPtr + 0x10) & 0x80000) != 0)
    {
        int iVar2 = *(int*)(thisPtr + 4);
        local_80 = *(float*)(iVar2 + 0xa0) * local_80;
        fStack_7c = *(float*)(iVar2 + 0xa4) * fStack_7c;
        fStack_78 = *(float*)(iVar2 + 0xa8) * fStack_78;
    }

    // Push data onto some global memory stack (logging or temporary storage)
    int* stack = (int*)(DAT_01206880 + 0x14);
    **(int**)stack = (int)&PTR_LAB_0112511c; // some label
    *stack += 4;
    *(int*)*stack = thisPtr;
    void* dst = (void*)(*stack + 0x13 & 0xfffffff0);
    *stack = (int)dst;
    memcpy(dst, &local_80, 0x30); // Copy 48 bytes (12 floats)
    *stack += 0x30;

    return;
}