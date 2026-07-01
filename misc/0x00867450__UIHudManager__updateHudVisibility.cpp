// FUNC_NAME: UIHudManager::updateHudVisibility
void __thiscall UIHudManager::updateHudVisibility()
{
    // FUN_008651a0: checks if HUD is currently visible/active
    if (!isHudVisible())
    {
        // FUN_005fe6f0: hides all HUD elements
        hideHud();
        // Clear bits 25-27 (0x0E000000) in the visibility flags at offset +0xF28.
        // These bits likely correspond to minimap, health bar, and objective overlays.
        *(uint32_t*)(this + 0xF28) &= 0xF1FFFFFF;
    }
}