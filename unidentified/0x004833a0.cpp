// FUN_004833a0: storeTripleValue
void storeTripleValue(int keyId, int secondValue, int firstValue, int thirdValue)
{
    // +0x01223d14: global initialization flag (bit 0)
    // +0x012239bc: counter or state (initialized to 0)
    // +0x012239c0, +0x012239c4: additional global state (initialized to 0)
    // atexit handler at 0x00d50740: cleanup function
    if ((*(unsigned int*)0x01223d14 & 1) == 0)
    {
        *(unsigned int*)0x01223d14 |= 1;
        *(int*)0x012239bc = 0;
        *(int*)0x012239c0 = 0;
        *(int*)0x012239c4 = 0;
        _atexit((void (*)())(void*)0x00d50740);
    }

    // FUN_00483720: returns a pointer to a buffer (likely allocated or looked up by keyId)
    int* buffer = (int*)FUN_00483720(&keyId);
    if (buffer != (int*)0x0)
    {
        buffer[0] = firstValue;   // param3 stored at offset 0
        buffer[1] = secondValue;  // param2 stored at offset 4
        buffer[2] = thirdValue;   // param4 stored at offset 8
    }
}