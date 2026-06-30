// FUNC_NAME: GlobalInitializeIndexedArrays
void __fastcall GlobalInitializeIndexedArrays(int index1, int index2) // index1 in ECX, index2 in EAX (non-standard __fastcall)
{
    // Globals from static data segment
    extern int g_value1;
    extern int g_value2;
    extern void* g_arrayPtr1;   // points to structure of size 0x5c
    extern void* g_arrayPtr2;   // points to structure of size 0x14
    extern void* g_arrayPtr3;   // points to structure of size 0x2c
    extern void* g_arrayPtr4;   // points to structure of size 0x30
    extern int g_flag;

    // Read 4-byte values from arrays indexed by the parameters
    g_value1 = *(int*)(&g_someIntArray1 + index1 * 4);      // DAT_0121b658
    g_value2 = *(int*)(&g_someIntArray2 + index2 * 4);      // DAT_0121b6b8

    // For large index2 (>15), set additional pointers to extended arrays
    if (index2 > 15)
    {
        g_arrayPtr1 = (void*)(&g_largeStructArray1 + index2 * 0x5c);   // DAT_01219e64
        g_arrayPtr2 = (void*)(&g_mediumStructArray + index2 * 0x14);   // DAT_0121a8a4
    }

    g_arrayPtr3 = (void*)(&g_smallStructArray + index2 * 0x2c);        // DAT_0121ab24
    g_arrayPtr4 = (void*)(&g_structArrayByIndex1 + index1 * 0x30);     // DAT_0121b1b8

    g_flag = 0;
}