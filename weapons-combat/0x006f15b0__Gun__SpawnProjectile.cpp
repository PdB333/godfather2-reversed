// FUNC_NAME: Gun::SpawnProjectile
// Address: 0x006f15b0
// Role: Handles the registration and initialization of a new projectile/bullet from a weapon fire event.
// Uses a slot-based pool at offset +0x24 (each slot 0x20 bytes) to track active projectiles.
// Validates target, weapon data, and game state before creating a bullet slot and launching it.

bool __thiscall Gun::SpawnProjectile(
    Vec3* origin,           // param_2: origin point of bullet spawn
    Vec3* direction,        // param_3: travel direction vector
    Entity* targetEntity,   // param_4: target entity (NPC, player, etc.)
    int* weaponItem,        // param_5: pointer to item ID hash of weapon used (offset -0x48 used for lookup)
    int bulletSlotIndex,    // param_6: scratch index used in bullet slot update
    uint flags,             // param_7: flags bitmask (bit 1 set if weapon has special property?)
    int extraData           // param_8: extra data (e.g., damage modifier or override value)
) {
    bool success = false;

    // Require a valid target
    if (targetEntity == nullptr)
        return false;

    // Each entity has a bullet data block at +0x24 (pointer to array/struct)
    int* bulletDataBlock = *(int**)((char*)targetEntity + 0x24); // +0x24: pointer to bullet data
    if (bulletDataBlock == nullptr)
        return false;

    // Get global weapon database ID (likely a hash)
    int weaponDBID = DAT_01205214;
    // Global function: returns a session/order index
    int sessionIndex = GetSessionIndex(); // FUN_006f5530
    // Look up weapon definition from bullet data block
    WeaponDef* weaponDef = (WeaponDef*)LookupWeaponDef(bulletDataBlock, weaponDBID); // FUN_006f5190

    if (weaponDef != nullptr &&
        weaponDef->somePtr != nullptr && // +0x0c? Actually weaponDef[3] is a pointer
        *(short*)((char*)weaponDef->somePtr + 0x1c) != -1) // +0x1c: short weaponTypeID? Must not be -1
    {
        // Game state checks: not in some special state, and not in another state
        if (IsGameStateAllowed() && !IsInMenuState()) // FUN_00445250, FUN_004209a0
        {
            // Allocate a projectile handle
            int projectileHandle = AllocateProjectileHandle(); // FUN_006fc460
            // Convert handle to an index in the pool
            int poolIndex = HandleToPoolIndex(projectileHandle); // FUN_006f0520

            // Calculate pointer to a bullet slot in the pool (array at this+0x24, each slot 0x20)
            BulletSlot* slot = (BulletSlot*)((char*)this + 0x24 + poolIndex * 0x20);
            slot->targetEntity = targetEntity;          // +0x0c
            slot->projectileHandle = projectileHandle;  // +0x10
            slot->bulletDataBlock = bulletDataBlock;    // +0x08
            slot->field14 = *(int*)((char*)weaponDef->somePtr + 0x10); // +0x14: copy from weapon def
            slot->field18 = 0;                            // +0x18

            byte isSpecialWeapon = 0;
            int param4 = extraData;

            // Check if we have a weapon item
            if (*weaponItem != 0) {
                int weaponID = *weaponItem - 0x48; // Subtracting 0x48 converts item hash to weapon type ID?
                if (weaponID != 0) {
                    // Possibly get weapon distance/range data
                    int rangeData = GetWeaponRangeData(weaponID); // FUN_006eafe0
                    if (rangeData != 0)
                        param4 = *(int*)(rangeData + 0xe0); // Override extraData with range value
                }
                // Check if weapon has a specific property (hash 0x383225a1)
                if (*weaponItem == 0)
                    weaponID = 0;
                else
                    weaponID = *weaponItem - 0x48;
                // Does the weapon have a special flag?
                int hasSpecial = CheckWeaponProperty(weaponID, 0x383225a1); // FUN_006c9470
                if (hasSpecial != 0)
                    isSpecialWeapon = 1;
            }

            // Set bit 1 if special weapon
            flags = (isSpecialWeapon ? 2 : 0) | flags;
            slot->flags = flags; // +0x1c

            // Register this slot with a callback list (push onto some queue)
            RegisterBulletSlot(0x006f1570, slot); // FUN_006fbc40, constant likely a label/funcPtr

            // Now attempt to launch the projectile
            if (*weaponItem == 0)
                weaponID = 0;
            else
                weaponID = *weaponItem - 0x48;
            // local_10 is a 16-byte buffer (maybe projectile trajectory data)
            char result = LaunchProjectile(weaponDef->somePtr, slot->trajectoryBuffer /* local_10 */,
                                           weaponID, flags, param4); // FUN_006fe6b0
            success = (result != 0);

            if (success) {
                // Update bullet slot index + session offset
                UpdateBulletSlotArray(bulletSlotIndex + sessionIndex); // FUN_006fbe20

                // Write back to bullet data block: store projectile handle's +0x18 value
                *bulletDataBlock = *(int*)(projectileHandle + 0x18);
                // Get speed from global data
                float speed = GetGlobalSpeed(weaponDBID); // FUN_006f4d20
                bulletDataBlock[1] = *(int*)&speed;       // store as float

                // Copy origin and direction vectors into the bullet data (or somewhere)
                CopyVec3(origin);      // FUN_006f0bf0
                CopyVec3Sum(direction); // FUN_006f0c20 (maybe adds something)

                // Increment weapon def's count
                weaponDef->count++; // +0x00
                // Store current weapon DB ID
                weaponDef->field08 = weaponDBID; // +0x08
                // Write global ID to origin+0x0c (overwrites part of the vector struct)
                *(int*)((char*)origin + 0x0c) = weaponDBID;
            } else {
                // Clean up the slot on failure
                slot->targetEntity = nullptr;
                slot->projectileHandle = 0;
                slot->bulletDataBlock = nullptr;
                slot->field14 = 0;
                slot->flags = 0;
            }

            // Pop the callback/slot from registration
            PopBulletSlotRegistration(); // FUN_006fbc70
        }
    }

    return success;
}