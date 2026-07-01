// Xbox PDB: EARS_Apt_UIHud_HideTutorial
// FUNC_NAME: TutorialManager::dismissTutorial
void __thiscall TutorialManager::dismissTutorial(TutorialManager* this, int targetObject)
{
    // local struct for tutorial dismissal data (e.g., GUID + flags)
    struct TutorialDismissalData {
        uint32_t data1; // +0x00
        uint32_t data2; // +0x04
        uint8_t  flags; // +0x08
    } dismissalData;

    // Check if target is null or matches the current tutorial target (stored at +0xC8 = 200)
    if ((targetObject == 0) || (*(int*)((uintptr_t)this + 0xC8) == targetObject)) {
        // If tutorial sound flag (bit 15 of +0x5C) is set, stop sound and close UI
        if ((*(uint32_t*)((uintptr_t)this + 0x5C) >> 15) & 1) {
            // stop tutorial sound (slot 10)
            FUN_006915c0(10);
            // close some UI (arg 1)
            FUN_0040eaf0(1);
            // Clear bit 15 (tutorial sound active)
            *(uint32_t*)((uintptr_t)this + 0x5C) &= 0xFFFF7FFF;
        }

        // Send "HideTutorial" message globally (string, 0, DAT_00d8a64c, 0)
        FUN_005a04a0("HideTutorial", 0, &DAT_00d8a64c, 0);

        // Clear bit 14 (tutorial visible flag?)
        *(uint32_t*)((uintptr_t)this + 0x5C) &= 0xFFFFBFFF;

        // Prepare dismissal data (likely a GUID from global)
        dismissalData.data1 = DAT_011304b0;
        dismissalData.data2 = 0;
        dismissalData.flags = 0;

        // Call finalization function with the data
        FUN_00408a00(&dismissalData, 0);
    }
}