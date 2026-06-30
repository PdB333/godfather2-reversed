// FUNC_NAME: StringTableLoader::loadFromBuffer
// Address: 0x00604ff0
// Role: Parse a binary localization string table buffer and populate a StringTable structure.
// The buffer format appears to be: a header with count and entry size, then entries with 5 string fields (32 chars each) and two IDs.
// This function allocates memory for the table and populates it.

#include <stdlib.h>
#include <string.h>

// Forward declarations for helper functions (inlined from other modules)
extern "C" int FUN_00605690(void* buffer, void** outPtr); // parse buffer header, returns string pointer
extern "C" unsigned int FUN_00605df0(void); // get entry count or version
extern "C" void* FUN_009c8e80(int size); // custom allocator
extern "C" void FUN_00605e30(unsigned int param); // cleanup?
extern "C" int FUN_006052d0(void* table, int param); // add string entry?
extern "C" void FUN_00605340(int a, int b, int c); // error handling?
extern "C" int FUN_006054b0(void* table, int param); // add ID entry?
extern "C" void FUN_00605520(int a, int b); // error handling?
extern "C" void FUN_009c8f10(void* ptr); // custom free

// Structure representing one localization string entry (32 bytes each, 5 fields)
struct StringEntry {
    char key[32];        // +0x04 offset from base? Actually param_2+1 is the start of key
    char strings[4][32]; // Four additional strings (offsets +9, +0x11, +0x19, +0x21)
    int id1;             // +0x29
    int id2;             // +0x2a
    int stringTablePtr;  // +0x2b
    int stringTablePtr2; // +0x2c
};

// The main load function - param_2 is the output StringTable
StringEntry* __thiscall FUN_00604ff0(void* thisPtr, StringEntry* outTable)
{
    unsigned int entryCount;
    int numEntries;
    char* bufferPos;
    int i;
    int result;
    StringEntry* newTable;
    StringEntry* currentEntry;
    char tempStr[32];
    char tempStr2[32];
    char tempStr3[32];
    char tempStr4[32];
    char tempStr5[32];
    int field1, field2;

    // Initialize output table fields (first 4 ints? Actually param_2 points to the structure)
    outTable->key[0] = 0; // +0x04 relative to param_2? Actually param_2+1 is the start of key (offset 4 bytes)
    // Wait: param_2 is a pointer to an array of undefined4 (4-byte values). The decompiled code shows:
    // *param_2 = param_1 (store this pointer at offset 0)
    // *(undefined1 *)(param_2 + 1) = 0; // sets byte at offset 4? Actually param_2+1 is a pointer offset by 4 bytes (sizeof(undefined4) = 4)
    // So param_2[0] = this, then the string fields start at param_2+1, param_2+9, etc.
    // This implies a struct: uintptr_t base; char str1[32]; char str2[32]; char str3[32]; char str4[32]; char str5[32]; int a; int b; int c; int d;
    // Let's be more precise:

    struct StringTableHeader {
        void* basePtr;      // offset 0x00
        char field1[32];    // offset 0x04
        char field2[32];    // offset 0x24
        char field3[32];    // offset 0x44
        char field4[32];    // offset 0x64
        char field5[32];    // offset 0x84
        int value1;         // offset 0xA4
        int value2;         // offset 0xA8
        int stringArrayPtr; // offset 0xAC
        int intArrayPtr;    // offset 0xB0
    };

    StringTableHeader* table = (StringTableHeader*)outTable;

    table->basePtr = thisPtr;
    table->field1[0] = 0;
    table->field2[0] = 0;
    table->field3[0] = 0;
    table->field4[0] = 0;
    table->field5[0] = 0;
    table->value1 = 0;
    table->value2 = 0;
    table->stringArrayPtr = 0;
    table->intArrayPtr = 0;

    // Call base class method (likely virtual table function at offset 8)
    (**(code**)(*(int*)thisPtr + 8))();

    bufferPos = (char*)FUN_00605690(outTable, &outTable);
    if (bufferPos != NULL) {
        entryCount = FUN_00605df0(); // get some count from global?
        if (_atol(bufferPos) == 7) { // version check (7)
            numEntries = (entryCount - 6) / 6; // calculate number of entries

            // Allocate arrays for string pointers and int pointers (size 0x61 and 0x60 per entry)
            table->stringArrayPtr = (int)(*(code**)(**(int**)table->basePtr))(numEntries * 0x61, &tempStr);
            table->intArrayPtr = (int)(*(code**)(**(int**)table->basePtr))(numEntries * 0x60, &tempStr);

            // Allocate a temporary block for parsed entries (size = entryCount * 4? )
            StringEntry* parsedEntries = (StringEntry*)FUN_009c8e80(entryCount * 4);
            FUN_00605e30(*(unsigned int*)&thisPtr); // likely passes some ID

            // Copy the first 5 strings from parsed buffer into output table
            bufferPos = (char*)parsedEntries[1].key; // Actually parsedEntries[1] is the first entry? hmm
            // The decompiled code: pcVar6 = (char *)puVar10[1]; // puVar10 is the allocated block
            // Then copy to table->field1
            char* src = (char*)((int*)parsedEntries)[1];
            if (src != NULL && *src != '\0') {
                _strncpy(table->field1, src, 31);
                i = 31;
            }
            table->field1[i] = '\0';

            src = (char*)((int*)parsedEntries)[2];
            if (src != NULL && *src != '\0') {
                _strncpy(table->field2, src, 31);
                i = 31;
            }
            table->field2[i] = '\0';

            src = (char*)((int*)parsedEntries)[3];
            if (src != NULL && *src != '\0') {
                _strncpy(table->field3, src, 31);
                i = 31;
            }
            table->field3[i] = '\0';

            src = (char*)((int*)parsedEntries)[4];
            if (src != NULL && *src != '\0') {
                _strncpy(table->field4, src, 31);
                i = 31;
            }
            table->field4[i] = '\0';

            src = (char*)((int*)parsedEntries)[5];
            if (src != NULL && *src != '\0') {
                _strncpy(table->field5, src, 31);
                i = 31;
            }
            table->field5[i] = '\0';

            // Now loop over numEntries, each entry consists of 6 ints (index 6..11 in parsedEntries)
            for (currentEntry = parsedEntries; numEntries != 0; numEntries--) {
                // Read fields from parsed entry
                result = FUN_006052d0(table, ((int*)currentEntry)[6]); // add string?
                if (result < 0) {
                    FUN_00605340(((int*)currentEntry)[8], ((int*)currentEntry)[11], ((int*)currentEntry)[9]);
                }
                result = FUN_006054b0(table, ((int*)currentEntry)[7]); // add int?
                if (result < 0) {
                    FUN_00605520(((int*)currentEntry)[8], ((int*)currentEntry)[10]);
                }
                // Skip ahead 6 ints (since each entry group uses indices 6-11)
                currentEntry = (StringEntry*)((int*)currentEntry + 6);
            }

            FUN_009c8f10(parsedEntries); // free temp buffer

            // Call another virtual function with 0
            (**(code**)(*(int*)table->basePtr + 4))(*(unsigned int*)&thisPtr, 0);
        }
    }
    return (StringEntry*)outTable;
}