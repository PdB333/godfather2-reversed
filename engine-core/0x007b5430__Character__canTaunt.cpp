// FUNC_NAME: Character::canTaunt
// Address: 0x007b5430
// Checks if a character can perform a taunt based on state, weapon, and environmental conditions.

bool Character::canTaunt(PlayerController* player, Character* character)
{
    // Check if character is alive or something? vtable+0xC0 returns a float (e.g., health?)
    float health = (*(float (__thiscall**)(void*))(*(int*)character + 0xC0))();
    if (health <= 0.0f) {
        return false;
    }

    // Check various state flags: bitfields at offsets 0x239, 0x238, 0x23a
    if (((uint)character->field_0x239 >> 0x16 & 1) != 0) { // e.g., stunned or ragdoll
        return false;
    }
    if (((uint)character->field_0x238 >> 4 & 1) != 0) { // e.g., in cover?
        return false;
    }
    if (((uint)character->field_0x23a >> 0x1c & 1) != 0) { // e.g., driving?
        return false;
    }
    if (((uint)character->field_0x23a >> 0x1d & 1) != 0) { // e.g., climbing?
        return false;
    }

    // Check global action flags (input modes etc.)
    if (areInputsBlocked(5)) { // e.g., cinematics, menu?
        return false;
    }

    if (character->field_0x79c != 0) { // some pointer or count
        return false;
    }

    // Check specific action availability: taunt (0x25,0x26,0x27,0x29 are action IDs)
    if (areInputsBlocked(0x25)) { // e.g., action "taunt" blocked
        return false;
    }
    if (areInputsBlocked(0x26) || areInputsBlocked(0x27) || areInputsBlocked(0x29)) {
        return false;
    }

    // Get distance to target? player->vtable+0x218 returns a float (e.g., range)
    float range = (*(float (__thiscall**)(void*))(*(int*)player + 0x218))();
    if (!isCharacterInRange(character, range)) {
        return false;
    }

    // Check weapon
    int currentWeapon = character->field_0x226; // +0x226
    int weaponState = character->field_0x225; // +0x225 (flags)
    if ((currentWeapon != 0) && (currentWeapon != 0x48) && // 0x48 is unarmed? fists?
        ((weaponState & 1) != 0 || ((weaponState >> 3) & 1) != 0)) { // weapon in hand or equipped?
        // If weapon is not 0 and not unarmed, check specific weapon animation state
        int weaponBase = (currentWeapon == 0) ? 0 : (currentWeapon - 0x48); // offset to weapon data
        if ((*(byte*)(weaponBase + 0x120) & 0x10) == 0) { // weapon animation not ready?
            return false;
        }
    }

    // Check if character is performing an action (vtable+0x1BC)
    bool isPerformingAction = (*(char (__thiscall**)(void*))(*(int*)character + 0x1BC))();
    int someGlobalPtr1 = getGlobalObject(DAT_01131040);
    if ((!isPerformingAction) || (someGlobalPtr1 != 0 && ((*(uint*)(someGlobalPtr1 + 0x48) >> 1) & 1) == 0)) {
        // Check player's mode
        if ((character->field_0x208 >> 2 & 1) == 0) { // not in some special state
            int someGlobalPtr2 = getGlobalObject(DAT_01131018);
            if (someGlobalPtr2 == 0) {
                return true;
            }
            else {
                if (!canPerformTauntAnimation(player)) {
                    return false;
                }
            }
        }

        // Create bullet effect or spawn projectile? 
        isPerformingAction = (*(char (__thiscall**)(void*))(*(int*)character + 0x1BC))();
        int timeData = getGameTimeData();
        // Build two positions based on time
        float pos1_x = (float)((ulonglong)*(undefined8*)(timeData + 0x30) >> 0x20) + DAT_00d5ef50;
        float pos1_y = *(float*)(timeData + 0x38); // z or y?
        // ... (similar for pos2)
        spawnBulletEffect(0x40122, pos1, pos2, (isPerformingAction ? 0x30000 : 0x10000), 0, 0);

        // Setup some callback structure
        // ...

        if (someCondition) {
            return true;
        }
    }
    return false;
}