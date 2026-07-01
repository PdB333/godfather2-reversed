// Xbox PDB: EARS_Apt_UIAccomplishment_ShowAllMonopolyControlledInfo
// FUNC_NAME: playAllCrimeRingsCompletedFanfare
// Function address: 0x0090edb0
// Purpose: Plays the "all crime rings completed" fanfare animation and shows the associated message.

void playAllCrimeRingsCompletedFanfare(void)
{
    // Play the "all_mono" movie clip (likely the fanfare for all crime rings)
    FUN_005a04a0("gotoAndPlay",          // ActionScript method on a GFx object
                 0,                      // Unknown parameter (maybe frame?)
                 &DAT_00d83810,          // Target GFx object (e.g., a DisplayObject or MovieClip)
                 1,                      // Number of arguments to follow
                 "all_mono");            // Label/identifier of the clip to play

    // Show the "All Crime Rings" completion message (localized strings)
    FUN_005a04a0("ShowMessage",          // ActionScript method to display a message
                 0,                      // Unknown parameter (maybe index or channel?)
                 &DAT_00d83810,          // Same target object
                 3,                      // Number of arguments to follow
                 "$fanfare_all_crime_rings_01", // First line of message (usually title)
                 "$fanfare_all_crime_rings_02", // Second line (description)
                 &DAT_00e2f044);        // Additional parameter (maybe a callback or data)
    return;
}