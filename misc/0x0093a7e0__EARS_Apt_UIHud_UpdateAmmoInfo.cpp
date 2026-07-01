// Xbox PDB: EARS_Apt_UIHud_UpdateAmmoInfo
// FUNC_NAME: HUDManager::updateAmmoDisplay
void __thiscall HUDManager::updateAmmoDisplay(HUDManager *this, WeaponData *weapon) {
    char ammoText[128]; // +0xe4 buffer
    _memset(this->ammoTextBuffer, 0, 0x80);

    if (weapon == NULL) {
        if ((this->flags & 0x40) == 0) {
            return;
        }
        sendUIEvent("HideWeaponDisplay", 0, &g_uiEventManager, 0);
        this->flags &= 0xe7ffff3f; // clear weapon display flags
        return;
    }

    if (weapon->isGun != 0) { // +0x1a8 - flag for gun type
        if ((weapon->infiniteAmmoFlag & 0x20) == 0) { // +0x2d8 bit5
            int magazineAmmo = weapon->currentMagazineAmmo; // +0x328
            int totalAmmo = getTotalAmmo();
            formatString(this->ammoTextBuffer, 0x80, "%d-%d", magazineAmmo, totalAmmo - magazineAmmo);
        } else {
            formatString(this->ammoTextBuffer, 0x80, "%d-[b=Infinity]", weapon->currentMagazineAmmo);
        }
        goto updateUI;
    }

    // Not a gun weapon - different ammo types
    int playerIndex = **(int**)(g_globalObject + 4); // DAT_012233a0
    if (playerIndex == 0 || playerIndex == 0x1f30) {
        playerIndex = 0;
    } else {
        playerIndex = *(int*)(playerIndex + 0x578);
    }
    if (playerIndex == 0) {
        goto updateUI;
    }

    int ammoCount;
    char weaponType = weapon->weaponType; // +0x1ad
    if (weaponType == 0x1a) {
        ammoCount = getCurrentMagazineAmmo();
    } else if (weaponType == 0x19) {
        ammoCount = getReserveAmmo();
    } else if (weaponType == 0x1b) {
        ammoCount = getSpecialAmmo();
    } else {
        goto updateUI;
    }
    formatString(this->ammoTextBuffer, 0x80, "%d", ammoCount);

updateUI:
    if ((this->flags & 0x40) != 0) {
        sendUIEvent("UpdateAmmoInfo", 0, &g_uiEventManager, 0);
    }
    return;
}