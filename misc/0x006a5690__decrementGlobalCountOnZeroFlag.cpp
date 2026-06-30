// FUNC_NAME: decrementGlobalCountOnZeroFlag
// Function address: 0x006a5690
// Role: Decrements a global counter at the address stored in g_pGlobalManager at offset +0x6a0,
//       but only if the second parameter (flag) is 0 and the counter is positive.

// Forward declaration for the global manager pointer (likely points to a singleton game manager).
extern void* g_pGlobalManager;

void decrementGlobalCountOnZeroFlag(int unused, int flag) {
    if (flag == 0 && g_pGlobalManager != nullptr) {
        // Access the integer counter at offset +0x6a0 from the manager base.
        int* count = reinterpret_cast<int*>(static_cast<char*>(g_pGlobalManager) + 0x6a0);
        if (*count > 0) {
            (*count)--;
        }
    }
}