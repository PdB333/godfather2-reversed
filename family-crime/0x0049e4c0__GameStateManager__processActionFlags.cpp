// FUNC_NAME: GameStateManager::processActionFlags
void GameStateManager::processActionFlags(uint* playerFlags, uint actionMask, int unused)
{
    uint flags;
    
    // Check if player flags pointer is valid and the action mask matches
    if (playerFlags != nullptr) {
        flags = *playerFlags;
        if ((flags & actionMask) != 0) {
            // Clamp minimum heat level to 25 (0x19)
            if (g_heatLevelMin < 0x19) {
                g_heatLevelMin = 0x19;
            }
            // Clamp maximum heat level to 25 (0x19)
            if (0x19 < g_heatLevelMax) {
                g_heatLevelMax = 0x19;
            }
            g_heatState = 7;      // +0x???? (global heat state)
            
            // Clamp minimum heat level to 24 (0x18)
            if (g_heatLevelMin < 0x18) {
                g_heatLevelMin = 0x18;
            }
            // Clamp maximum heat level to 24 (0x18)
            if (0x18 < g_heatLevelMax) {
                g_heatLevelMax = 0x18;
            }
            g_heatTimer1 = 0;     // +0x???? (reset timer)
            
            // Clamp minimum heat level to 15 (0x0F)
            if (g_heatLevelMin < 0xf) {
                g_heatLevelMin = 0xf;
            }
            // Clamp maximum heat level to 15 (0x0F)
            if (0xf < g_heatLevelMax) {
                g_heatLevelMax = 0xf;
            }
            g_heatTimer2 = 0;     // +0x???? (reset another timer)
            
            logAction(1, 5, 6);   // Debug log for heat event
            
            // If action mask includes additional flag (0x100)
            if ((flags & actionMask & 0x100) != 0) {
                logAction(1, 5, 6);   // Additional debug log
                
                // Clamp minimum heat level to 27 (0x1B)
                if (g_heatLevelMin < 0x1b) {
                    g_heatLevelMin = 0x1b;
                }
                // Clamp maximum heat level to 27 (0x1B)
                if (0x1a < g_heatLevelMax) {
                    g_heatLevelMax = 0x1b; // Note: originally used 0x1b despite condition
                }
                g_heatTimer3 = 0;   // +0x???? (reset third timer)
            }
        }
    }
    
    // Check for special action flags (0x10000 or 0x20000) and player flag bit 0
    if (((actionMask & 0x30000) != 0) && ((*playerFlags & 1) != 0)) {
        if ((actionMask & 0x10000) != 0) {
            // Immediate heat level cap at 22 (0x16)
            if (g_heatLevelMin < 0x16) {
                g_heatLevelMin = 0x16;
            }
            if (0x16 < g_heatLevelMax) {
                g_heatLevelMax = 0x16;
            }
            g_heatState2 = 0;      // +0x???? (secondary state)
            g_heatMode = 2;        // +0x???? (mode indicator)
            return;
        }
        if ((actionMask & 0x20000) != 0) {
            // Same heat level cap but different mode
            if (g_heatLevelMin < 0x16) {
                g_heatLevelMin = 0x16;
            }
            if (0x16 < g_heatLevelMax) {
                g_heatLevelMax = 0x16;
            }
            g_heatMode = 3;        // +0x???? (different mode)
        }
    }
    g_heatState2 = 0;             // +0x???? (reset secondary state)
}