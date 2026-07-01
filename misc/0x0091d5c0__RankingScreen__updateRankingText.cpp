// FUNC_NAME: RankingScreen::updateRankingText
void __thiscall RankingScreen::updateRankingText(int this) {
    int* offsetPtr = (int*)(this + 0xc0); // +0xc0: offset into ranking list
    int tickCount = FUN_009185a0(); // returns current game tick or frame count
    
    // Assert: current display index + offset should equal tickCount - 1
    if (*(int*)(this + 0xb4) + *offsetPtr != tickCount + -1) {
        FUN_00402050(&DAT_011301c0, 0); // potentially g_assertMsg, 0
    }
    
    // Number of items to update = MAX_ITEMS (0x13) minus current index
    int remaining = 0x13 - *(int*)(this + 0xb4);
    for (; remaining != 0; remaining--) {
        int gameState = *(int*)(DAT_01130044 + 0xb8); // global game structure, field +0xb8: current state
        int colorValue = DAT_00e54cd8; // some text color default
        
        // Chain of conditions to choose color based on gameState
        if (gameState != 10 && gameState != 11 && gameState != 12) {
            colorValue = DAT_00e54ce4;
            if (gameState != 25) {
                colorValue = DAT_00e54cf0;
                if (gameState != 13 && gameState != 14 && gameState != 15 && 
                    gameState != 16 && gameState != 17) {
                    if (gameState == 18 || gameState == 19 || gameState == 20 || 
                        gameState == 21 || gameState == 22 || gameState == 23 || gameState == 24) {
                        colorValue = DAT_00e54cfc;
                    } else {
                        colorValue = 0;
                    }
                }
            }
        }
        
        int currentIndex = *(int*)(this + 0xb4); // +0xb4: current display index
        // If no global flag set and (tickCount - 10) <= (offset + currentIndex), do timing update
        if (DAT_00e54d1c == '\0') {
            int tickNow = FUN_009185a0();
            if (tickNow - 10U <= (uint)(*offsetPtr + currentIndex)) {
                DAT_00e54d24 = DAT_00e54d28 + 1; // some timing variable
                DAT_00e54d20 = DAT_00e54d28 + 5;
                FUN_0091cd80(0, 0); // reset timing or update
            }
        }
        
        // Set the ranking text for this slot
        FUN_0095c5d0(offsetPtr, currentIndex, colorValue, 10);
    }
    
    // Final update: draw highlight bar or finalize
    FUN_00918940(*(int*)(this + 0xb4) + *offsetPtr, *(undefined4*)(this + 0xf0), 0x80);
    
    // Debug/profiling trace
    FUN_005a04a0("UpdateRankingText", 0, &DAT_00d8510c, 1, *(undefined4*)(this + 0xf0));
}