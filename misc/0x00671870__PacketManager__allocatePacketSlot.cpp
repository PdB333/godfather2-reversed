// FUNC_NAME: PacketManager::allocatePacketSlot

uint __thiscall PacketManager::allocatePacketSlot(int thisPtr, ushort slotId, int *outErrorCode)
{
    int iVar1;
    ulonglong uVar2;
    ushort currentCount;
    uint uVar4;
    ulonglong *edi;
    int entryOffset;

    currentCount = *(ushort *)(thisPtr + 0x1a);
    // Clear the error flag in the caller's context (in_EAX is a register variable, represented as *outErrorCode? Actually in_EAX appears to be a register used as flag, but we emulate as writing to a local)
    // The decompiler shows *in_EAX = 0; this is likely clearing a register that is used later.
    // We'll ignore this for C++ reconstruction as it's a register manipulation.
    // Actually in_EAX is likely a global or register variable. We'll skip it.
    // In the original, it writes to *in_EAX. That might be a global flag. We'll not include.

    if (currentCount > 0x7f) // Maximum 128 slots
    {
        *outErrorCode = 0x4e22; // Error: too many entries
        return 0xffff;
    }

    if (slotId < *(ushort *)(thisPtr + 0x10)) // Check if slotId is within allowed range
    {
        do
        {
            currentCount = *(ushort *)(thisPtr + 0x18);
            uVar4 = (uint)currentCount;
            *(ushort *)(thisPtr + 0x18) = currentCount + 1;
            if (currentCount == 0xffff)
            {
                // Wrap around - reset counter to 1 (skip index 0?)
                // This is a bug? should be 0? But code sets *in_EAX = 1 first, then sets to 1.
                *(undefined2 *)(thisPtr + 0x18) = 1;
                uVar4 = 0; // Force index 0? Actually after wrap, uVar4 becomes 0, so next iteration checks slot 0.
            }
        } while (*(short *)(thisPtr + 0x1e + (uVar4 & 0x8000007f) * 0x3c) != -1);

        // uVar4 now holds the index of a free slot (mod 128)
        uVar2 = *edi; // edi is a saved register from caller, likely holds packet data pointer
        entryOffset = thisPtr + (uVar4 & 0x8000007f) * 0x3c; // Each slot is 0x3c bytes
        *(ushort *)(entryOffset + 0x1c) = slotId; // +0x1c: slot ID
        *(ulonglong *)(entryOffset + 0x20) = uVar2; // +0x20: packet data pointer (8 bytes)
        uVar2 = edi[1]; // Second qword from packet data
        *(int *)(entryOffset + 0x30) = 0; // +0x30: clear two ints
        *(int *)(entryOffset + 0x34) = 0;
        *(short *)(entryOffset + 0x1e) = (short)uVar4; // +0x1e: store index as short
        *(ulonglong *)(entryOffset + 0x28) = uVar2; // +0x28: another pointer or data
        *(short *)(thisPtr + 0x1a) = *(short *)(thisPtr + 0x1a) + 1; // Increment active count
        *outErrorCode = 0;
        return uVar4 & 0x8000007f; // Return the slot index (mod 128)
    }

    *outErrorCode = 20000; // Error: no free slot
    return 0xffff;
}