// FUNC_NAME: flattenNodeList
void flattenNodeList(int **ppOutput)
{
    int currentNodeAddr;

    FUN_00498180();
    if (*ppOutput == 0)
    {
        ppOutput = nullptr;
        currentNodeAddr = 0;
    }
    else
    {
        // Dereference through a pointer at offset 0x30 of the structure pointed to by *ppOutput
        ppOutput = (int *)*( *(int **)( (int)*ppOutput + 0x30 ) );
        currentNodeAddr = (int)ppOutput;
    }

    for (; currentNodeAddr != 0; currentNodeAddr = *( *(int **)(currentNodeAddr + 0x30) ) )
    {
        FUN_00498740(&ppOutput, currentNodeAddr);
        // Copy 5 8-byte chunks (40 bytes) from the node to the current output position
        *(unsigned long long *)((int)ppOutput + 8) = *(unsigned long long *)(currentNodeAddr + 8);
        *(unsigned long long *)((int)ppOutput + 0x10) = *(unsigned long long *)(currentNodeAddr + 0x10);
        *(unsigned long long *)((int)ppOutput + 0x18) = *(unsigned long long *)(currentNodeAddr + 0x18);
        *(unsigned long long *)((int)ppOutput + 0x20) = *(unsigned long long *)(currentNodeAddr + 0x20);
        *(unsigned long long *)((int)ppOutput + 0x28) = *(unsigned long long *)(currentNodeAddr + 0x28);
    }
}