// UIScreenBase::setOptionEnabled
void __thiscall UIScreenBase::setOptionEnabled(bool enabled)
{
    // this + 0x168 points to an internal option/sub-object
    int subObj = *(int *)(this + 0x168);
    char currentEnabled = *(char *)(subObj + 0x62);

    if (enabled != currentEnabled) {
        // Update the enabled flag
        *(char *)(subObj + 0x62) = enabled;

        // Call virtual function at vtable index 10 (offset 0x28) with command 4
        // (likely "update" or "stateChanged")
        (**(code **)(*(int *)(this + 0x58) + 0x28))(4);

        // If setting to disabled, also issue command 2 (e.g., "deactivate" or "hide")
        if (enabled == 0) {
            (**(code **)(*(int *)(this + 0x58) + 0x28))(2);
        }
    }
}