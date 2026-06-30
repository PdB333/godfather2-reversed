// FUNC_NAME: SummaryScreen::setupVenue
// Address: 0x006b3eb0
// This function sets up the venue name for the summary screen control. It constructs a formatted string
// with the venue name and passes it to a UI display function. It also handles cleanup of allocated string.
void __fastcall SummaryScreen::setupVenue(int thisPtr)
{
    // Locals for string buffer
    char *buffer; // local_10, initially null
    int someId;   // local_c, initially 0
    int someFlag; // local_8, initially 0
    void (*destroyFunc)(char *); // local_4, destructor function pointer, initially null

    buffer = (char *)0x0;
    someId = 0;
    someFlag = 0;
    destroyFunc = (void (*)(char *))0x0;

    // Check if venue string is already set at offset +0xE4
    // If not set, resolve the venue ID (at +0xDC) into a string pointer (at +0xE0)
    if (*(int *)(thisPtr + 0xE4) == 0) {
        // FUN_00603330 likely resolves venueId to venueName string
        FUN_00603330(*(undefined4 *)(thisPtr + 0xDC), thisPtr + 0xE0);
    }

    // Get the venue name string from offset +0xE0
    char *venueName = *(char **)(thisPtr + 0xE0);
    if (venueName == (char *)0x0) {
        // Default empty string (DAT_0120546e is likely "" or a placeholder)
        venueName = (char *)&DAT_0120546e;
    }

    // Format string: "{v:%s}{$summary_screen_control_venue}"
    // This constructs a UI command string with the venue name
    FUN_004d4ad0(&buffer, "{v:%s}{$summary_screen_control_venue}", venueName);

    char *formattedString = buffer;
    if (formattedString == (char *)0x0) {
        formattedString = (char *)&DAT_0120546e;
    }

    // Call UI display function with the formatted string, constants, and a callback target
    // FUN_0093f600 is likely a UI command executor (e.g., pushScreen or setText)
    FUN_0093f600(formattedString, 0, 0, thisPtr, (void (*)())0x006b29f0);

    // Cleanup allocated string buffer if it was allocated
    if (buffer != (char *)0x0) {
        // destroyFunc is the destructor for the string allocated by FUN_004d4ad0
        // (In the decompiled output it appears uninitialized, but actually it is set by the allocator)
        (*destroyFunc)(buffer);
    }

    return;
}