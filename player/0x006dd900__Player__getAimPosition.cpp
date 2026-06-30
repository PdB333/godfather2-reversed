// FUNC_NAME: Player::getAimPosition
void __thiscall Player::getAimPosition(float *outPosition, WeaponData *weaponData, int someFlag)
{
    float *initialPos;
    float *localPtr;
    float resultFloat;
    float delta;
    Vector3 localOffset;
    
    // Check weapon type: if weaponData->type != 0 and != kWeaponTypeGun (0x48)
    if ((weaponData->type != 0) && (weaponData->type != kWeaponTypeGun)) {
        // Get player transform (camera or root)
        PlayerTransform *playerTransform = getPlayerTransform();
        // Copy forward/aim vector from transform (offset 0x30 - 0x38)
        outPosition[0] = playerTransform->forward.x;
        outPosition[1] = playerTransform->forward.y;
        outPosition[2] = playerTransform->forward.z;
        
        // Get parent object from weaponData (embedded base at +8, parent at -0x48)
        void *weaponBase = (weaponData->somePointer == 0) ? 0 : (void *)((int)weaponData->somePointer - 0x48);
        localPtr = 0;
        // Virtual call: query a float with hash 0x55859efa (possibly muzzle height offset)
        if ((***(int (__thiscall**)(void*, uint, float**))weaponBase)(0x55859efa, &localPtr) && (resultFloat != 0.0f)) {
            if ((*(uint8_t*)(this->someState + 0x8e3) & 1) == 0) {
                // Interpolate between weaponData->offset1 and offset2 based on the returned float
                delta = (weaponData->offset1 - weaponData->offset2) * (float)localPtr + weaponData->offset2;
            } else {
                delta = weaponData->offset3;
            }
            outPosition[1] = outPosition[1] + delta;
        }
        return;
    }
    
    // For other weapons (or when type == 0 or == kWeaponTypeGun)
    computeWeaponLocalOffset(&localOffset, weaponData, someFlag);
    PlayerTransform *playerTransform = getPlayerTransform();
    outPosition[0] = playerTransform->position.x + localOffset.x;
    outPosition[1] = playerTransform->position.y + localOffset.y;
    outPosition[2] = playerTransform->position.z + localOffset.z;
    transformVector(&localOffset, outPosition, outPosition);
}