// FUNC_NAME: lookupValueFromTable
// Function at 0x0066cf40: Looks up a value from a static table of size 3.
// The table is an array of {key, value} pairs, each 8 bytes.
// Default return is 1 if key not found.
// Called by other functions (0x006626f0, 0x0066cb20) likely as part of enum/conversion logic.
int __fastcall lookupValueFromTable(int key)
{
    // Static table at address 0x00e2747c (base) and 0x00e27480 (base+4) representing {key, value} pairs.
    // Values are unknown from decompiler alone, but structure is:
    // [0x00e2747c + i*8] = key_i
    // [0x00e27480 + i*8] = value_i
    for (int i = 0; i < 3; i++)
    {
        if (key == *(int*)(0x00e2747c + i * 8))
        {
            return *(int*)(0x00e27480 + i * 8);
        }
    }
    return 1;
}