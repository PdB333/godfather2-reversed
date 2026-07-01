// FUNC_NAME: FamilyManager::setActiveFamily
void __thiscall FamilyManager::setActiveFamily(int this, int family) // param_1 = this, param_2 = family pointer
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    FUN_004df650(); // likely some mutex/thread safety
    if (*(int *)(this + 0x160) != family) {
        if (*(int *)(this + 0x160) != 0) {
            // Deactivate current family
            FUN_006b5360(0, 0); // stop audio? (0,0)
            local_8 = *(undefined4 *)(*(int *)(this + 0x160) + 0x38); // family name hash?
            local_c = DAT_01130210; // some global string/ID
            local_4 = 0;
            FUN_00408a00(&local_c, 0); // send event/message
            FUN_006b2b50(0); // stop audio? (0)
        }
        *(int *)(this + 0x160) = family;
        if (*(char *)(this + 0x48) != '\0') {
            FUN_005a04a0("UpdateFamilyInfo", 0, &DAT_00d8f99c, 0); // debug log
        }
        if (family != 0) {
            // Activate new family
            FUN_00979700(family); // load family data
            FUN_00979ca0(family); // setup family UI
            FUN_006b5360(0, 1); // start audio? (0,1)
            FUN_00976c50(); // update family info display
            local_8 = *(undefined4 *)(family + 0x38); // family name hash
            local_c = DAT_01130340; // some global string/ID
            local_4 = 0;
            FUN_00408a00(&local_c, 0); // send event/message
            FUN_006b2b50(1); // start audio? (1)
            return;
        }
        FUN_00979700(0); // clear family data
    }
    return;
}