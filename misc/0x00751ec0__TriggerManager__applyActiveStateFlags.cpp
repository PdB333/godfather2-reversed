// FUNC_NAME: TriggerManager::applyActiveStateFlags
void __fastcall TriggerManager::applyActiveStateFlags(int thisPtr)
{
    int currentNode;
    char *flagArray;

    // Check if the enable flag at +0x100 is set
    if (*(int *)(thisPtr + 0x100) != 0)
    {
        // Get head of linked list from +0x1c
        currentNode = *(int *)(thisPtr + 0x1c);
        if (currentNode != 0)
        {
            // Pointer to array of boolean flags at +0x104 (one byte per node)
            flagArray = (char *)(thisPtr + 0x104);
            do
            {
                // Call helper to set the state based on flag (non-zero = true)
                FUN_00624ca0(*flagArray != '\0');
                // Move to next node (next pointer at +0x1c of each node)
                currentNode = *(int *)(currentNode + 0x1c);
                flagArray++;
            } while (currentNode != 0);
        }
    }
    // Clear the enable flag
    *(int *)(thisPtr + 0x100) = 0;
}