// FUNC_NAME: refreshSelectedVenue

void refreshSelectedVenue(void)
{
    // Possibly part of DonControlGadget or BuildingManager UI update
    // Calls internal refresh and UI update with "RefreshSelectedVenue" event
    FUN_00957350();
    FUN_005a04a0("RefreshSelectedVenue", 0, &DAT_00d8ca78, 0);
    FUN_005c1b40();
    return;
}