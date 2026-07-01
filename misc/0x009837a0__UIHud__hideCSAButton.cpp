//FUNC_NAME: UIHud::hideCSAButton
void __thiscall UIHud::hideCSAButton(int this) {
    // Set the CSA button visibility state to hidden via a generic UI property setter
    // Arguments: property name, value (0 = hidden), data pointer, flags (0)
    setUIProperty("HideCSAButton", 0, &g_uiStateData, 0);
    // +0x108: CSA button ID or state; set to -1 (invalid/disabled)
    *(int *)(this + 0x108) = -1;
}