// FUNC_NAME: NetworkStreamProcessor::processPacket
void __thiscall NetworkStreamProcessor::processPacket(int thisPtr)
{
    int iVar1;
    int iVar2;
    int iVar3;

    // Check if vtable pointer (at +0x50) and packet pointer (at +0x9c) are valid,
    // and that the packet pointer is not a sentinel value 0x48 (possibly "empty" state).
    if ((*(int *)(thisPtr + 0x50) != 0) &&
        (*(int *)(thisPtr + 0x9c) != 0) &&
        (*(int *)(thisPtr + 0x9c) != 0x48))
    {
        // Get global time or timestamp from a helper function.
        iVar1 = getGameTime(); // FUN_00471610

        // Retrieve the packet offset/pointer from the object.
        iVar2 = *(int *)(thisPtr + 0x9c);
        if (iVar2 == 0)
        {
            iVar3 = 0;
            iVar2 = 0;
        }
        else
        {
            // Subtract the header size (0x48 bytes) to get the payload start.
            iVar3 = iVar2 - 0x48;
            iVar2 = iVar2 - 0x48;
        }

        // Call a vtable function at offset 0x1E8 on the object pointed to by +0x50.
        // Arguments: payload pointer (iVar2), flag (2),
        //            payload size in dwords (dereference at iVar3+0x6DC >> 2),
        //            timestamp from helper (iVar1+0x30), and three zeros.
        (**(code **)(**(int **)(thisPtr + 0x50) + 0x1E8))
        (iVar2, 2, *(uint *)(iVar3 + 0x6DC) >> 2, iVar1 + 0x30, 0, 0, 0);
    }
    return;
}