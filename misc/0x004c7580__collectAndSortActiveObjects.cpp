// FUNC_NAME: collectAndSortActiveObjects
// Function address: 0x004c7580
// Role: Collects active objects (flag bit 5 set) from an array and sorts them by a key.
// The object array is at this+0x50, count at this+0x34, each object size 0xB0.
// Flag byte at object+8, bit 0x20 indicates active.
// Sort key at object+4 (assumed).
// Uses global buffer g_sortBuffer (8-byte entries: pointer + key) and g_sortCount.

#include <stdlib.h> // for qsort

// Global variables (from DAT_01163ee0 and DAT_01163edc)
static void* g_sortBuffer; // base of 8-byte entries
static int g_sortCount;     // number of entries

// Comparator function at 0x004c7560 (not shown, assumed to compare keys)
extern "C" int __cdecl sortComparator(const void* a, const void* b);

void __fastcall collectAndSortActiveObjects(void* thisPtr)
{
    int count = *(int*)((char*)thisPtr + 0x34);
    if (count == 0)
        return;

    int baseOffset = 0;
    unsigned int index = 0;
    do {
        void* objectPtr = *(void**)((char*)thisPtr + 0x50) + baseOffset; // base + offset
        char flags = *(char*)((char*)objectPtr + 8);
        if (flags & 0x20) {
            // Store pointer and sort key into global buffer
            void** entry = (void**)((char*)g_sortBuffer + g_sortCount * 8);
            entry[0] = objectPtr;
            entry[1] = (void*)*(int*)((char*)objectPtr + 4); // sort key at offset 4
            g_sortCount++;
        }
        index++;
        baseOffset += 0xB0;
    } while (index < (unsigned int)count);

    // Sort the collected entries by key
    qsort(g_sortBuffer, g_sortCount, 8, sortComparator);
}