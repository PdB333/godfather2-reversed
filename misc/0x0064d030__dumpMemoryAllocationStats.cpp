// FUNC_NAME: dumpMemoryAllocationStats
// Address: 0x0064d030
// Role: Iterates over a linked list of memory allocation statistics (initial and partial) and prints them.

#include <cstdio> // for printf-like function

// Global linked list head (likely from a memory manager singleton)
extern int g_memoryAllocListHead; // DAT_012059ec

// Constant used for signed-to-unsigned conversion (2^32)
static const float kTwoToThe32 = 4294967296.0f; // DAT_00e44578

// Structure for each allocation statistics node
struct AllocStatsNode {
    char name[32];          // +0x20: name string (offset 0x20 from node start)
    int totalSizeInitial;   // +0x60: sum of sizes for initial allocations
    int countInitial;       // +0x68: count of initial allocations
    int countPartial;       // +0x6c: count of partial allocations
    int totalSizePartial;   // +0x64 (offset 100 = 0x64): sum of sizes for partial allocations
    AllocStatsNode* next;   // +0x70: next node in linked list
};

// Forward declaration of debug print function (likely a custom printf)
void debugPrintf(const char* format, ...); // FUN_0065bc40

void dumpMemoryAllocationStats() {
    debugPrintf(); // Possibly a newline or header? The decompiled shows a call with no arguments first.

    AllocStatsNode* node = reinterpret_cast<AllocStatsNode*>(g_memoryAllocListHead);
    while (node != nullptr) {
        // Print initial allocation stats
        if (node->countInitial != 0) {
            float totalSizeFloat = static_cast<float>(node->totalSizeInitial);
            if (node->totalSizeInitial < 0) {
                totalSizeFloat += kTwoToThe32; // Convert negative to unsigned range
            }
            float countFloat = static_cast<float>(node->countInitial);
            if (node->countInitial < 0) {
                countFloat += kTwoToThe32;
            }
            double avgSize = static_cast<double>(totalSizeFloat / countFloat);
            debugPrintf("%s (Initial) - Count: %d   Avg Size: %g",
                        node->name, node->countInitial, avgSize);
        }

        // Print partial allocation stats
        if (node->countPartial != 0) {
            float totalSizeFloat = static_cast<float>(node->totalSizePartial);
            if (node->totalSizePartial < 0) {
                totalSizeFloat += kTwoToThe32;
            }
            float countFloat = static_cast<float>(node->countPartial);
            if (node->countPartial < 0) {
                countFloat += kTwoToThe32;
            }
            double avgSize = static_cast<double>(totalSizeFloat / countFloat);
            debugPrintf("%s (Partial) - Count: %d   Avg Size: %g",
                        node->name, node->countPartial, avgSize);
        }

        node = node->next;
    }
}