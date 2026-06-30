// FUNC_NAME: Matrix4x4::accumulateTransformation
void __fastcall Matrix4x4::accumulateTransformation(float *thisOut, float *transformIn)
{
    float scale = DAT_00e2b1a4; // global scale factor (likely time delta or animation blend weight)
    float sx = scale * transformIn[1];
    float sy = scale * transformIn[2];
    float sz = scale * transformIn[3];

    // Accumulate rotation/scale columns (first 3 columns are 3x3 rotation+scale)
    thisOut[0] = scale * transformIn[0] + thisOut[0];
    thisOut[1] = sx + thisOut[1];
    thisOut[2] = sy + thisOut[2];
    thisOut[3] = sz + thisOut[3];

    // Accumulate translation (columns 4 and 5 are translation, column 8 is homogeneous w)
    thisOut[4] = transformIn[4] + thisOut[4];
    thisOut[5] = transformIn[5] + thisOut[5];
    thisOut[8] = thisOut[8] + scale; // accumulate homogeneous component (w)
}