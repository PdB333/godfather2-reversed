// FUNC_NAME: DropBox::closeDropSelection
void __fastcall DropBox::closeDropSelection(DropBox *this)
{
    // Local buffer for formatting the selection text (512 bytes)
    char formattedText[512];

    // Format the selection text using the stored string at offset +0xA04 (0x281 * 4)
    // FUN_005c4630 is likely a safe string formatting function (e.g., snprintf)
    formatString(formattedText, sizeof(formattedText), &DAT_00e3266c, *(const char **)((char *)this + 0xA04));

    // Send UI event to roll out the drop selection (show animation)
    sendUIEvent("RollOutDropSelection", 0, &DAT_00d8d668, 1, formattedText);

    // Send UI event to close the drop box
    sendUIEvent("CloseDropBox", 0, &DAT_00d8d668, 0);

    // Reset the first field of the object (likely a flag or state)
    *(int *)this = 0;
}