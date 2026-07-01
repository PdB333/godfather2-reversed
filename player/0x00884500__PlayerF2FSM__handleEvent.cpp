// FUNC_NAME: PlayerF2FSM::handleEvent
int __thiscall PlayerF2FSM::handleEvent(unsigned int playerF2FSM *this, int param_2, int param_3, int param_4, int eventID, int param_6)
{
    char cVar1;
    int iVar2;
    int iVar3;
    float *pfVar4;
    int *piVar5;
    undefined4 unaff_EBX;
    undefined4 uStack_24;
    undefined4 uStack_20;
    float afStack_1c [6];

    uStack_20._3_1_ = 1; // likely default return true

    switch(eventID + -10) {
    case 0: // eventID == 10
        // check if component pointer (m_pComponent at +0x14) is non-zero and not 0x48? Actually offset 0x48 from component start?
        if ((this->m_pComponent != 0) && (this->m_pComponent != (Component*)0x48)) {
            if (this->m_pComponent == 0) {
                iVar2 = 0;
            } else {
                iVar2 = (int)this->m_pComponent + -0x48;
            }
            if ((*(uint *)(iVar2 + 0xc88) >> 2 & 1) != 0) {
                this->m_field_1e = DAT_00d76f60; // some global value
                return 1;
            }
        }
        break;
    case 1: // eventID == 11
        // call FUN_00883e00 with 0 and a value derived from some field
        FUN_00883e00(0, CONCAT31((uint3)(*(uint *)(this->m_pPlayer + 0x1b94) >> 0x1b), (char)(*(uint *)(this->m_pPlayer + 0x1b94) >> 0x13)) & 0xffffff01);
        return uStack_20._3_1_;
    case 2: // eventID == 12
        this->m_flags = this->m_flags | 1;
        FUN_00883e00(1, CONCAT31((uint3)(*(uint *)(this->m_pPlayer + 0x1b94) >> 0x1b), (char)(*(uint *)(this->m_pPlayer + 0x1b94) >> 0x13)) & 0xffffff01);
        FUN_00471610(); // presumably getPlayerTransform or something
        FUN_00883100(); // some update
        return uStack_20._3_1_;
    case 3: // eventID == 13
        if ((((uint)this->m_flags >> 2 & 1) != 0) && (this->m_pPlayer != 0)) {
            FUN_0072d290(); // some logic
            return uStack_20._3_1_;
        }
        break;
    case 4: // eventID == 14
        FUN_00884110(); // probably audio trigger
        return uStack_20._3_1_;
    case 5: // eventID == 15
        if (((uint)this->m_flags >> 1 & 1) != 0) {
            iVar2 = (int)this->m_pPlayer;
            if (this->m_pComponent == 0) {
                piVar5 = (int *)0x0;
            } else {
                piVar5 = (int *)(this->m_pComponent + -0x48);
            }
            afStack_1c[0] = (float)(**(code **)(*piVar5 + 0x1e4))(); // virtual call
            if (afStack_1c[0] == 0.0) {
                afStack_1c[1] = 0.0;
                if (this->m_pComponent == 0) {
                    piVar5 = (int *)0x0;
                } else {
                    piVar5 = (int *)(this->m_pComponent + -0x48);
                }
                (**(code **)(*piVar5 + 0x1cc))(afStack_1c); // virtual call
                if (this->m_pComponent == 0) {
                    piVar5 = (int *)0x0;
                } else {
                    piVar5 = (int *)(this->m_pComponent + -0x48);
                }
                iVar3 = (**(code **)(*piVar5 + 500))(&uStack_20); // 500 = 0x1f4? virtual call
                if ((iVar3 != 0) && (iVar3 = FUN_006bc8d0(iVar3, 0x369ac561), iVar3 != 0)) { // type check
                    FUN_00543160(iVar2, iVar3); // attach to something?
                    if (this->m_pComponent != 0) {
                        FUN_008755f0(iVar2);
                        return uStack_24._3_1_;
                    }
                    FUN_008755f0(iVar2);
                    return uStack_24._3_1_;
                }
            }
        }
        break;
    case 6: // eventID == 16
        iVar2 = (int)this->m_pPlayer;
        if (((iVar2 != 0) && (this->m_pComponent != 0)) && (this->m_pComponent != (Component*)0x48)) {
            this->m_field_1b = *(int *)(iVar2 + 0x85c); // some player field
            this->m_field_19 = *(int *)(iVar2 + 0x860);
            this->m_field_1a = *(int *)(iVar2 + 0x864);
            if (this->m_pComponent == 0) {
                piVar5 = (int *)0x0;
            } else {
                piVar5 = (int *)(this->m_pComponent + -0x48);
            }
            (**(code **)(*piVar5 + 0x1f0))(&this->m_field_19, &this->m_field_17); // virtual call
            iVar2 = FUN_00471610(); // get something
            iVar3 = FUN_00471610(); // get something else
            uStack_24 = *(float *)(iVar3 + 0x30) - *(float *)(iVar2 + 0x30);
            uStack_20 = *(float *)(iVar3 + 0x34) - *(float *)(iVar2 + 0x34);
            afStack_1c[0] = *(float *)(iVar3 + 0x38) - *(float *)(iVar2 + 0x38);
            FUN_0043a210(&uStack_24, &uStack_24); // normalize direction
            pfVar4 = (float *)FUN_00471610(); // get another transform?
            iVar2 = FUN_00471610();
            iVar3 = FUN_00471610();
            uStack_24 = *(float *)(iVar2 + 4) * uStack_20 + *pfVar4 * uStack_24 + *(float *)(iVar3 + 8) * afStack_1c[0];
            if (((_DAT_00d577a0 < uStack_24) && (cVar1 = FUN_008754b0(&this->m_field_19), cVar1 != '\0')) ||
               ((uStack_24 < 0.0 && (cVar1 = FUN_008754b0(&this->m_field_19), cVar1 == '\0')))) {
                if (this->m_pComponent == 0) {
                    piVar5 = (int *)0x0;
                } else {
                    piVar5 = (int *)(this->m_pComponent + -0x48);
                }
                (**(code **)(*piVar5 + 0x1c8))(&this->m_field_17, &this->m_field_17); // virtual call
            }
            cVar1 = FUN_008754b0(&this->m_field_17);
            this->m_field_1c = 2 - (uint)(cVar1 != '\0');
            return (char)((uint)unaff_EBX >> 0x18);
        }
        break;
    case 7: // eventID == 17
        iVar2 = this->m_field_1e;
        (**(code **)(*this + 0x2c))(0x46f5c7b4, 1, 0, 0, iVar2, 0x3f800000); // some call with flags/color? Might be DebugDraw?
        return (char)((uint)iVar2 >> 0x18);
    case 8: // eventID == 18
        FUN_00884290();
        return uStack_20._3_1_;
    case 9: // eventID == 19
        (**(code **)(*(int *)this->m_pPlayer + 0x7c))(); // virtual call on player
        this->m_flags = this->m_flags & 0xfffffff7; // clear bit 3
        return uStack_20._3_1_;
    case 10: // eventID == 20
        FUN_00883240(&this->m_transform1, &this->m_transform2, (float)this->m_field_c / (DAT_00d76f64 / (float)this->m_field_1e));
        return uStack_20._3_1_;
    case 0xb: // eventID == 21
        FUN_00883240(&this->m_transform2, &this->m_transform3, (float)this->m_field_c / (_DAT_00d5780c / (float)this->m_field_1e));
        return uStack_20._3_1_;
    default:
        uStack_20._3_1_ = FUN_004ac700(param_2, param_3, param_4, eventID, param_6); // base class handler
    }
    return uStack_20._3_1_;
}