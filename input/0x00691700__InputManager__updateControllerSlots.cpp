// FUNC_NAME: InputManager::updateControllerSlots
void __thiscall InputManager::updateControllerSlots(InputManager* thisPtr, int oldSlotIndex, int newSlotIndex)
{
    char byte565 = *((char*)thisPtr + 0x565);
    char byte564 = *((char*)thisPtr + 0x564);

    // First mapping table (primary - e.g., player 1)
    if (byte564 != 0x12) // if primary slot state is valid
    {
        short oldMapping = *((short*)(DAT_01129bd4 + oldSlotIndex * 2)); // value at oldSlot in primary table
        short newMapping = *((short*)(DAT_01129bd4 + newSlotIndex * 2)); // value at newSlot

        // set state for this controller type
        InputManager::setControllerState(byte564);

        int currentActive = InputManager::getCurrentPlayerIndex(); // current "active" controller index

        if (oldMapping != currentActive)
        {
            if (newMapping == currentActive)
            {
                // Update mapping: swap or reassign
                InputManager::updatePrimarySlot(oldSlotIndex, newSlotIndex);
            }
            else
            {
                int count = *(int*)(DAT_00e50698); // number of entries in remap list
                for (int i = count - 1; i >= 0; i--)
                {
                    if (*(int*)(DAT_00e50658 + i * 4) == newMapping)
                    {
                        *(int*)(DAT_00e50658 + i * 4) = oldMapping;
                        break;
                    }
                }
            }
        }
    }

    // Second mapping table (secondary - e.g., player 2)
    if (byte565 != 0x12) // if secondary slot state is valid
    {
        short oldMapping2 = *((short*)(DAT_01129bd0 + oldSlotIndex * 2));
        short newMapping2 = *((short*)(DAT_01129bd0 + newSlotIndex * 2));

        InputManager::setControllerState(byte565);

        int currentActive2 = InputManager::getCurrentPlayerIndex();

        if (oldMapping2 != currentActive2)
        {
            if (newMapping2 == currentActive2)
            {
                InputManager::updateSecondarySlot(oldSlotIndex, newSlotIndex);
                return;
            }

            int count2 = *(int*)(DAT_00e50650);
            if (count2 >= 0)
            {
                for (int i = count2 - 1; i >= 0; i--)
                {
                    if (*(int*)(DAT_00e50610 + i * 4) == newMapping2)
                    {
                        *(int*)(DAT_00e50610 + i * 4) = oldMapping2;
                        break;
                    }
                }
            }
        }
    }
}