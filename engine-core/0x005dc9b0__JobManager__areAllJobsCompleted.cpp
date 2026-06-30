// FUNC_NAME: JobManager::areAllJobsCompleted
// Address: 0x005dc9b0
// The function iterates over a linked list of job nodes (each node at +0x10 has a completion flag, +0x1c is next pointer).
// Returns true if all jobs are completed, false if any job is incomplete.

// Note: The decompilation shows a potential loop variable update omission; the logic is reconstructed to reflect a standard linked list traversal.
bool JobManager::areAllJobsCompleted()
{
    // this +0x08 likely holds pointer to the head sentinel node of the job list
    int* headNode = *(int**)(this + 8);
    bool hasIncomplete = false;

    if (headNode == nullptr)
    {
        hasIncomplete = true; // empty list treated as incomplete? Alternatively could be true; see logic.
    }
    else
    {
        int* currentNode = *(int**)(headNode + 0x1c); // head->next (first real node)
        int* sentinelNext = *(int**)(headNode + 0x1c); // sentinel's initial next pointer (will break when we return to sentinel)

        while (true)
        {
            // Debug assertions ensuring valid pointers
            if ((headNode == nullptr) || (headNode != *(int**)(this + 8)))
            {
                FUN_00b97aea(); // assert
            }
            if (currentNode == sentinelNext) break; // returned to start of list (sentinel's next)
            if (headNode == nullptr)
            {
                FUN_00b97aea(); // assert
            }
            if (currentNode == *(int**)(headNode + 0x1c))
            {
                FUN_00b97aea(); // assert (redundant)
            }

            int* jobData = currentNode;
            // offset +0x10: completion flag (0 = incomplete, non-zero = complete)
            if (*(int*)(jobData + 0x10) == 0)
            {
                hasIncomplete = true;
                // Advance to next job (implementation likely updates global pointer)
                FUN_005e09e0();
            }
            else
            {
                // Process completed job and advance
                FUN_005dd660();
                FUN_005e09e0();
            }

            // Advance to next node (omitted in decompilation but necessary for loop progression)
            currentNode = *(int**)(currentNode + 0x1c);
        }
    }
    return !hasIncomplete;
}