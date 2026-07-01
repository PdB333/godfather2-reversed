// FUNC_NAME: Weapon::getCurrentAttackData

int __thiscall Weapon::getCurrentAttackData(Weapon *this, Entity *entity, AttackData **outAttackData)
{
    int attackDataPtr;

    // Entity must be valid
    if (entity == nullptr)
        return 0;

    // Weapon type field at +0x164: 1 = melee, 2 = ranged
    if (this->weaponType == 1) {
        // Melee: get attack data from entity's animation component (+0x180 -> +0x40)
        attackDataPtr = FUN_008c74d0(*(uint*)(*(int*)(entity->animationComponent) + 0x40));
    }
    else if (this->weaponType == 2) {
        // Ranged: get attack data from entity's ammo component (+0x1ED8)
        if (entity->ammoComponent == 0)
            return 0;
        attackDataPtr = entity->ammoComponent - 0x48;
    }
    else {
        return 0;
    }

    if (attackDataPtr != 0) {
        // Attack data at offset +0xF8 from the component
        *outAttackData = *(AttackData**)(attackDataPtr + 0xF8);
        return 1;
    }

    return 0;
}