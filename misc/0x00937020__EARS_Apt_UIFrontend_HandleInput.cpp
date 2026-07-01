// Xbox PDB: EARS_Apt_UIFrontend_HandleInput
// FUNC_NAME: UIMenu::moveSelectionDown
void __thiscall UIMenu::moveSelectionDown(void) {
    // Log or dispatch UI event for moving selection down
    // FUN_005a04a0("MoveSelectionDown", 0, &DAT_00d8a0dc, 0);
    dispatchUISound("MoveSelectionDown", 0, &DAT_00d8a0dc, 0);

    // Build temporary structure from global data and zero-fill
    // Structure likely used for playing sound or UI effect
    struct {
        uint32_t field_0;  // from DAT_011302b0
        uint32_t field_4;  // zero
        uint8_t  field_8;  // zero
    } localStruct;
    localStruct.field_0 = DAT_011302b0; // global value
    localStruct.field_4 = 0;
    localStruct.field_8 = 0;

    // Initialize or play the sound effect
    // FUN_00408a00(&localStruct, 0);
    initializeOrPlayEffect(&localStruct, 0);
}