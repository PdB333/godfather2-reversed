// FUNC_NAME: ListContainer::trySelectItemByPath
// Address: 0x009529b0
// This function attempts to select an item in a list container by matching a given path string.
// It iterates over items with indices 0..maxItems-1, constructs a path like "/lang/mcMain/listContainer/item%d/hspt",
// compares it to input path, and if found and not already the current selection, sets the current index
// and triggers some action (likely updating the UI selection indicator).

char __thiscall ListContainer::trySelectItemByPath(int this, byte *targetPath)
{
    byte bVar1;
    byte *pbVar2;
    int iVar3;
    byte *pbVar4;
    char foundFlag;
    uint index;
    bool bVar7;
    byte formattedPath[64];  // buffer for constructed path

    foundFlag = '\0';   // false (0)
    index = 0;
    do {
        // Check if index is within bounds [0, maxItems)
        if (*(uint *)(this + 0x50) <= index) {
            return foundFlag;   // no match found
        }
        // Format the path string: "/lang/mcMain/listContainer/item%d/hspt"
        // FUN_00910160 likely acts like sprintf(dst, fmt, index)
        FUN_00910160(formattedPath, "/lang/mcMain/listContainer/item%d/hspt", index);

        // Compare formattedPath with targetPath (custom string compare)
        pbVar2 = formattedPath;
        pbVar4 = targetPath;
        do {
            bVar1 = *pbVar2;
            bVar7 = bVar1 < *pbVar4;
            if (bVar1 != *pbVar4) {
                // Paths differ
                iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                goto LAB_00952a09;
            }
            if (bVar1 == 0) break;          // end of strings reached
            bVar1 = pbVar2[1];
            bVar7 = bVar1 < pbVar4[1];
            if (bVar1 != pbVar4[1]) goto LAB_00952a09;
            pbVar2 = pbVar2 + 2;
            pbVar4 = pbVar4 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;   // strings are equal

LAB_00952a09:
        // If paths match and index is not equal to current selection (stored at +0x54)
        if ((iVar3 == 0) && (index != *(uint *)(this + 0x54))) {
            // Format the base item path (without "/hspt"): "/lang/mcMain/listContainer/item%d"
            FUN_00910160(formattedPath, &DAT_00e3266c, index);
            // Call an action function, likely to set the index in a UI list
            // Parameters: "SetIndex", 0, someStringOrCallback, 1, formattedPath
            // DAT_00d8bea0 might be a constant like "listContainer" or a callback id
            FUN_005a04a0("SetIndex", 0, &DAT_00d8bea0, 1, formattedPath);
            // Clear a flag at +0x58 (maybe something like "pendingSelectionChange" or "justSet")
            *(undefined4 *)(this + 0x58) = 0;
            foundFlag = '\x01';   // true
        }
        index = index + 1;
        if (foundFlag != '\0') {
            return foundFlag;
        }
    } while( true );
}