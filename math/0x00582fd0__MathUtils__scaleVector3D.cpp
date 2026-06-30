// FUNC_NAME: MathUtils::scaleVector3D
void __fastcall scaleVector3D(void* thisPtr, int param2, int param3)
{
    float* pfVar1;  // pointer to first vector's scale factors
    float* pfVar2;  // pointer to output vector
    float* pfVar3;  // pointer to input vector
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;

    fVar6 = DAT_00e2b1a4;  // global scale factor (e.g., world unit conversion)
    pfVar1 = *(float**)((int)thisPtr + 8);  // this +0x8: pointer to scale factors (x,y,z)
    pfVar2 = *(float**)(param2 + 8);        // param2 +0x8: pointer to output vector
    pfVar3 = *(float**)(param3 + 8);        // param3 +0x8: pointer to input vector

    fVar7 = DAT_00e2b1a4 / pfVar1[1];  // scale Y factor
    fVar8 = DAT_00e2b1a4 / pfVar1[2];  // scale Z factor

    fVar4 = pfVar3[1];  // input Y
    fVar5 = pfVar3[2];  // input Z
    fVar9 = pfVar3[3] * DAT_00e2b1a4;  // input W * global scale

    *pfVar2 = *pfVar3 * (DAT_00e2b1a4 / *pfVar1);  // output X = input X * (global / scaleX)
    pfVar2[1] = fVar4 * fVar7;  // output Y = input Y * (global / scaleY)
    pfVar2[2] = fVar5 * fVar8;  // output Z = input Z * (global / scaleZ)
    pfVar2[3] = fVar9;  // output W = input W * global
    pfVar2[3] = fVar6;  // overwrite W with global scale (likely a bug or intentional override)

    return;
}