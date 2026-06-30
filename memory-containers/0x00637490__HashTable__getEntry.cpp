// FUNC_NAME: HashTable::getEntry
int __fastcall HashTable::getEntry(void* thisPtr, int* params)
{
    int mask = (1 << (*(unsigned char*)((int)thisPtr + 7) & 0x1f)) - 1;
    int base = *(int*)((int)thisPtr + 0x10); // +0x10: pointer to array of entries (each 0x14 bytes)
    int op = params[0];
    int value = params[1];
    int index;

    switch (op)
    {
    case 1: // direct bitwise AND
        index = mask & value;
        break;
    case 2: // modulo (with mask|1 to avoid zero)
        index = value % (mask | 1);
        break;
    case 3: // float addition then modulo
    {
        float f = (float)value + DAT_00e2b1a4; // global float offset
        index = (int)f % (mask | 1);
        break;
    }
    case 4: // bitwise AND with value from another struct
        index = mask & *(int*)(value + 8);
        break;
    default: // default: just modulo with float cast
    {
        float f = (float)value;
        index = (int)f % (mask | 1);
        break;
    }
    }

    return base + index * 0x14; // return pointer to the entry
}