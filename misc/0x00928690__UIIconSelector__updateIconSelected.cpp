// FUNC_NAME: UIIconSelector::updateIconSelected
void __thiscall UIIconSelector::updateIconSelected() {
    // Set selected icon index/state to 5 (e.g., kIconSelected or kStateActive)
    *(int*)(this + 0x5C) = 5;
    // Broadcast event that an icon was selected (likely to UI system or listeners)
    FUN_005a04a0("UpdateIconSelected", 0, &DAT_00d87b2c, 0);
}