// FUNC_NAME: DonControlGadget::updateSelectionHighlights
void DonControlGadget::updateSelectionHighlights(bool isInteractive, uint highlightColor)
{
    // Global arrays indexed by player/target indices
    // s_playerIndex and s_targetIndex are likely current selection indices in the Don Control interface
    // The arrays at gSelectionList (0x01125400) and gTargetList (0x011254b0) hold pointers to UI elements or entity data
    
    if (gSelectionList[s_playerIndex * 0x38] != nullptr)
    {
        removeFromList(gSomeCollection1, gSelectionList[s_playerIndex * 0x38]);
    }
    if (gSelectionList[s_playerIndex * 0x38 + 4] != nullptr) // next slot?
    {
        removeFromAnotherList(gSomeCollection1, gSelectionList[s_playerIndex * 0x38 + 4]);
    }
    
    // Now handle target list for the secondary index
    if (gTargetList[s_targetIndex * 0x3c] != nullptr)
    {
        if ((isInteractive) && (gDonControlManager != nullptr) && (*(int *)(gDonControlManager + 0x24) != 0))
        {
            // Call a virtual method on the object at gDonControlManager+0x24 (likely DonControlGadget's internal manager)
            // The vtable entry at offset 4 is something like "getSelectedEntityData" – returns a pointer to a structure
            int entityDataPtr = (**(code **)(**(int **)(gDonControlManager + 0x24) + 4))(this + 0x30);
            if (entityDataPtr != 0)
            {
                // Add the entity's data to the target highlight list
                addToList(gSomeCollection2, gTargetList[s_targetIndex * 0x3c], entityDataPtr + 0x10);
                
                // Prepare a color/structure from entity data offsets
                uint localColor[4];
                localColor[0] = *(uint *)(entityDataPtr + 0x20); // color r
                localColor[1] = *(uint *)(entityDataPtr + 0x24); // color g
                localColor[2] = *(uint *)(entityDataPtr + 0x28); // color b
                localColor[3] = highlightColor;                  // color a
                
                addToList(gSomeCollection2, gTargetList[s_targetIndex * 0x3c + 4], &localColor);
                addToList(gSomeCollection1, gSelectionList[s_playerIndex * 0x38 + 0x30], entityDataPtr);
                addToList(gSomeCollection1, gSelectionList[s_playerIndex * 0x38 + 0x34],
                         *(int *)(**(int **)(this + 0x2c) + 0x24) + 0x70);
                return;
            }
        }
        // Fallback: clear highlight
        uint zeroColor[4] = {0, 0, 0, 0};
        addToList(gSomeCollection1, gSelectionList[s_playerIndex * 0x38 + 0x30], &zeroColor);
    }
}