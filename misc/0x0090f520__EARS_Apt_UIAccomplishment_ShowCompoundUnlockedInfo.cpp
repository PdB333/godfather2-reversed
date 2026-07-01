// Xbox PDB: EARS_Apt_UIAccomplishment_ShowCompoundUnlockedInfo
// FUNC_NAME: CompoundAttackSummaryScreen::showSummary
// Address: 0x0090f520
// Role: Displays the compound attack summary screen with venue and attack info, sets callback.

void __fastcall CompoundAttackSummaryScreen::showSummary(void)
{
    char isValid;
    int compoundInfo;
    char** prefixPtr;
    char* prefixString;
    char* lastVenueString;
    char* attackCompoundString;
    char* imageString; // Possibly set elsewhere, used for SetImage
    int unused1;
    int unused2;
    void (*deallocFunc1)(char*);
    char* lastVenueFormatted;
    int unused3;
    int unused4;
    void (*deallocFunc2)(char*);
    char* attackCompoundFormatted;
    void (*deallocFunc3)(char*);

    // Tell the Flash movie to go to the "compound" frame
    scaleformInvoke("gotoAndPlay", 0, g_pSummaryMovieClip, 1, "compound");

    // Get the compound info object from this+0x80
    compoundInfo = getCompoundInfo(*(int*)(this + 0x80));
    if (compoundInfo != 0) {
        // Prepare formatted strings for the summary messages
        lastVenueFormatted = 0;
        unused3 = 0;
        unused4 = 0;
        deallocFunc2 = 0;
        attackCompoundFormatted = 0;
        unused1 = 0;
        unused2 = 0;
        deallocFunc1 = 0;

        // Get localization prefix (e.g., font name)
        prefixPtr = (char**)getLocalizationPrefix();
        prefixString = *prefixPtr;
        if (prefixString == 0) {
            prefixString = &DAT_0120546e; // Default empty string
        }
        formatString(&lastVenueFormatted, "{f:%s}{$summary_screen_last_venue}", prefixString);

        prefixPtr = (char**)getLocalizationPrefix();
        prefixString = *prefixPtr;
        if (prefixString == 0) {
            prefixString = &DAT_0120546e;
        }
        formatString(&attackCompoundFormatted, "{f:%s}{$summary_screen_attack_compound}", prefixString);

        // Show the message with two formatted strings and an additional parameter
        lastVenueString = lastVenueFormatted;
        if (lastVenueFormatted == 0) {
            lastVenueString = &DAT_0120546e;
        }
        attackCompoundString = attackCompoundFormatted;
        if (attackCompoundFormatted == 0) {
            attackCompoundString = &DAT_0120546e;
        }
        scaleformInvoke("ShowMessage", 0, g_pSummaryMovieClip, 3, lastVenueString, attackCompoundString, &DAT_00e2f044);

        // Update the compound summary image (offset +0x8c)
        updateCompoundSummary(compoundInfo + 0x8c);

        // Check if an image string is valid and set it
        imageString = 0; // Note: In original decomp, local_10 was never assigned; assume it's set elsewhere
        if (imageString == 0) {
            imageString = &DAT_0120546e;
        }
        isValid = isStringValid(imageString);
        if (isValid != 0) {
            scaleformInvoke("SetImage", 0, g_pSummaryMovieClip, 1, imageString);
        }

        // Set the callback function pointer at this+0x7c
        *(void**)(this + 0x7c) = &LAB_00980bf0; // Summary callback

        // Clean up formatted strings
        if (imageString != 0) {
            deallocFunc3(imageString); // deallocFunc3 corresponds to local_4
        }
        if (attackCompoundFormatted != 0) {
            deallocFunc1(attackCompoundFormatted); // deallocFunc1 corresponds to local_24
        }
        if (lastVenueFormatted != 0) {
            deallocFunc2(lastVenueFormatted); // deallocFunc2 corresponds to local_14
        }
    }
    return;
}