// FUNC_NAME: InitGlobalList
// This function initializes a global circular doubly linked list head structure.
// It retrieves the head from FUN_00485090, zeroes the key pointer fields,
// sets two flag bytes at offsets +0x14 and +0x15 to 1, makes the list circular
// by having prev/next/extra point to itself, and resets the global count.

struct GlobalListHead {
    GlobalListHead* pPrev;      // +0x00
    GlobalListHead* pNext;      // +0x04
    GlobalListHead* pExtra;     // +0x08
    // 12 bytes padding (0x0C–0x13)
    byte    flagA;              // +0x14 (0x14)
    byte    flagB;              // +0x15 (0x15)
};

// Globals
GlobalListHead*  g_pGlobalListHead = nullptr;   // DAT_012239a0
int              g_globalListCount = 0;          // _DAT_012239a4

// External function that returns a GlobalListHead*
GlobalListHead* FUN_00485090(void);

void InitGlobalList(void)
{
    g_pGlobalListHead = FUN_00485090();

    if (g_pGlobalListHead != nullptr)
    {
        // Zero the three pointer fields
        g_pGlobalListHead->pPrev  = nullptr;
        g_pGlobalListHead->pNext  = nullptr;
        g_pGlobalListHead->pExtra = nullptr;

        // Set flag bytes (likely indicates list is active/initialized)
        g_pGlobalListHead->flagA = 1;
        g_pGlobalListHead->flagB = 1;

        // Make the list circular (sentinel pointing to itself)
        g_pGlobalListHead->pNext  = g_pGlobalListHead;
        g_pGlobalListHead->pPrev  = g_pGlobalListHead;
        g_pGlobalListHead->pExtra = g_pGlobalListHead;
    }

    g_globalListCount = 0;
}