// FUNC_NAME: PlayerSM::handleActionableInteraction
// Address: 0x007d8e50
// Simulates logic for handling player actionable interactions (e.g., entering vehicles, using objects)
uint8_t __fastcall PlayerSM::handleActionableInteraction(PlayerSM* this) {
    uint8_t result = 0;

    // Check if interaction flow is enabled (flag at +0x74->+4 bit 1)
    uint32_t* flagsPtr = *(uint32_t**)((uint8_t*)this + 0x74);
    if (flagsPtr != nullptr && (*flagsPtr & 2) != 0) {
        SimManager* simMgr = SimManager::getInstance();                 // FUN_007ab160
        if (simMgr != nullptr && (*(uint32_t*)((uint8_t*)simMgr + 4) & 4) != 0) {
            // Check if game is paused or mission active (global check)
            if (DAT_0112a838 == 0 || *(uint32_t*)(DAT_0112a838 + 0x5c) == 0) {
                Player* player = Player::getCurrentPlayer();             // FUN_007ab1f0
                if (player != nullptr) {
                    if (!InputManager::isInputBlocked()) {               // FUN_00481620
                        // Set interaction flag at +0x58->+0x23c8
                        uint8_t* interactFlag = *(uint8_t**)((uint8_t*)this + 0x58) + 0x23c8;
                        if (*interactFlag == 0) {
                            *interactFlag = 1;
                            result = 1;
                        }
                    } else {
                        if (PlayerSM::isInCutscene()) {                  // FUN_007013c0
                            // Handle cutscene case
                            uint32_t* somePtr = *(uint32_t**)((uint8_t*)player + 0x328);
                            if (somePtr == nullptr) {
                                // Send event 0x14 (20) to notify cutscene skip
                                PlayerSM::sendNotifyEvent(0x14, CONCAT44(1, local_1c_rest), 0, local_c, local_4); // FUN_0079fb90
                                return 1;
                            } else {
                                if (!PlayerSM::hasAbility(0x34)) {       // FUN_00690210
                                    uint32_t playerData = PlayerDataManager::get(0x39); // FUN_00798f50
                                    if (PlayerSM::isDataValid(playerData) && // FUN_0079e920
                                        !PlayerSM::isInteractionBlocked()) // FUN_007012f0
                                    {
                                        if (PlayerSM::startInteraction()) // FUN_00701340
                                            goto sendCutsceneSkip;       // LAB_007d8f14
                                    }
                                }
                            }
                        } else {
                            // Not in cutscene; try to start an action
                            if (!InputManager::isInputBlocked()) {       // FUN_00481620
                                if (PlayerSM::isActionAllowed()) {       // FUN_00701820
                                    Action* action = PlayerSM::getCurrentAction(); // FUN_007057c0
                                    if (action != nullptr) {
                                        ActionManager::executeAction(action); // FUN_00690820
                                        if (CutsceneManager::isPlaying()) { // FUN_00481660
                                            Animator::startAction(action + 0x58); // FUN_004a8ec0
                                            PlayerSM::sendNotifyEvent(3, CONCAT44(5, ...), ...); // FUN_0079fb90
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}