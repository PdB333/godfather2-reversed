// FUNC_NAME: SimNpc::handleDeath
void __fastcall SimNpc::handleDeath(void)
{
    int iVar1;
    char *_Source;
    int *piVar2;
    bool bVar3;

    bVar3 = false;
    // check NPC state at offset +0xdc
    if (*(int *)(this + 0xdc) == 4) {
        // state = 4: pre-death or dying
        if (*(char *)(this + 0x220) == '\0') { // flag at +0x220 (maybe isAlive?)
            piVar2 = (int *)(this + 0x2ec); // vtable pointer for NPC type A
        } else {
            piVar2 = (int *)(this + 0x378); // vtable pointer for NPC type B
        }
        (**(code **)(*piVar2 + 0x8c))(); // call virtual onDeath
        FUN_00967e30();                  // notify manager or play effects
    }
    else if (*(int *)(this + 0xdc) == 7) {
        // state = 7: dead
        if (DAT_01223484 == 0) {
            iVar1 = 0;
        }
        else if (*(int *)(DAT_01223484 + 8) == 0) {
            iVar1 = **(int **)(this + 0x3c4); // dereference from +0x3c4
        }
        else {
            iVar1 = **(int **)(this + 0x338); // dereference from +0x338
        }
        bVar3 = *(int *)(iVar1 + 4) == 7; // compare sub-state to 7
        (**(code **)(*(int *)(this + 0x378) + 0x8c))(); // virtual onDeath from vtable at +0x378
        FUN_0096a1e0();                  // remove from simulation
        FUN_005a04a0("Destroy", 0, &DAT_00d8cdec, 0); // log destroy event
        FUN_00965ea0();                  // cleanup entity resources
        if (bVar3) {
            FUN_0096f9b0(_DAT_00d8dc88); // play death sound or final effect
        }
    }

    FUN_0095e840();                      // general cleanup (maybe animation, shadows)

    if (bVar3 != false) {
        FUN_00967e30();                  // secondary notification if state 7 sub-flag
    }

    _Source = (char *)FUN_00564830();    // get a string (name, ID, or log message)
    if (_Source == (char *)0x0) {
        *(undefined1 *)(this + 0x244) = 0; // clear name buffer at +0x244
    }
    else {
        _strncpy((char *)(this + 0x244), _Source, 0x30); // copy into name buffer (48 bytes)
        *(undefined1 *)(this + 0x273) = 0; // null-terminate at offset +0x273
    }

    *(bool *)(this + 500) = bVar3;      // store flag at +0x1f4
    *(undefined1 *)(this + 0x27c) = 1;  // set flag at +0x27c
    *(undefined4 *)(this + 0x1b0) = *(undefined4 *)(this + 0x6f8); // copy some ID/pointer
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) & 0xffefffff; // clear bit 20 in flags

    return;
}