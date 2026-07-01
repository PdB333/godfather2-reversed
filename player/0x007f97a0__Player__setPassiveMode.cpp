// FUNC_NAME: Player::setPassiveMode
void __thiscall Player::setPassiveMode(Player* this, bool enable)
{
    // Offset 0x8EC: flags bitfield (bit 8 = kPassiveFlag)
    const uint kPassiveFlag = 0x100;

    if (enable) {
        // Call vtable method at offset 0x284 (virtual function #0xA1) with arguments (8, 1)
        // This likely sets a state/enum value (e.g., state 8 = passive, 1 = active)
        (**(code (__thiscall**)(int,int))(*this + 0x284))(8, 1);

        // If passive flag was not already set, notify sub-component at offset 0x58
        if (((uint)this->flags >> 8 & 1) == 0) {
            // Sub-component at offset 0x58 (e.g., InputManager or CharacterController)
            // Its vtable method at offset 0x28 (virtual function #0xA) with argument 0x20
            // 0x20 likely disables input/ai control (e.g., kDisableFlag)
            (**(code (__thiscall**)(int))(this->subComponent + 0x28))(0x20);
        }

        // Set the passive flag
        this->flags = this->flags | kPassiveFlag;

        // Call external helper to propagate the change
        FUN_007ef9b0(enable);
        return;
    }

    // If passive was active, disable sub-component input
    if (((uint)this->flags >> 8 & 1) != 0) {
        (**(code (__thiscall**)(int))(this->subComponent + 0x28))(0x20);
    }

    // Clear the passive flag
    this->flags = this->flags & ~kPassiveFlag;

    // Propagate
    FUN_007ef9b0(enable);
}