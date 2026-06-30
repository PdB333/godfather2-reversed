// FUNC_NAME: StringTable::buildMapping
// Address: 0x0065f6b0
// Builds a sorted index map for a linked list of wide-character strings.
// Each string gets a unique index; duplicates get the same index.

#include <stdlib.h>
#include <wchar.h>

// Global static data (initialized elsewhere)
static bool s_built = false;                     // DAT_0120589b
static StringNode* s_stringListHead = nullptr;   // DAT_01205a84
static wchar_t s_initialString[] = L"";          // DAT_00e2f044 (empty wide string)

struct StringNode {
    const wchar_t* string;   // +0x00
    int index;               // +0x04
    StringNode* next;        // +0x08
};

// Custom comparison function for qsort (sorted by string pointer, not content)
int __cdecl compareStringNodePtrs(const void* a, const void* b) {
    const StringNode* nodeA = *(const StringNode**)a;
    const StringNode* nodeB = *(const StringNode**)b;
    return (int)(nodeA->string - nodeB->string); // arbitrary order, later grouped by content
}

int __thiscall StringTable::buildMapping(void* thisPtr) {
    // Already built? Return cached value at +0x04
    if (s_built) {
        return *(int*)((char*)thisPtr + 4);
    }
    s_built = true;

    // Count nodes and fill a sorted pointer array
    int nodeCount = 0;
    int currentIndex = 0;
    const wchar_t* prevString = s_initialString; // base for first comparison
    StringNode* curr = s_stringListHead;
    StringNode** sortedArray = nullptr;

    while (curr) {
        // Allocate or extend sorted array (FUN_0065ffa0)
        // The function presumably returns a pointer to an array of (nodeCount+1) pointers.
        sortedArray = (StringNode**)FUN_0065ffa0(nodeCount + 1);
        // Store current node pointer
        sortedArray[nodeCount] = curr;
        curr = curr->next;
        nodeCount++;
    }

    // Sort by string pointer (address)
    qsort(sortedArray, nodeCount, sizeof(StringNode*), compareStringNodePtrs);

    // Assign contiguous indices based on string content
    // Use custom two-byte (UTF-16) string comparison
    for (int i = 0; i < nodeCount; i++) {
        const wchar_t* currentStr = sortedArray[i]->string;
        const wchar_t* pCur = currentStr;
        const wchar_t* pPrev = prevString;
        int cmp = 0;

        // Manual wcscmp (two-byte characters)
        while (*pCur && *pPrev) {
            if (*pCur != *pPrev) {
                cmp = (*pCur < *pPrev) ? -1 : 1;
                break;
            }
            pCur++;
            pPrev++;
        }
        if (cmp == 0) {
            // Strings equal, use same index
            sortedArray[i]->index = currentIndex;
        } else {
            // New unique string
            currentIndex++;
            sortedArray[i]->index = currentIndex;
            prevString = currentStr; // update base for next comparison
        }
    }

    // Free temporary array
    free(sortedArray); // PTR__free_00f0cd8c

    return *(int*)((char*)thisPtr + 4);
}