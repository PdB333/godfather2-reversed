// FUNC_NAME: global_registerActionPacket
void global_dispatchActionPacket(uint32_t* pData1, uint32_t* pData2, uint32_t* pData3, uint32_t* pData4, uint32_t param5)
{
    uint32_t data[4];
    data[0] = *pData1;
    data[1] = *pData2;
    data[2] = *pData3;
    data[3] = *pData4;

    // Global pool pointer at 0x01206880
    // +0x14 is offset to a linked list or allocation table
    int* piVar1 = (int*)(*(int*)0x01206880 + 0x14);

    // Write function pointer into the next slot in the table
    // PTR_FUN_01123c88 is likely a handler callback
    *(void**)*piVar1 = (void*)0x01123c88;
    *piVar1 += 4; // Advance to next slot

    // Build a 64-bit value: (type=4) concatenated with pointer to data array
    // Then call the packet processing function with 1 (count?) and param5
    processActionPacket(CONCAT44(4, &data), 1, param5);
}