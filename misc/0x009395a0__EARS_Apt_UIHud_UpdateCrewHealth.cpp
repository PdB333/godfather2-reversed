// Xbox PDB: EARS_Apt_UIHud_UpdateCrewHealth
// FUNC_NAME: CrewLeaderComponent::updateCrewHealth
// Function address: 0x009395a0
// Role: Updates the health display value for a crew leader based on current/max health ratio.
// Offsets: this+0x48 = bool (alive/active flag), this+0x70 = maxHealth (from global manager), this+0x78 = computed health display value.
// External: DAT_00d5e288 = global health bar maximum (float)
// External: FUN_007351c0() = getCrewHealthManager() singleton getter
// External: FUN_005a04a0() = debug logging

void __thiscall CrewLeaderComponent::updateCrewHealth(void* thisPtr, int unusedParam, float currentHealth, float maxHealth)
{
    int managerPtr;
    float ratio;
    
    // Only update if the crew member is alive/active
    if (*(bool*)((char*)thisPtr + 0x48) != 0) {
        managerPtr = getCrewHealthManager();  // FUN_007351c0
        if (managerPtr != 0) {
            // Retrieve the max health value from the manager (offset +0xC4)
            managerPtr = getCrewHealthManager(); // Second call obtains the instance
            *(float*)((char*)thisPtr + 0x70) = *(float*)(managerPtr + 0xC4);
        }
        
        // Compute the health display value: ratio * global maximum
        ratio = (currentHealth / maxHealth) * DAT_00d5e288;
        if (ratio > 0.0f) {
            if (ratio > DAT_00d5e288) {
                ratio = DAT_00d5e288;
            }
        } else {
            ratio = 0.0f;
        }
        *(float*)((char*)thisPtr + 0x78) = ratio;
        
        // Debug logging (string tag, unused params)
        debugLog("UpdateCrewHealth", 0, &DAT_00d8a64c, 0);   // FUN_005a04a0
    }
}