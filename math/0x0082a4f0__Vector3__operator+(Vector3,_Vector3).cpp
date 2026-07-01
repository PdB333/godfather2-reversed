// FUNC_NAME: Vector3::operator+(Vector3, Vector3)
undefined4 FUN_0082a4f0(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
    // This appears to be a vector addition function (v3 = v1 + v2)
    // param_1: destination Vector3 (this pointer)
    // param_2: first Vector3 operand
    // param_3: second Vector3 operand (passed to helper)
    // param_4: potentially a flag or scale factor
    
    undefined4 tempResult1;
    undefined1 tempBuffer1[176]; // 176 bytes = enough for Vector3 + padding
    undefined1 tempBuffer2[188]; // 188 bytes = enough for Vector3 + padding
    
    // First helper: likely copies/scales first operand based on param_4 (scale?)
    tempResult1 = FUN_0081fc80(tempBuffer1, param_4, param_3);
    
    // Second helper: likely adds param_2 to the scaled first operand
    tempResult1 = FUN_0081fe40(tempBuffer2, param_2, tempResult1);
    
    // Third helper: likely stores result to destination (param_1)
    FUN_0081fb90(param_1, param_3, tempResult1);
    
    return param_1;
}