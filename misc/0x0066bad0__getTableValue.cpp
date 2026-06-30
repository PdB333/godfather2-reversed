// FUNC_NAME: getTableValue
int __fastcall getTableValue(int unused, int key)
{
    // Static table of sorted key-value pairs, likely defined elsewhere (e.g., &DAT_00e274c0, &DAT_00e274c4)
    int i = 0;
    while (true)
    {
        int k = s_keyTable[i]; // DAT_00e274c0[i*2]
        if (k == key)
            return s_valueTable[i]; // DAT_00e274c4[i*2]
        if (key < k)
            break;
        i++;
        if (i > 31)
            return 0x1; // Default fallback
    }
    if (i == 0)
        return 0x1c; // Before first key
    return s_pointerTable[i]; // PTR_FUN_00e274bc
}