// FUNC_NAME: NPCManager::setMaxNPCs
void NPCManager::setMaxNPCs(int param_2) {
    int maxNPCs = 0x78; // 120 - maximum number of NPCs
    FUN_004eba90(this, param_2, &maxNPCs, 1);
}