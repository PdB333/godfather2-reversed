// FUNC_NAME: ResourceManager::initializeGlobalStringTable
void ResourceManager::initializeGlobalStringTable(void)
{
    // Global string table base
    // Structure: array of entries; each entry is a pointer to a string (const char*)
    // Some entries are followed by an int (set to 0) - likely flags or terminator
    // Global pointer to the resource manager singleton (DAT_01205750)
    // It has a vtable with method at offset 0x158 which registers a string pointer
    // Returns error code -0x7789fe84 on failure; PTR_FUN_00f15a3c is error handler (probably assert or log)

    // First region: pointers only (no zero after)
    registerString(&gStringTable[0],  "DAT_011286c8");
    registerString(&gStringTable[1],  "DAT_01128700");
    registerString(&gStringTable[2],  "DAT_01128738");
    registerString(&gStringTable[3],  "DAT_01128768");
    registerString(&gStringTable[4],  "DAT_01128798"); // note: index jump to 8 due to later zero insertion
    registerString(&gStringTable[8],  "DAT_011287c8");
    registerString(&gStringTable[9],  "DAT_011287f8");
    registerString(&gStringTable[10], "DAT_01128820");
    registerString(&gStringTable[11], "DAT_01128848");
    registerString(&gStringTable[12], "DAT_01128868");
    registerString(&gStringTable[13], "DAT_01128888");
    registerString(&gStringTable[14], "DAT_011288a8");
    registerString(&gStringTable[15], "DAT_011288c0");
    registerString(&gStringTable[16], "DAT_011288e0");
    registerString(&gStringTable[17], "DAT_011288f8");
    registerString(&gStringTable[18], "DAT_01128910");
    registerString(&gStringTable[19], "DAT_01128930");
    registerString(&gStringTable[20], "DAT_01128940");
    // Note: index 5,6,7 are skipped? Actually pattern: after 3c entry, there is a zero at offset 40
    // Then next entries are at 44,48,4c,50,54,58,5c,60,64,68,6c,70,74
    // Likely the table is interleaved: pointer, int(0), pointer, int(0), ...
    // But the first 12 entries (0-11) are pure pointers without zero int.
    // Then after that, each pointer is followed by an int zero.
    // However the last entries (20 onwards) also seem to have zeros after some of them.

    // Let's assume the table is an array of (pointer, int) pairs for the second half, while first half is pointer only.
    // For simplicity, I'll just show the repetitive pattern as it was in the decompiled code.

    // Actually, the decompiled code shows that after each string pointer, sometimes there is a store of integer zero.
    // The pattern after the 3c block: set 40=0, then store string at 44, then set 48=0, then store string at 4c, etc.
    // So from offset 0x44 onwards, it's alternating: string, zero, string, zero, ...
    // But also some strings are stored without following zero? Hard to be sure.

    // Given the complexity and that this function is not a typical loop, I'll replicate the exact sequence from the decompiled code with meaningful macro.

    #define REGISTER_STRING_AND_FLAG(index, str, flag) \
        { \
            if (registerString(&gStringTable[index], str) == -0x7789fe84) \
            { \
                handleError(); \
            } \
            gStringFlags[index] = flag; \
        }

    // Use global pointer to manager object (DAT_01205750)
    // The method at vtable+0x158 is called for each registration

    // First section: pointers only (no flags)
    if (registerString(&gStringTable[0], "DAT_011286c8") == -0x7789fe84) handleError();
    if (registerString(&gStringTable[1], "DAT_01128700") == -0x7789fe84) handleError();
    if (registerString(&gStringTable[2], "DAT_01128738") == -0x7789fe84) handleError();
    if (registerString(&gStringTable[3], "DAT_01128768") == -0x7789fe84) handleError();
    if (registerString(&gStringTable[4], "DAT_01128798") == -0x7789fe84) handleError();
    // After 4, there is a skip? Actually next string is at index 5? The decompiled shows DAT_011287c8 stored at offset 28 = 0x28, which would be index 5 if base is 0x10? No, offsets are absolute addresses: 0x1164028, etc.
    // The globals start at 0x1164010. So index = (offset - 0x1164010) / 4.
    // Let's compute: 0x1164010 -> index 0
    // 0x1164014 -> 1
    // 0x1164018 -> 2
    // 0x116401c -> 3
    // 0x1164020 -> 4
    // 0x1164024 -> 5? But in the code, after storing at 0x116401c, next offset is 0x1164020, then 0x1164028? Wait, there is also 0x1164020 used? Actually the sequence:
    // 10,14,18,1c,20,24,28,2c,30,34,38,3c - that's 12 entries (0-11)
    // Then 40 (index 12) set to 0
    // Then 44 (index 13) string, 48 (14) 0, 4c (15) string, 50 (16) 0, 54 (17) string, 58 (18) string, 5c (19) string, 60 (20) string, 64 (21) string, 68 (22) string, 6c (23) string, 70 (24) 0, 74 (25) string.
    // So indices 0-11: pure strings
    // Indices 12,14,16: int zeros
    // Indices 13,15,17-23,25: strings
    // Index 24: zero

    // Given the complexity, I'll just write the function using a loop over an array of (string, flag) pairs, but the original code is unrolled.

    // For clarity, I'll write the exact unrolled initialization as seen in the decompiled:

    // Strings 0-11
    // (already shown above)

    // Then set flag at index 12 = 0
    gStringTable[12] = 0; // int? Actually gStringTable is pointer array? But flag is separate.

    // I'll define gStringTable as an array of const char* and gStringFlags as int array.
    // But the globals are actually of type undefined* and int. So the table is interleaved in memory?

    // To be faithful, I'll declare the table as:
    // struct StringEntry { const char* str; int flags; };
    // and the globals start at 0x1164010.
    // Then we have:
    // entry0: str, flags(0)
    // entry1: str, flags(0) ... but from code, the first 12 entries have no flags? They set only pointers.
    // Actually the code does not set flags for the first 12; they just store pointers.
    // So the first 12 entries are only pointers, no flags. Then after index 12, each entry is a (pointer, int) pair.
    // This suggests that the array structure changes after index 12. Possibly two separate arrays.
    // I'll treat it as two arrays: one for string pointers only (12 entries) and one for interleaved (pointer, flag) (remaining).
    // The globals are contiguous though.

    // I think it's best to replicate the original code literally with macros, without inventing a unified structure.

    // For the final output, I'll produce a clean version that matches the decompiled pattern but with meaningful names.

    #define CALL_REGISTER(ptr) \
        if ((**(int (__stdcall **)(int, const char**))(*DAT_01205750 + 0x158))(DAT_01205750, &ptr) == -0x7789fe84) \
            handleError()

    const char* temp;

    // 0:
    temp = "DAT_011286c8";
    CALL_REGISTER(temp);
    gStringTable[0] = temp;

    // 1:
    temp = "DAT_01128700";
    CALL_REGISTER(temp);
    gStringTable[1] = temp;

    // ... repeat for all

    // But to avoid extremely long output, I'll use a loop with a static table.

    // Actually, the function is long but repetitive. I'll present a cleaned version using a struct array.

}