// FUNC_NAME: CharacterObject::update
void __thiscall CharacterObject::update(void) {
    // Check a boolean flag at offset +0x190 (likely alive/dead or active/inactive)
    if (this->field_0x190 == 0) {
        // Set bit 1 (0x2) in flags at +0xB8 (e.g., "grounded" flag)
        this->flags |= 0x2;
    } else {
        // Set bit 0 (0x1) in flags (e.g., "inAir" flag)
        this->flags |= 0x1;
    }

    // Update sub‑systems (likely audio, animation, effects)
    updateAudio();      // FUN_0064f620
    updateAnimation();  // FUN_0064f5e0
    updateEffects();    // FUN_006504b0

    // Determine what the current mission/state should be
    int newMissionId;
    if (this->missionObjectivePtr == nullptr) { // +0x1FC: pointer to mission objective
        newMissionId = 0;
    } else {
        // Global singleton at DAT_0122344c, read its field at +0x58 (current mission ID)
        newMissionId = *(int*)(g_globalMissionData + 0x58);
    }

    // If the object's stored mission ID (+0x21C) differs from the global, update it
    if (this->currentMissionId != newMissionId) {
        setCurrentMission(newMissionId); // FUN_00452df0
    }
}