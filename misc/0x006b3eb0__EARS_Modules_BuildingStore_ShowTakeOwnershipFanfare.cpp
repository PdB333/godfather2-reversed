// Xbox PDB: EARS::Modules::BuildingStore::ShowTakeOwnershipFanfare
// FUNC_NAME: SummaryScreenControl::showVenueInfo
// Function address: 0x006b3eb0
// This method displays venue information on the summary screen control overlay.
// It lazily loads the venue name if not already loaded, formats a display string,
// and sends it to the UI system.

void __fastcall SummaryScreenControl::showVenueInfo(void)
{
    char *formattedString = NULL;
    undefined4 local_c; // unused
    undefined4 local_8; // unused
    code *stringDeleter = NULL; // deleter function pointer, potentially set by FormatString

    // Check if venue name needs to be loaded from ID
    if (*(int *)(this + 0xe4) == 0) {
        // Load venue name from venue ID (stored at +0xdc) into venue name pointer (+0xe0)
        FUN_00603330(*(undefined4 *)(this + 0xdc), this + 0xe0);
    }

    // Get venue name string, default to empty string if null
    char *venueName = *(char **)(this + 0xe0);
    if (venueName == NULL) {
        venueName = &DAT_0120546e; // likely empty string constant
    }

    // Format string: "{v:%s}{$summary_screen_control_venue}"
    FUN_004d4ad0(&formattedString, "{v:%s}{$summary_screen_control_venue}", venueName);

    // Update raw pointer with dereference for safety (duplicate of formattedString)
    char *displayStr = formattedString;
    if (formattedString == NULL) {
        displayStr = &DAT_0120546e;
    }

    // Send the formatted text to the UI summary screen control system
    FUN_0093f600(displayStr, 0, 0, this, &LAB_006b29f0);

    // Free allocated string if it was allocated
    if (formattedString != NULL) {
        (*stringDeleter)(formattedString); // Note: stringDeleter is null, may be a bug or static deleter
    }

    return;
}