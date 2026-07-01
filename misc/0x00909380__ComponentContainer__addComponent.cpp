// FUNC_NAME: ComponentContainer::addComponent

void __thiscall ComponentContainer::addComponent(int thisPtr, int unusedParam, int componentPtr)
{
    int slotIndex = 0;
    int *currentSlot = (int *)(thisPtr + 0x70); // slot array base

    // Find a free slot (first field == 0 or first field == 0x48)
    while ((*currentSlot != 0) && (*currentSlot != 0x48))
    {
        slotIndex++;
        currentSlot += 2; // each slot is 8 bytes
        if (slotIndex > 5)
        {
            // All slots full, remove component from previous list
            FUN_004088c0(componentPtr + 0x3c); // owner list removal
            return;
        }
    }

    // Pointer to the chosen slot
    int *chosenSlot = (int *)(thisPtr + 0x70 + slotIndex * 8);

    // Determine the value to store in the slot's first field:
    // For a null component, store 0; otherwise store address of component's type field (+0x48)
    int targetValue = (componentPtr != 0) ? (componentPtr + 0x48) : 0;

    if (*chosenSlot != targetValue)
    {
        // If slot currently holds a different component, detach it
        if (*chosenSlot != 0)
        {
            FUN_004daf90(chosenSlot); // detach slot from its current component
        }

        // Set slot's first field to target value
        *chosenSlot = targetValue;

        if (targetValue != 0)
        {
            // Link the slot into the component's list of slots:
            // Slot's second field becomes the component's previous head
            chosenSlot[1] = *(int *)(targetValue + 4); // component's next pointer at +0x4C
            // Set component's next pointer to point to this slot
            *(int **)(targetValue + 4) = chosenSlot;
        }
    }

    // Check if any condition requires removing from owner list
    if ((slotIndex > 5) ||
        (*(int *)(thisPtr + 0x64) == 0) ||
        (*(int *)(thisPtr + 0x64) == 0x48) ||
        ((*(byte *)(thisPtr + 0xb4) & 1) != 0))
    {
        FUN_004088c0(componentPtr + 0x3c); // remove from owner list
    }
}