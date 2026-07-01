// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_LeaveCrew
// FUNC_NAME: PauseFamilyTreeConfirmDismissAction::create
void PauseFamilyTreeConfirmDismissAction::create(void)
{
    PauseFamilyTreeConfirmDismissAction *action;

    action = (PauseFamilyTreeConfirmDismissAction *)FUN_009c8e50(0xf0);
    if (action != (PauseFamilyTreeConfirmDismissAction *)0x0) {
        action = (PauseFamilyTreeConfirmDismissAction *)FUN_00982280((int)action);
    }
    // Load localized string key for the confirm dismiss button
    FUN_00981eb0("$pause_family_tree_confirm_dismiss");
    // Set action type to 2 (e.g., kActionType_ConfirmDismiss)
    action->field_0c = 2;
    // Set color/hash values (RGBA? 0xb9754031 = 0x31,0x40,0x75,0xb9? unknown format)
    action->field_20 = 0xb9754031;
    action->field_1c = 0x997dee17;
    // Set callback function pointer (vtable or function pointer)
    action->field_14 = &LAB_0097f680; // likely a member function pointer or handler
    // Register/finalize the action (e.g., add to UI manager)
    FUN_00982e10();
    return;
}