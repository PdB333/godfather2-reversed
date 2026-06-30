// FUNC_NAME: Entity::isActionPermitted

bool __fastcall Entity::isActionPermitted(int this) {
    // Check state at offset 0x338 (likely an enum for entity state)
    int state = *(int*)(this + 0x338);
    if (state == 0) {
        return false; // Null state, not permitted
    }
    
    // 0x48 is a specific state (e.g., dead, incapacitated, or cinematic)
    if (state != 0x48) {
        // Get global game manager (from FUN_007ff880)
        int gameManager = FUN_007ff880();
        
        // Condition: either in multiplayer (gameManager->+0xb74 != 0) OR
        // in single player with some flags (FUN_007f7c60 != 0 and FUN_00716d40 == 0)
        // AND player control is not active (FUN_0072d880 == 0)
        if ((((gameManager != 0) && (*(int*)(gameManager + 0xb74) != 0)) ||
             ((FUN_007f7c60() != 0) && (FUN_00716d40() == 0))) &&
            (FUN_0072d880() == 0)) {
            return true;
        }
        
        // Fallback: return true if gameManager exists and +0xb74 is set (multiplayer)
        if ((gameManager != 0) && (*(int*)(gameManager + 0xb74) != 0)) {
            return true;
        }
        
        return false;
    }
    
    return false; // State is 0x48 – action not permitted
}