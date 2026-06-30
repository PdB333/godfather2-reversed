// FUNC_NAME: Player::setCurrentWeapon
void __thiscall Player::setCurrentWeapon(Player* this, uint32_t weaponIndex)
{
    // +0x230: Current weapon identifier (e.g. index or handle)
    this->currentWeapon = weaponIndex;

    // +0x20: Pointer to weapon slot manager (WeaponSlotManager*)
    // +0x04 of that manager: Active weapon index
    WeaponSlotManager* slotManager = *(WeaponSlotManager**)((uintptr_t)this + 0x20);
    if (slotManager)
    {
        slotManager->activeWeapon = weaponIndex;
    }
}