// FUNC_NAME: cleanUpSlotArray
void __fastcall cleanUpSlotArray(int thisPtr)
{
    // Release each of the 8 slot sub-objects at offsets +0xa4 to +0xdc (each 8 bytes apart)
    // These likely represent an array of 8 small objects or handles
    sub_408680(thisPtr + 0xa4);
    sub_408680(thisPtr + 0xac);
    sub_408680(thisPtr + 0xb4);
    sub_408680(thisPtr + 0xbc);
    sub_408680(thisPtr + 0xc4);
    sub_408680(thisPtr + 0xcc);
    sub_408680(thisPtr + 0xd4);
    sub_408680(thisPtr + 0xdc);

    // Also release a global singleton/resource at address 0x012069c4
    sub_408680(&g_globalSlotData);
}