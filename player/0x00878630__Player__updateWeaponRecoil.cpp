// FUNC_NAME: Player::updateWeaponRecoil
void __thiscall Player::updateWeaponRecoil(int thisPtr, float deltaTime)
{
    // Access weapon component via +0x368 (likely m_weaponComponent or m_weaponManager)
    int weaponComponent = *(int *)(thisPtr + 0x368);
    // Access weapon data via +0x8c (likely m_currentWeaponData or m_weaponStats)
    int weaponData = *(int *)(weaponComponent + 0x8c);

    // Apply recoil values scaled by deltaTime
    // +0x0c: horizontal recoil (x-axis)
    *(float *)(weaponData + 0xc) = *(float *)(thisPtr + 0xe1c) * deltaTime;
    // +0x34: vertical recoil (y-axis)
    *(float *)(weaponData + 0x34) = *(float *)(thisPtr + 0xe20) * deltaTime;
    // +0x5c: horizontal spread (z-axis or secondary)
    *(float *)(weaponData + 0x5c) = *(float *)(thisPtr + 0xe24) * deltaTime;
    // +0x84: vertical spread (w-axis or secondary)
    *(float *)(weaponData + 0x84) = *(float *)(thisPtr + 0xe28) * deltaTime;
}