// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_FormatRivalFamilyMemeberStatusString
// FUNC_NAME: FamilyMember::updateStatusText
void __thiscall FamilyMember::updateStatusText(int this, int statusInfo)
{
    char cVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int *piVar6;
    char *pcVar8;
    char *local_10;
    int local_c;
    int local_8;
    int local_4;

    iVar2 = FUN_00791540(); // GameManager::getInstance?
    iVar3 = FUN_008c1250(statusInfo); // GetFamilyMemberStatusInfo
    iVar4 = FUN_00790d90(); // GetPlayerCrew?
    iVar5 = FUN_006b0ee0(iVar4); // GetPlayerCrewLeader?
    cVar1 = FUN_008fda60(); // IsPlayerAtHangout?
    if (iVar3 == 0) {
        return;
    }
    iVar3 = *(int *)(iVar3 + 4); // statusType
    local_10 = (char *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    if (iVar3 == 5) {
        pcVar8 = "{$pause_family_tree_status_hospital}";
    }
    else if (iVar3 == 6) {
        pcVar8 = "{$pause_family_tree_status_jail}";
    }
    else if (iVar3 == 7) {
        pcVar8 = "{$pause_family_tree_status_dead}";
    }
    else if (iVar3 == 1) {
        if (cVar1 == '\0') goto LAB_0097fee4;
        pcVar8 = "{$pause_family_tree_status_at_hangout}";
    }
    else if ((cVar1 == '\0') || (iVar5 == 0)) {
LAB_0097fee4:
        pcVar8 = "{$pause_family_tree_status_alive}";
    }
    else {
        if (iVar3 == 2) {
            if (*(int *)(iVar5 + 0x40) == *(int *)(iVar2 + 0x54)) { // compare crewID
                piVar6 = (int *)FUN_006b2160(); // GetCurrentLocationName?
                if (*piVar6 == 0) {
                    piVar6 = (int *)&DAT_0120546e; // empty string
                }
                FUN_004d4ad0(&local_10, "{v:%s}{$pause_family_tree_status_defending}", *piVar6);
            }
            else {
                piVar6 = (int *)FUN_006b2160();
                if (*piVar6 == 0) {
                    piVar6 = (int *)&DAT_0120546e;
                }
                FUN_004d4ad0(&local_10, "{v:%s}{$pause_family_tree_status_attacking}", *piVar6);
            }
            goto LAB_0097fef2;
        }
        if (iVar3 == 3) {
            cVar1 = FUN_008fe3d0(); // IsAssignedToHangout?
            if (cVar1 == '\0') {
                if (*(int *)(iVar5 + 0x40) == *(int *)(iVar2 + 0x54)) {
                    piVar6 = (int *)FUN_006b2160();
                    if (*piVar6 == 0) {
                        piVar6 = (int *)&DAT_0120546e;
                    }
                    FUN_004d4ad0(&local_10, "{v:%s}{$pause_family_tree_status_guarding}", *piVar6);
                    goto LAB_0097fef2;
                }
                pcVar8 = "{$pause_family_tree_status_heading_to_hangout}";
            }
            else {
                pcVar8 = "{$pause_family_tree_status_at_hangout}";
            }
        }
        else {
            if (iVar3 == 4) {
                piVar6 = (int *)FUN_006b2160();
                if (*piVar6 == 0) {
                    piVar6 = (int *)&DAT_0120546e;
                }
                FUN_004d4ad0(&local_10, "{v:%s}{$pause_family_tree_status_moving}", *piVar6);
                goto LAB_0097fef2;
            }
            pcVar8 = "{$pause_family_tree_status_unknown}";
        }
    }
    FUN_004d3d90(pcVar8); // SetStatusText
LAB_0097fef2:
    if (local_10 == (char *)0x0) {
        piVar6 = (int *)&DAT_0120546e;
    } else {
        piVar6 = (int *)local_10;
    }
    FUN_005c4660(*(int *)(this + 0xfc), piVar6, 0x100, 0); // SetTextField(this->uiTextField, text, 256, 0)
    if (local_10 != (char *)0x0) {
        local_4(local_10); // free dynamical string
    }
    return;
}