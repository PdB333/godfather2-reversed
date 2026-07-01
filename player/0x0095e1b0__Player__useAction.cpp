// FUNC_NAME: Player::useAction
bool __thiscall Player::useAction(int *this, int actionType, char *outFlag)
{
    int iVar1;
    int iVar2;
    uint uVar3;
    bool bVar4;

    bVar4 = false;
    switch(actionType) {
    case 0: // Primary weapon fire
        if (this[0] != 0) { // +0x00: m_primaryAmmo
            this[0] = this[0] - 1;
            return true;
        }
        break;
    case 1: // Secondary weapon fire (special effect)
        if (this[0x1c] != 0) { // +0x70: m_secondaryAmmo
            this[0x1c] = this[0x1c] - 1;
            *outFlag = 1;
            FUN_0095cf50(); // playActionEffect
            return true;
        }
        break;
    case 2: // Reload / special action
        if (this[2] != 0) { // +0x08: m_specialAmmo
            this[2] = this[2] - 1;
            iVar1 = FUN_0095c9f0(); // getRandomInt
            this[0xd] = iVar1; // +0x34: m_damageModifier
            return true;
        }
        break;
    case 3: // Apply damage modifier
        iVar2 = FUN_0095ca40(); // getBaseDamage
        iVar1 = this[0xd]; // +0x34: m_damageModifier
        uVar3 = FUN_0095c9f0(); // getRandomInt
        if (uVar3 <= (uint)(iVar1 - iVar2)) {
            this[0xd] = iVar1 - iVar2;
            return true;
        }
        break;
    case 4: // Action type 4
        if (this[9] != 0) { // +0x24: m_counter9
            this[9] = this[9] - 1;
            return true;
        }
        break;
    case 5: // Action type 5
        if (this[10] != 0) { // +0x28: m_counter10
            this[10] = this[10] - 1;
            return true;
        }
        break;
    case 6: // Action type 6
        if (this[5] != 0) { // +0x14: m_counter5
            this[5] = this[5] - 1;
            return true;
        }
        break;
    case 7: // Action type 7
        if (this[8] != 0) { // +0x20: m_counter8
            this[8] = this[8] - 1;
            return true;
        }
        break;
    case 8: // Toggle flag
        bVar4 = *(char *)((int)this + 0x7a) == '\0'; // +0x7a: m_flag
        *(undefined1 *)((int)this + 0x7a) = 1;
        break;
    case 9: // Action type 9
        if (this[7] != 0) { // +0x1c: m_counter7
            this[7] = this[7] - 1;
            return true;
        }
    }
    return bVar4;
}