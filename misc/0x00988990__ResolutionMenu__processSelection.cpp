// FUNC_NAME: ResolutionMenu::processSelection

// Address: 0x00988990
// Role: Handles the state transitions of a resolution dropdown menu. Manages initialization,
// user selection changes, and triggers UI updates.

void __fastcall ResolutionMenu::processSelection(int thisPtr)
{
    bool isProcessing = *(char *)(thisPtr + 0x50) != '\0';
    int state = *(int *)(thisPtr + 0x58);   // +0x58: state (probably 1 = active)
    int selectionIndex = *(int *)(thisPtr + 0x54); // +0x54: selected item index
    int currentIndex = *(int *)(thisPtr + 0x5c);  // +0x5c: current display index
    int previousIndex = *(int *)(thisPtr + 0x6c); // +0x6c: previous index

    if (isProcessing) {
        // Second call: user has made a selection, apply it
        if (state == 1 && selectionIndex == 0) {
            if (currentIndex != previousIndex) {
                *(char *)(thisPtr + 0x10d) = 1; // +0x10d: flag indicating index changed
            }

            // Read resolution data from array at +0xC0 (each entry is 12 bytes: width, height, refresh)
            float *resolutionData = *(float **)(thisPtr + 0xc0); // +0xC0: pointer to array of ResolutionInfo
            float *entry = resolutionData + currentIndex * 3; // each entry is 3 floats (width, height, refresh)

            // Store resolution as ints (cast from float, likely integer data stored as float)
            *(int *)(thisPtr + 0x114) = (int)entry[0]; // +0x114: width
            *(int *)(thisPtr + 0x110) = (int)entry[1]; // +0x110: height
            *(int *)(thisPtr + 0x118) = (int)entry[2]; // +0x118: refresh rate

            *(int *)(thisPtr + 0x6c) = currentIndex; // update previous index

            FUN_00987530(); // unknown, likely post-processing

            // Clear resolution list UI
            FUN_005a04a0("ClearResolutionList", 0, &DAT_00d90fa8, 0); // DAT_00d90fa8 is likely a string constant

            // Trigger event/timer
            int local_c = DAT_01130448; // some global event ID
            FUN_00408a00(&local_c, 0);
        }
        *(char *)(thisPtr + 0x50) = 0; // reset processing flag
    } else {
        // First call: initialize dropdown menu
        if (state == 1 && selectionIndex == 0) {
            FUN_00988770(); // unknown, possibly pre-initialization

            // Store current settings as previous
            *(int *)(thisPtr + 100) = *(int *)(thisPtr + 0xbc); // +0xbc: some initial value? (offset 100 = 0x64)
            *(int *)(thisPtr + 0x5c) = *(int *)(thisPtr + 0x6c); // set current index to previous

            // Show dropdown UI
            FUN_005a04a0("InitDropMenu", 0, &DAT_00d90fa8, 0);
            FUN_005a04a0("OpenDropSelection", 0, &DAT_00d90fa8, 0);

            *(char *)(thisPtr + 0x50) = 1; // set processing flag

            // Trigger event/timer
            int local_c = DAT_01130448; // same global event ID
            FUN_00408a00(&local_c, 0);
        }
    }
}