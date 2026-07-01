// FUNC_NAME: Player::updateMasterStateMachine
void __fastcall Player::updateMasterStateMachine(Player *this)
{
    bool bVar1;
    int iVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 local_c;
    undefined4 local_8;
    int local_4;

    // Check if game is paused or in cutscene -> skip
    if (isGamePaused() == false && isInCutscene() == true) {
        return;
    }

    bVar1 = isPlayerAlive();                     // returns bool
    if (bVar1 == false || *(int *)((char *)this + 0x2b4) != 0) { // +0x2b4: some state flag/disabled flag?
        bVar1 = isInGameplay();
        if (bVar1) {
            // Allocate new state info (size 0x38)
            iVar2 = allocateMemory(0x38);
            if (iVar2 == 0) {
                uVar4 = 0;
            }
            else {
                uVar4 = createStateInfo(this);    // this+0x2b4 used inside?
            }
            registerState(uVar4);                 // pass to some global state registry
        }
        // Check another component (e.g., audio/effects) at +0x3b0
        if (*(int *)((char *)this + 0x3b0) != 0) {
            updateAudioComponent();               // or something similar
        }

        // Build a hash-based lookup for player master state table
        uVar3 = DAT_012067e8;                     // global, probably some manager/table
        uVar4 = DAT_01205224;                     // another global
        uVar6 = 0;
        uVar7 = 0;
        local_c = 0;
        local_8 = 0xd42a2c49;                     // hash for "playerMasterStateTable"
        local_4 = (int)this;

        // Lookup the state table by string name
        uVar5 = lookupString("playerMasterStateTable", &local_c, 0, 0);
        // Retrieve state instance using hash 0xb08ae1f6
        uVar5 = getStateFromTable(0xb08ae1f6, uVar5, &local_c);
        // Apply/update the state
        updatePlayerState(uVar4, uVar3, uVar5, uVar7, uVar6);
    }
    return;
}