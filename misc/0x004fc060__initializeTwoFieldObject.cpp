// FUNC_NAME: initializeTwoFieldObject
void __thiscall initializeTwoFieldObject(void) {
    byte buffer[12]; // Temporary buffer for generating values
    int *pResult;    // Pointer to generated value pair

    // Zero out first two dwords of this object (+0x00 and +0x04)
    *(int *)this = 0;
    *((int *)this + 1) = 0;

    // Fill buffer and obtain a pair of ints from helper function
    pResult = (int *)FUN_004fc430(buffer);
    
    // Copy the generated values into the object's first two fields
    *(int *)this = pResult[0];       // +0x00: value1
    *((int *)this + 1) = pResult[1]; // +0x04: value2
    return;
}