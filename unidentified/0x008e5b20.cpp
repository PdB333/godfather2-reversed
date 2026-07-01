// FUN_NAME: CrewSlotManager::getSlotPosition
// Address: 0x008e5b20
// This function looks up a crew slot by ID and returns the position (4 ints) for that slot.
// It checks various conditions (player state, family membership) before returning a primary or secondary position.

int* __thiscall CrewSlotManager::getSlotPosition(int thisPtr, int* outPosition, int slotId)
{
    int* pSlotArray = (int*)(thisPtr + 0x70); // Array of 8 slot structs, each 0x24 bytes, first int is ID
    int* pSecondaryPositions = (int*)(thisPtr + 0x74); // 8 secondary positions (4 ints each)
    int* pPrimaryPositions = (int*)(thisPtr + 0x84);   // 8 primary positions (4 ints each)

    outPosition[0] = 0;
    outPosition[1] = 0;
    outPosition[2] = 0;
    outPosition[3] = 0;

    for (int i = 0; i < 8; i++)
    {
        // Check if the slot ID matches
        if (*pSlotArray == slotId)
        {
            // Get some player/sentient object from this+0x50
            int* pPlayerObj = (int*)FUN_00446100(thisPtr + 0x50, 0);
            if (pPlayerObj != 0 && *(char*)(pPlayerObj + 0x1a5) != 0)
            {
                // Get singleton object (e.g., DonControlGadget or Presentation)
                int* pSingleton = (int*)FUN_008e33d0(1);
                int* temp = 0;
                bool bResult = (**(code**)(*pSingleton + 0x10))(0x254cce9, &temp); // Hash-> family/crew check
                if (bResult && unaff_EBX != 0) // unaff_EBX likely a global e.g., g_pPresentation
                {
                    // Check if current family is active
                    int iVar5 = (**(code**)(*unaff_EBX + 0x160))(); // e.g., getCurrentFamily
                    if (iVar5 != 0 && (*(byte*)(iVar5 + 0xd4) & 1) != 0)
                    {
                        // Copy primary position for this slot
                        int* pPrimary = pPrimaryPositions + i * 4;
                        outPosition[0] = pPrimary[0]; // offset 0
                        outPosition[1] = pPrimary[1]; // offset 4
                        outPosition[2] = pPrimary[2]; // offset 8
                        outPosition[3] = pPrimary[3]; // offset 12
                    }
                }
            }

            // If primary position is all zero, fallback to secondary position
            if (outPosition[0] == 0 && outPosition[1] == 0 && outPosition[2] == 0 && outPosition[3] == 0)
            {
                int* pSecondary = pSecondaryPositions + i * 4;
                outPosition[0] = pSecondary[0];
                outPosition[1] = pSecondary[1];
                outPosition[2] = pSecondary[2];
                outPosition[3] = pSecondary[3];
            }
            return outPosition;
        }
        pSlotArray += 9; // Move to next slot struct (9 ints = 0x24 bytes)
    }
    return outPosition; // Return the initially zeroed buffer if no slot found
}