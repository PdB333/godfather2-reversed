// FUNC_NAME: GodfatherGameManager::handlePuzzleMode
void GodfatherGameManager::handlePuzzleMode() {
    char puzzleBuffer1[8];
    char puzzleBuffer2[8];
    char missionName[260];

    clearBuffer(0x40, puzzleBuffer2);
    clearBuffer(0x40, puzzleBuffer1);

    GodfatherGameManager* manager = getGameManager();
    if (manager != nullptr && (manager->state == 1 || manager->state == 4)) {
        if (!isTransitionAllowed()) {
            if (!isTransitionAllowed()) {
                getCurrentMissionName(missionName);
                bool isPuzzle = true;
                char* p1 = missionName;
                char* p2 = "Puzzle";
                int count = 7;
                while (count != 0 && isPuzzle) {
                    count--;
                    isPuzzle = (*p1 == *p2);
                    p1++;
                    p2++;
                }
                if (isPuzzle && manager->puzzleActive == '\0') {
                    manager->puzzleActive = 1;
                    manager->puzzleTimer = 0;
                    manager->state = 1;
                    startPuzzleMode(&manager->puzzleData);
                    initializePuzzle();
                    return;
                }
                // Not a puzzle mission or puzzle already active: handle as generic command
                manager->vtable->handleCommand(2, missionName);
                manager->state = 6;
                exitPuzzleMode();
            }
        }
    }
}