// FUNC_NAME: ControllerState::getActiveButtonAction
int ControllerState::getActiveButtonAction(ControllerState* this)
{
    uint buttonFlags = *(uint*)((int)this + 0x1c); // +0x1c: bitfield of pressed/relevant buttons
    // Returns action ID (0xc through 0x10) based on which bit (2-6) is set.
    // Used to map physical buttons to gameplay actions.
    if ((buttonFlags >> 2 & 1) != 0) {
        return 0xc; // Action mapped to bit 2
    }
    if ((buttonFlags >> 3 & 1) != 0) {
        return 0xd; // Action mapped to bit 3
    }
    if ((buttonFlags >> 4 & 1) != 0) {
        return 0xe; // Action mapped to bit 4
    }
    if ((buttonFlags >> 5 & 1) != 0) {
        return 0xf; // Action mapped to bit 5
    }
    if ((buttonFlags >> 6 & 1) != 0) {
        return 0x10; // Action mapped to bit 6
    }
    return -1;
}