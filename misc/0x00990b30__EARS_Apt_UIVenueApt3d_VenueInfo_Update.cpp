// Xbox PDB: EARS_Apt_UIVenueApt3d_VenueInfo_Update
// FUNC_NAME: Building::updateVenueInfo
void __thiscall Building::updateVenueInfo(void)
{
    char buf1[32];
    char buf2[32];
    // Get venue data from some ID at +0x40
    int venueData = FUN_006b0ee0(*(int*)(this + 0x40));
    if (venueData != 0) {
        // Check if venue update is needed, passing three fields: +0x0c, +0x20, +0x34
        char result = FUN_00992d00(venueData, this + 0x0c, this + 0x20, this + 0x34);
        if (result != 0) {
            // Build strings: level from +0x44 (short) and base ID from +0x40
            _sprintf(buf1, "_level%u", (int)*(short*)(this + 0x44));
            _sprintf(buf2, "%u", *(int*)(this + 0x40));
            // Log the update (category "UpdateVenueInfo", level flag, venue ID)
            FUN_005a04a0("UpdateVenueInfo", 0, buf1, 1, buf2);
        }
    }
    return;
}