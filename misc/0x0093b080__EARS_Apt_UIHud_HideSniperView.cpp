// Xbox PDB: EARS_Apt_UIHud_HideSniperView
// FUNC_NAME: CameraManager::hideSniperView
void __fastcall CameraManager::hideSniperView(CameraManager* this) {
    // Check if sniper view is visible (bit 29 of flags at +0x5c)
    if ((this->flags & 0x20000000) != 0) {
        // Clear the sniper view visible flag
        this->flags &= 0xDfffffff;

        // Notify gameplay: hide sniper view
        postGameplayEvent("HideSniperView", 0, &DAT_00d8a64c, 0);

        // Internal cleanup for sniper view state
        endSniperView();

        // If we are not in a "suppress all" state (bit 19 clear), unsuppress everything
        if ((this->flags & 0x00080000) == 0) {
            postGameplayEvent("UnSuppressAll", 0, &DAT_00d8a64c, 0);
        }
    }
}