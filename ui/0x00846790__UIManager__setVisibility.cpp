//FUNC_NAME: UIManager::setVisibility
void __thiscall UIManager::setVisibility(int this, char visible, uint32_t data)
{
    // +0x118: flags bitfield (bit 4 = 0x10, bit 5 = 0x20, bit 6 = 0x40)
    if (visible != '\0') {
        if ((*(byte *)(this + 0x118) & 0x10) == 0) {
            // Global pointer to UI data (e.g., debug overlay buffer)
            if (DAT_0120685c != 0) {
                // Copy 0x8000 bytes from global data to this+0x3c
                FUN_00408900(this + 0x3c, &DAT_0120685c, 0x8000);
            }
            // Clear bits 5 and 6 (0x20 and 0x40) in flags
            *(uint *)(this + 0x118) = *(uint *)(this + 0x118) & 0xffffff9f;
        }
        // Show action (e.g., enable rendering)
        FUN_008427f0(0, 0, 0, data);
        return;
    }
    // Hide action (e.g., disable rendering)
    FUN_00842830(0, 0, 0, data);
    // Set bit 5 (0x20) and clear bit 6 (0x40) in flags
    *(uint *)(this + 0x118) = *(uint *)(this + 0x118) & 0xffffffbf | 0x20;
    return;
}