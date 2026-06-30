// FUNC_NAME: Matrix44::multiply
void __fastcall Matrix44::multiply(float *param_1, float *param_2, float *this) // Actually this in ECX, param_1 in EDX, param_2? The calling convention is fastcall with param_1 in ECX, param_2 in EDX, but Ghidra shows param_1 and param_2 as float* and no this. However, the code uses unaff_ESI which is likely the 'this' pointer. So we'll assume __thiscall: void __thiscall Matrix44::multiply(float *other, float *result) with this in ECX.
{
    // Extract all 16 floats from the 'this' matrix into local vars for speed
    float a00 = m[0][0]; // fVar1
    float a01 = m[0][1]; // fVar2
    float a02 = m[0][2]; // fVar3
    float a03 = m[0][3]; // fVar4
    float a10 = m[1][0]; // fVar5
    float a11 = m[1][1]; // fVar6
    float a12 = m[1][2]; // fVar7
    float a13 = m[1][3]; // fVar8
    float a20 = m[2][0]; // fVar9
    float a21 = m[2][1]; // fVar10
    float a22 = m[2][2]; // fVar11
    float a23 = m[2][3]; // fVar12
    float a30 = m[3][0]; // fVar13
    float a31 = m[3][1]; // fVar14
    float a32 = m[3][2]; // fVar15
    float a33 = m[3][3]; // fVar16
    
    int rowCount = 4;
    do
    {
        float b0 = param_1[0]; // fVar17
        float b1 = param_1[1]; // fVar18
        float b2 = param_1[2]; // fVar19
        float b3 = param_1[3]; // fVar20
        
        rowCount--;
        // Compute result row = this * input column (assuming row-major multiplication)
        param_2[0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
        param_2[1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
        param_2[2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
        param_2[3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
        
        param_1 += 4;
        param_2 += 4;
    } while (rowCount > 0);
}