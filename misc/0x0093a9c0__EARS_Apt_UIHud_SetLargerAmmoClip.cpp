// Xbox PDB: EARS_Apt_UIHud_SetLargerAmmoClip
//FUNC_NAME: Player::setShowLargerAmmoClip
// Address: 0x0093a9c0
// Sets whether to show a larger ammo clip indicator. Updates flags and triggers UI event.

void __thiscall Player::setShowLargerAmmoClip(int thisPtr, bool show)
{
    // Update flag at +0x5c (bit 25 = 0x2000000) based on show parameter
    if (show) {
        *(uint32_t*)(thisPtr + 0x5c) |= 0x2000000;
    } else {
        *(uint32_t*)(thisPtr + 0x5c) &= ~0x2000000;
    }

    // Check if the object is active (+0x48) and not in a certain state (+0x49 & 0x0A == 0)
    if (*(char*)(thisPtr + 0x48) != '\0' && (*(byte*)(thisPtr + 0x49) & 0x0A) == 0) {
        // If showing and bit 27 (+0x5c >> 27 & 1) is set, show larger clip
        if (show && (*(uint32_t*)(thisPtr + 0x5c) >> 0x1b & 1) != 0) {
            sendUIEvent("ShowLargerAmmoClip", 0, &DAT_00d8a64c, 0);
            return;
        }
        // Otherwise hide larger clip
        sendUIEvent("HideLargerAmmoClip", 0, &DAT_00d8a64c, 0);
    }
}