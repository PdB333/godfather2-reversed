// FUN_00500490: ObjectBase::markMemoryPage
int __fastcall ObjectBase::markMemoryPage(int thisPtr)
{
    byte* flags = (byte*)(thisPtr + 0x2c);   // +0x2c: bitfield flags (bit1 = release flag)
    int* pointer = (int*)(thisPtr + 0x30);   // +0x30: pointer to some resource or object
    char* flagChar = (char*)(thisPtr + 0x35); // +0x35: single‑byte state flag

    if ((*flags & 2) != 0 && *pointer != 0 && *flagChar == '\0')
    {
        // Call cleanup function – likely a destructor or resource release
        FUN_004b1ca0();
    }

    int offset = *(int*)(thisPtr + 0x10); // +0x10: offset relative to module image base

    // Retrieve the executable's image base address from the PEB (FS:[0x2c])
    // FS segment → Thread Information Block → offset 0x2c → PEB → offset 8 → ImageBaseAddress
    int* peb = *(int**)(__readfsdword(0x2c));
    int imageBase = *(int*)((uint8*)peb + 8);

    int* targetAddr = (int*)(offset + imageBase);
    *targetAddr |= 1;                     // Mark the memory location (set bit 0)
    return (int)targetAddr;               // Return the target address
}