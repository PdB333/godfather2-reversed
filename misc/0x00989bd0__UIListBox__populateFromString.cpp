// FUNC_NAME: UIListBox::populateFromString
void __thiscall UIListBox::populateFromString(int this, char *inputString)
{
    char *pcVar1;
    undefined4 uVar2;
    int iVar3;
    undefined4 *puVar4;
    int tokenLength;          // iStack_c
    float scaleFactor;        // fStack_8
    undefined4 local_4;

    // Initialization sequence
    initDefaults();
    allocateMemory(0x800);                                                  // allocate internal buffer

    // Retrieve global state
    local_4 = DAT_0122349c;                                                 // some global pointer

    // Virtual call to get a value (likely text length or similar)
    uVar2 = (*(code **)(**(undefined4 **)(this + 0x74)))();                 // vtable +0x74

    uVar2 = convertEncoding(uVar2);                                         // text conversion
    setWindowText(uVar2);                                                   // set window title

    // Compute scaling factor for line spacing
    scaleFactor = (float)DAT_0120588c * _DAT_00d916a0 * *(float *)(this + 0xf8); // global scale * custom spacing

    // Parse input string into items (newline-separated?)
    while (pcVar1 = inputString, pcVar1 != (char *)0x0 && *pcVar1 != '\0')
    {
        tokenLength = 0;
        inputString = (char *)0x0;                                          // reset for next iteration

        // Parse one token: returns token length and sets inputString to next token pointer
        parseToken(pcVar1, *(int *)(this + 0xfc), &tokenLength,
                   scaleFactor, &inputString, 0, 0, 1);

        // Check if item array needs expansion
        iVar3 = *(int *)(this + 0x6c);                                      // capacity (+0x6c)
        if (*(int *)(this + 0x68) == iVar3)                                 // count == capacity (+0x68)
        {
            if (iVar3 == 0)
            {
                iVar3 = 1;
            }
            else
            {
                iVar3 = iVar3 * 2;                                          // double capacity
            }
            reallocateItems(iVar3);                                         // realloc (+0x6c updated internally)
        }

        // Pointer to new slot (each slot is 16 bytes = 4 ints)
        puVar4 = (undefined4 *)(*(int *)(this + 0x68) * 0x10 + *(int *)(this + 100)); // index * 16 + array base (+0x64)

        if (puVar4 != (undefined4 *)0x0)
        {
            // Clear slot
            *puVar4 = 0;
            puVar4[1] = 0;
            puVar4[2] = 0;
            puVar4[3] = 0;
        }

        // Increment item count
        *(int *)(this + 0x68) = *(int *)(this + 0x68) + 1;

        if (tokenLength != 0)
        {
            // Cleanup: release the parsed token (free its memory)
            releaseToken(pcVar1, inputString + (-1 - (int)pcVar1));
        }
    }

    // Update total item count (possibly for scroll range)
    *(int *)(this + 0x60) = *(int *)(this + 0x68);

    inputString = pcVar1;

    // Notify scrollbar system
    debugPrint("InitScrollBar", 0, &DAT_00d9158c, 0);

    // Reset selection index
    *(int *)(this + 0x5c) = 0;

    // Set scrollbar range: min(count, maxVisible)
    iVar3 = *(int *)(this + 0x68);
    if (*(int *)(this + 0x70) <= *(int *)(this + 0x68))                     // maxVisible (+0x70)
    {
        iVar3 = *(int *)(this + 0x70);
    }
    updateScrollBar(iVar3);

    return;
}