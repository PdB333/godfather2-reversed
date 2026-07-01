//FUNC_NAME: TargetingManager::findBestTarget
uint __fastcall TargetingManager::findBestTarget(int *thisPtr)
{
    // thisPtr is 'this' for TargetingManager
    // Offset 0x60: m_targetIterator (pointer to an iterator object)
    int *iterator = (int *)thisPtr[0x18]; // 0x18 * 4 = 0x60
    short bestScore = 0;
    int bestTargetNode = 0;
    int currentScore;
    int currentNode;
    int temp;

    if (iterator != 0) {
        // Check if iterator has a current node (offset 0x8 from iterator)
        if (*(int *)(iterator + 8) == 0) {
            currentNode = 0;
        } else {
            currentNode = (int)iterator;
        }

        bestTargetNode = 0;
        while (currentNode != 0) {
            // Call a global function (PTR_FUN_00d79c8c) - likely returns some context data
            temp = (*(code *)PTR_FUN_00d79c8c)();

            // Virtual call on this: vtable+0xE4, takes argument from temp+8, returns a short score
            currentScore = (**(code **)(*thisPtr + 0xE4))(*(int *)(temp + 8));

            // Call iterator's getCurrent (first vtable entry)
            temp = (*(code *)*iterator)();

            // Check if current node is valid (byte at offset 0x30 & 1)
            if ((*(byte *)(temp + 0x30) & 1) != 0 &&
                (bestTargetNode == 0 || bestScore < currentScore)) {
                // Update best
                bestTargetNode = (*(code *)*iterator)(); // Re-call getCurrent? Possibly a bug; maybe it's a different function
                bestScore = (short)currentScore;
            }

            // Advance iterator (second vtable entry)
            iterator = (int *)(*(code *)iterator[1])(); // iterator[1] is second vtable entry
        }
        // Return the last iterator pointer with low byte cleared (handle)
        return (uint)iterator & 0xFFFFFF00;
    }
    return 0;
}