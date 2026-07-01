// FUNC_NAME: TableModel::sortByColumn

#include <cstdlib> // for qsort

// Forward declaration of a global pointer to the game manager (DAT_01130044)
extern GameManager* g_pGameManager; // +0x00: pointer to singleton

// Forward declaration of the comparator function used by qsort (FUN_00918c30)
extern "C" int __cdecl sortByColumnComparator(const void* a, const void* b);

// Forward declaration of a function that sends UI commands (FUN_005a04a0)
// Parameters: command string, int arg0, some global identifier, int arg1
void ExecuteUICommand(const char* command, int arg0, void* id, int arg1);

// Forward declaration of the helper function (FUN_00917060) that returns sort data
// based on the current game state. Returns true if successful, and fills outBase and outCount.
bool GetCurrentSortData(int*& outBase, int& outCount);

// Method definition for sorting a column in a table-like list
// param_1 = this, param_2 = columnIndex (0-based)
void __thiscall TableModel::sortByColumn(int columnIndex)
{
    int* base = nullptr;          // _Base
    uint count = 0;                // _NumOfElements

    // Retrieve the current game state from the singleton game manager
    int gameState = *(int*)(g_pGameManager + 0xb8);  // +0xb8: eGameState

    if ((gameState == 10) || (gameState == 11) || (gameState == 12))
    {
        // State: main menu or similar screens
        count = *(uint*)(this + 0x50);  // +0x50: number of elements in first array
        if (count < 2)
            goto skipSort;
        base = *(int**)(this + 0x4c);   // +0x4c: pointer to first array of ints
    }
    else if (gameState == 25)
    {
        // State: some specific screen (0x19)
        count = *(uint*)(this + 0x5c);  // +0x5c: number of elements in second array
        if (count < 2)
            goto skipSort;
        base = *(int**)(this + 0x58);   // +0x58: pointer to second array
    }
    else if ((gameState == 13) || (gameState == 14) || (gameState == 15) ||
             (gameState == 16) || (gameState == 17))
    {
        // State: additional screens
        count = *(uint*)(this + 0x68);  // +0x68: number of elements in third array
        if (count < 2)
            goto skipSort;
        base = *(int**)(this + 0x64);   // +0x64: pointer to third array
    }
    else
    {
        // Fallback: get sort data from a helper function
        int* helperBase = nullptr;
        int helperCount = 0;
        if (!GetCurrentSortData(helperBase, helperCount) || helperCount < 2)
            goto skipSort;
        base = helperBase;
        count = helperCount;
    }

    // Sort the array using the predefined comparator
    qsort(base, count, sizeof(int), sortByColumnComparator);

skipSort:
    // Update UI highlighting: first unhighlight the old sorted title
    ExecuteUICommand("UnhighlightSortedTitle", 0, &DAT_00d8510c, 0);

    // Store the new sorted column index (1-indexed) in the game manager
    *(int*)(g_pGameManager + 0xdc) = columnIndex + 1;  // +0xdc: currentSortedColumn

    // Highlight the newly sorted title
    ExecuteUICommand("HighlightSortedTitle", 0, &DAT_00d8510c, 0);
}