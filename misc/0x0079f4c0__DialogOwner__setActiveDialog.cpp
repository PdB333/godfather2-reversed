// FUNC_NAME: DialogOwner::setActiveDialog
void __thiscall DialogOwner::setActiveDialog(int dialogID)
{
    // Get the global dialog system singleton (e.g., DialogManager)
    DialogSystem* pDialogSystem = nullptr;
    if (this != nullptr) {
        pDialogSystem = (DialogSystem*)getDialogSystem(DAT_01131010);
    }

    if (dialogID == 0) {
        // Clear current dialog: check if one is stored
        if (this->m_currentDialogID != 0) {
            DialogHandle handle = getDialogHandle(this->m_currentDialogID);
            bool isActive = isDialogIdActive(this->m_currentDialogID);
            if (isActive) {
                // Call virtual stop dialog (vtable+0x24)
                (**(code**)(*(int*)pDialogSystem + 0x24))(handle);
            }
            this->m_currentDialogID = 0;
        }
        return;
    }

    // Set a new dialog
    DialogHandle handle = getDialogHandle(dialogID);
    bool isActive = isDialogIdActive(dialogID);
    if (!isActive) {
        this->m_currentDialogID = dialogID;
        // Call virtual prepare/attach owner (vtable+0x1c)
        (**(code**)(*(int*)pDialogSystem + 0x1c))(this);
        // Call virtual play dialog (vtable+0x20)
        (**(code**)(*(int*)pDialogSystem + 0x20))(handle);
    }
}