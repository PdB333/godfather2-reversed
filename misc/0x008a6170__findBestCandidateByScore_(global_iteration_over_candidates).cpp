// FUNC_NAME: findBestCandidateByScore (global iteration over candidates)
// 0x008a6170 - Find the best candidate from a container using a global iterator.
// The container is valid if non-null and its +0x8 field is non-null.
// Scores each candidate via FUN_008a6100, returns the ID (+0x8) of the highest-scoring candidate,
// or -1 if none found.

// Global iterator function pointers (defined elsewhere)
extern int (*g_getCurrentItem)(void);      // PTR_FUN_00e35c28 – returns current item pointer
extern void (*g_advanceIterator)(void);     // _UNK_00e35c2c – advances to next item

unsigned int findBestCandidateByScore(void* container) {
    unsigned short bestScore = 0;
    unsigned int bestCandidateId = 0xFFFFFFFF;

    // Determine if we have a valid container
    void* current = 0;
    if (container != 0 && *(int*)((int)container + 8) != 0) {
        current = container; // container itself used as loop flag
    }

    // Loop over items (loop condition never changes in decompiled code,
    // likely relies on global iterator state or decompilation artifact)
    while (current != 0) {
        // Get the current item from the global iterator
        void* candidate = (void*)g_getCurrentItem();
        unsigned short score = FUN_008a6100(*(int*)((int)candidate + 8));

        if (bestScore < score) {
            // Better candidate found – get its ID (second call to iterator may be redundant)
            candidate = (void*)g_getCurrentItem();
            bestCandidateId = *(unsigned int*)((int)candidate + 8);
            bestScore = score;
        }

        // Advance the global iterator to next item
        g_advanceIterator();
    }

    return bestCandidateId;
}