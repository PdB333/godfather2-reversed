// FUNC_NAME: NetPacketWindow::updateTimeouts

uint __thiscall NetPacketWindow::updateTimeouts(int* thisPtr)
{
    int basePtr;
    uint counter;
    int entryPtr;
    uint newStatus;
    uint index;

    basePtr = (int)thisPtr;
    if (thisPtr == (int*)0x0) {
        // Null pointer check, return error flag (original EAX masked)
        return 0;
    }

    // Copy or update something with stored data at +0x04 (size at +0x38)
    FUN_005dbc10(*(undefined4*)(basePtr + 4), *(undefined4*)(basePtr + 0x38));

    if (*(int*)(basePtr + 0x38) != 0) {
        // Iterate through an array of entries starting at offset +0x58
        int* entryArray = (int*)(basePtr + 0x58);
        index = 0;
        do {
            // Each entry is a relative offset from base +0x50
            entryPtr = *entryArray + *(int*)(basePtr + 0x50);

            // Check if entry status is not a sentinel value (0xDEADBEEF or -1)
            if (*(int*)(entryPtr + 0x48) != -0x21524111 && *(int*)(entryPtr + 0x48) != -1) {
                // Get new status (e.g., timestamp or ack flag)
                newStatus = FUN_005f0b20();
                *(int*)(entryPtr + 0x48) = newStatus;
            }

            if (*(int*)(entryPtr + 0x48) == 0) {
                // Status zero means invalid, clear the entry
                *entryArray = 0;
            }
            else {
                // Update position/time counters
                *(int*)(entryPtr + 0x4c) += *(int*)(basePtr + 0x20);
                *(int*)(entryPtr + 0x50) += *(int*)(basePtr + 0x28);

                // Copy 4-byte data from entry to some destination
                FUN_005dbc10(*(undefined4*)(entryPtr + 0x28),
                             *(undefined1*)(entryPtr + 0x21),
                             *(undefined1*)(entryPtr + 0x20),
                             *(undefined1*)(entryPtr + 0x23),
                             *(undefined1*)(entryPtr + 0x22));

                // Perform additional processing
                FUN_005f2490();

                // Update the entry pointer in the array
                *entryArray = entryPtr;
            }

            entryArray++;
            index++;
        } while (index < *(uint*)(basePtr + 0x38));

        return (uint)(((byte)(index >> 8) << 24) | 1); // Return success with some index info packed
    }

    return 1;
}