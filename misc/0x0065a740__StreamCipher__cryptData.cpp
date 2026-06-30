// FUNC_NAME: StreamCipher::cryptData
void __thiscall StreamCipher::cryptData(int thisPtr, byte *input, byte *output, int length)
{
    byte bVar1;               // XOR result byte
    int iVar2;                // loop counter
    undefined4 *puVar3;       // source pointer for state copy
    undefined4 *puVar4;       // destination pointer for state copy
    undefined4 localStateCopy[1064]; // large local copy of state +0x6c (0x204 bytes used)
    // Stack canary placeholder (injected by __alloca_probe)

    // Copy state (0x81 dwords = 0x204 bytes) from this+0x6c to local array
    puVar3 = (undefined4 *)(thisPtr + 0x6c);      // +0x6c: m_state (size 0x204)
    puVar4 = localStateCopy;
    for (iVar2 = 0x81; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
    }

    if (length != 0) {
        do {
            length = length - 1;
            // When keystream buffer index reaches 16 (0x10), generate new keystream
            if (*(int *)(thisPtr + 0x270) == 0x10) { // +0x270: m_keystreamIndex
                // Update keystream buffer using state copy
                // FUN_00661210(this+0x5c, this+0x5c, localStateCopy)
                // Likely generates next 16 bytes of keystream from the state
                FUN_00661210(thisPtr + 0x5c, thisPtr + 0x5c, localStateCopy); // +0x5c: m_keystreamBuffer (16 bytes)
                *(int *)(thisPtr + 0x270) = 0; // reset index
            }
            bVar1 = *(byte *)(thisPtr + 0x5c + *(int *)(thisPtr + 0x270)) ^ *input; // XOR input with keystream
            input = input + 1;
            *output = bVar1;
            // Store XOR result back into keystream buffer (feedback)
            *(byte *)(thisPtr + 0x5c + *(int *)(thisPtr + 0x270)) = bVar1;
            *(int *)(thisPtr + 0x270) = *(int *)(thisPtr + 0x270) + 1; // advance index
            output = output + 1;
        } while (length != 0);
    }
    return;
}