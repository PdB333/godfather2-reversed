// FUNC_NAME: NPC::updateSpawnState
void NPC::updateSpawnState()
{
    int slotIndex = getSlotIndex();  // FUN_0090b0a0(this) : retrieves slot index for this NPC
    if (slotIndex != -1) {
        char isCutsceneActive = isCutscenePlaying();  // FUN_0090a8c0() : global cutscene flag
        if (isCutsceneActive == '\0') {
            // Not in a cutscene
            if ((byteFlags & 0x01) != 0) {  // +0x5f bit0 : needsSpawn flag
                stopAudioSequence(0);  // FUN_00791e00(0) : stop any pending audio
                int audioReady = isAudioSystemReady();  // FUN_00791300() : check audio system state
                if (audioReady != 0) {
                    int canSpawn = canSpawnGlobal(DAT_01131040);  // FUN_0043b870 : global spawnability check
                    if (canSpawn != 0) {
                        spawnObject();  // FUN_009b1970() : actually spawn the NPC
                        return;
                    }
                }
            }
        }
        else {
            // Cutscene active, mark slot for pending spawn
            setPendingSpawn(slotIndex, 1);  // FUN_0090b5d0(slotIndex,1) : defer spawn
        }
    }
}