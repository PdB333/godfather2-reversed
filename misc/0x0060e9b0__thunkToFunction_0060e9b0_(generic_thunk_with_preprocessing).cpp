// FUNC_NAME: thunkToFunction_0060e9b0 (generic thunk with preprocessing) 
void thunkToFunction_0060e9b0(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5) {
    uint32 var_param4 = param4;
    char result = prepareData(&param1, &param2, &param3, param4, param5); // FUN_006073e0
    
    if (result != 0) {
        // If param4 low byte is zero and global divisor > 1, normalize first two array elements
        if (((char)var_param4) == 0 && (int)pDivisor > 1) {
            tempArray[0] = tempArray[0] / pDivisor * 0x0;
            tempArray[1] = tempArray[1] / pDivisor * 0x0;
        }
        
        // Copy 14 elements from local array to global buffer
        for (int i = 0; i < 14; i++) {
            globalBuffer[i] = tempArray[i];
        }
        
        // Forward to next function
        forwardFunction(param3, var_param4, param5); // FUN_00607730
    }
}