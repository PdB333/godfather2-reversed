// FUNC_NAME: copyDataBlock
// Address: 0x0055f7d0
// Description: Copies specific fields of a data structure (size 0x80) from source to destination.
// The copy skips offsets 0x2-0x3, 0x8-0xF, which might be pointers, handles, or flags.

void __thiscall copyDataBlock(void* thisDest, void* src)
{
    // Copy first two bytes (likely a short or flags)
    *(char*)thisDest = *(char*)src;
    *((char*)thisDest + 1) = *((char*)src + 1);

    // Copy dword at +0x04 (e.g., an ID or type)
    *(int*)((char*)thisDest + 0x04) = *(int*)((char*)src + 0x04);

    // Copy a block of 28 dwords from +0x10 to +0x7C (0x10, 0x14, ..., 0x7C)
    // These are likely the main data payload (e.g., matrix or transform components)
    *(int*)((char*)thisDest + 0x10) = *(int*)((char*)src + 0x10);
    *(int*)((char*)thisDest + 0x14) = *(int*)((char*)src + 0x14);
    *(int*)((char*)thisDest + 0x18) = *(int*)((char*)src + 0x18);
    *(int*)((char*)thisDest + 0x1C) = *(int*)((char*)src + 0x1C);
    *(int*)((char*)thisDest + 0x20) = *(int*)((char*)src + 0x20);
    *(int*)((char*)thisDest + 0x24) = *(int*)((char*)src + 0x24);
    *(int*)((char*)thisDest + 0x28) = *(int*)((char*)src + 0x28);
    *(int*)((char*)thisDest + 0x2C) = *(int*)((char*)src + 0x2C);
    *(int*)((char*)thisDest + 0x30) = *(int*)((char*)src + 0x30);
    *(int*)((char*)thisDest + 0x34) = *(int*)((char*)src + 0x34);
    *(int*)((char*)thisDest + 0x38) = *(int*)((char*)src + 0x38);
    *(int*)((char*)thisDest + 0x3C) = *(int*)((char*)src + 0x3C);
    *(int*)((char*)thisDest + 0x40) = *(int*)((char*)src + 0x40);
    *(int*)((char*)thisDest + 0x44) = *(int*)((char*)src + 0x44);
    *(int*)((char*)thisDest + 0x48) = *(int*)((char*)src + 0x48);
    *(int*)((char*)thisDest + 0x4C) = *(int*)((char*)src + 0x4C);
    *(int*)((char*)thisDest + 0x50) = *(int*)((char*)src + 0x50);
    *(int*)((char*)thisDest + 0x54) = *(int*)((char*)src + 0x54);
    *(int*)((char*)thisDest + 0x58) = *(int*)((char*)src + 0x58);
    *(int*)((char*)thisDest + 0x5C) = *(int*)((char*)src + 0x5C);
    *(int*)((char*)thisDest + 0x60) = *(int*)((char*)src + 0x60);
    *(int*)((char*)thisDest + 0x64) = *(int*)((char*)src + 0x64);
    *(int*)((char*)thisDest + 0x68) = *(int*)((char*)src + 0x68);
    *(int*)((char*)thisDest + 0x6C) = *(int*)((char*)src + 0x6C);
    *(int*)((char*)thisDest + 0x70) = *(int*)((char*)src + 0x70);
    *(int*)((char*)thisDest + 0x74) = *(int*)((char*)src + 0x74);
    *(int*)((char*)thisDest + 0x78) = *(int*)((char*)src + 0x78);
    *(int*)((char*)thisDest + 0x7C) = *(int*)((char*)src + 0x7C);
}