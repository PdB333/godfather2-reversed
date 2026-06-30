//FUNC_NAME: PlayerSM::update
// Address: 0x005b5970
// Role: Main state machine update for player/NPC, handles death, cutscene, and default states

void __thiscall PlayerSM::update(uint* stateFlags, Player* owner, uint extraData)
{
    char isPaused;
    uint stateId;

    // Check if game is paused (FUN_005a4140)
    isPaused = isGamePaused();
    if (isPaused == '\0') {
        // Not paused: perform standard update steps
        updatePrePhysics();          // FUN_005a3f20
        updateAnimation();           // FUN_005b4270
        updateSubComponent(owner + 0x220); // FUN_005b4540, offset +0x220 likely sub-component (e.g., AnimationController)
        // Call vtable function on sub-component (DAT_0119cb68)
        (*(void (**)(void*))DAT_0119cb68)(owner + 0x220);

        // Check death/dying state: bit 0x8000 set and state ID 0xD or 0x12
        stateId = *stateFlags & 0x7fff;
        if (((*stateFlags & 0x8000) != 0) && ((stateId == 0xd) || (stateId == 0x12))) {
            handleDeathStart();       // FUN_005a19c0
            updateDeathState(owner);  // FUN_005b37f0
            finalizeUpdate();         // FUN_005b4350
            return;
        }

        // Check if in cutscene (FUN_0059c950)
        isPaused = isInCutscene();
        if (isPaused != '\0') {
            handleCutsceneStart();    // FUN_0059c810
            updateCutscene(owner);    // FUN_005bbe00
            finalizeUpdate();         // FUN_005b4350
            return;
        }

        // Default state update
        updateDefaultState(owner, extraData); // FUN_005b4880
        finalizeUpdate();                     // FUN_005b4350
    }
    // If paused, do nothing
    return;
}