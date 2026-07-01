// FUNC_NAME: FUN_008bd920
// The function checks if a parameter's field at offset +4 equals 5, then calls two subroutines.
// It returns 1 if condition met, otherwise 0.

uint8 FUN_008bd920(int* param1) {
    uint8 retVal = 0;
    
    if ((param1 != NULL) && (*(int*)((uint8*)param1 + 4) == 5)) {
        // Call subroutines (likely state transition or initialization)
        FUN_008c80d0(0);  // First action with arg 0
        FUN_008c8a20(1, 0); // Second action with args 1 and 0
        retVal = 1;
    }
    
    return retVal;
}