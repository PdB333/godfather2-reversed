// FUN_0049fa30: EventHandler::setTarget
void __thiscall EventHandler::setTarget(int this, int newTarget)
{
    int *arrayPtr;       // +0x8c: pointer to array of items
    int arrayCount;      // +0x90: number of items in array
    int *iter;           // loop iterator over array entries (4 bytes each)

    // Check if target at +0xb4 has changed
    if (*(int *)(this + 0xb4) != newTarget)
    {
        // Update the target
        *(int *)(this + 0xb4) = newTarget;

        // If flag at +0xac has bit 1 set, process the array
        if ((*(byte *)(this + 0xac) & 2) != 0)
        {
            arrayPtr = *(int **)(this + 0x8c);
            arrayCount = *(int *)(this + 0x90);

            // Iterate over the array (each entry is 4 bytes)
            if (arrayPtr != arrayPtr + arrayCount)
            {
                do {
                    // Calls a global function with a fixed argument (from DAT_012233a8+4)
                    // Note: The original decompiler shows that the argument is independent of the
                    // current array entry; this may be a decompilation artifact.
                    FUN_0042e760(*(int *)(DAT_012233a8 + 4));
                    iter = (int *)((int)arrayPtr + 4);
                } while (iter != arrayPtr + arrayCount);
            }
        }
    }
}