// FUNC_NAME: UIPopupManager::populateItems

void __fastcall UIPopupManager::populateItems(int thisPtr)
{
    *(byte *)(thisPtr + 0x9c) = 1;                     // mark as complete

    char inputPath[96];   // buffer for "/text/.../item%d/instance8/input"
    char hotspotPath[108];// buffer for "/text/.../item%d/instance8/hotspot"
    // small buffer (16 bytes) used internally, initialized to zero
    char tempBuffer[16] = {0};

    int itemCount = *(int *)(thisPtr + 0x74);
    if (itemCount != 0)
    {
        int structOffset = 0;
        uint index = 0;
        do
        {
            // build Flash paths for this item index
            formatItemPath(inputPath,
                "/text/popup_root/popup/contentPlaceHolderMc/item%d/instance8/input",
                index);
            formatItemPath(hotspotPath,
                "/text/popup_root/popup/contentPlaceHolderMc/item%d/instance8/hotspot",
                index);

            // get MovieClip references from paths
            int inputClip = getFlashMovieClip(inputPath);
            clearMovieClip(inputClip);                     // remove previous content

            setupItemInteraction(inputPath, hotspotPath, tempBuffer, thisPtr);

            // retrieve per-item data from array (struct size 0x4C)
            int itemDataBase = *(int *)(thisPtr + 0x70);   // pointer to item array
            int itemValue = *(int *)(itemDataBase + 0x44 + structOffset); // +0x44: value/data
            int clipWithValue = getFlashMovieClip(inputPath, itemValue);
            setMovieText(clipWithValue, itemValue);        // display value

            // determine the item type from +0x48 field
            int itemType = *(int *)(itemDataBase + 0x48 + structOffset);
            char *typeLabel;
            switch (itemType)
            {
            case 0:
            case 1:
                typeLabel = "textInput";   // LAB_00989f40
                break;
            case 2:
                typeLabel = "button";      // DAT_0098d580
                break;
            case 3:
            case 4:
                typeLabel = "textInput";   // LAB_00989f40 (same as 0,1)
                break;
            case 5:
                typeLabel = "toggle";      // LAB_0098a020
                break;
            case 6:
                typeLabel = "slider";      // LAB_00989ff0
                break;
            case 7:
                typeLabel = "dropdown";    // DAT_0098d5a0
                break;
            case 8:
                typeLabel = "checkbox";    // LAB_00989f60
                break;
            case 9:
                typeLabel = "radioButton"; // DAT_0098d5c0
                break;
            default:
                typeLabel = "textInput";   // fallback
                break;
            }

            int clipWithLabel = getFlashMovieClip(inputPath, typeLabel);
            setMovieProperty(clipWithLabel, typeLabel);

            structOffset += 0x4C;
            index++;
        } while (index < (uint)itemCount);
    }

    finalizePopupItems();  // FUN_0098e910
}