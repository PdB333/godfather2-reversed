// FUNC_NAME: ConnectionValidator::checkPairState
uint __fastcall ConnectionValidator::checkPairState(int this) {
    // this: pointer to connection/player object (offsets up to 0x109c)
    int globalPtr = DAT_0112af68; // global pointer to some manager/state (offset 0x1bc,0x1c0)
    uint rawVal = **(uint **)(DAT_012233a0 + 4); // double dereference from global pointer+4
    
    if (rawVal == 0 || rawVal == 0x1f30)
        goto exit;
    
    uint expectedDiff = rawVal - 0x1f30; // computed offset
    uint fieldValue;
    if (*(int *)(this + 0x109c) == 0)
        fieldValue = 0;
    else
        fieldValue = *(int *)(this + 0x109c) - 0x48;
    
    if (fieldValue != expectedDiff)
        goto exit;
    
    uint callResult = FUN_008f92b0(); // some external check
    if ((callResult & 0xFF) != 0 || globalPtr == -0x19c)
        goto exit;
    
    // Attempt to match a pair of values in either order
    uint temp[3];
    uint localVal;
    uint checkA, checkB;
    
    temp[0] = 1;
    FUN_005fd860(temp, temp + 2, &localVal); // first encoding step
    temp[1] = 2;
    FUN_005fd860(temp + 1, (uint *)temp + 3, temp); // second step, weird casting
    
    uint cmp1 = *(uint *)(globalPtr + 0x1bc);
    uint cmp2 = *(uint *)(globalPtr + 0x1c0);
    
    // Check if (localVal, temp[0]) equals either (cmp2, cmp1) or (cmp1, cmp2)
    if ((localVal != cmp2 || temp[0] != cmp1) &&
        (localVal != cmp1 || temp[0] != cmp2)) {
        // Retry with different indices
        temp[1] = 2;
        FUN_005fd860(temp + 1, temp + 2, &localVal);
        temp[2] = 3;
        FUN_005fd860(temp + 2, (uint *)temp + 3, temp);
        
        cmp1 = *(uint *)(globalPtr + 0x1bc);
        cmp2 = *(uint *)(globalPtr + 0x1c0);
        
        if ((localVal != cmp2 || temp[0] != cmp1) &&
            (localVal != cmp1 || temp[0] != cmp2))
            goto exit; // no match
    }
    
    // Match found – return low byte = 1, rest from shifted value
    return (callResult & 0xFFFFFF00) | 1;
    
exit:
    return callResult & 0xFFFFFF00; // clear low byte
}