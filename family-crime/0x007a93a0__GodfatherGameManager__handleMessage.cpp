// FUNC_NAME: GodfatherGameManager::handleMessage
// Address: 0x007a93a0
// Role: Processes incoming messages/events for the Godfather game manager, dispatching based on message ID.

// Known message IDs (likely string hashes or integer IDs):
enum GameMessageID {
    kMsgSaveGame             = 0x0112b2b4, // DAT_0112b2b4
    kMsgResumeGame           = 0x0112b534, // DAT_0112b534
    kMsgPauseGame            = 0x0112b2a4, // DAT_0112b2a4
    kMsgShowMap              = 0x0112b41c, // DAT_0112b41c
    kMsgHideMap              = 0x0112b544, // DAT_0112b544
    kMsgMapClosed            = 0x0112b56c, // DAT_0112b56c
    kMsgMapOpened            = 0x0112b39c, // DAT_0112b39c
    kMsgStopMap              = 0x01129aa0, // DAT_01129aa0
    kMsgStartMap             = 0x01129a98, // DAT_01129a98
    kMsgMobFaceRestore       = 0x01206760, // DAT_01206760
    kMsgMobFaceReload        = 0x0113109c, // DAT_0113109c
    kMsgMobFaceSave          = 0x01206778, // DAT_01206778
    kMsgMobFaceSaveRestored  = 0x01206780, // DAT_01206780
    kMsgSetObjectivePrime    = 0x0112b2ac, // DAT_0112b2ac
    kMsgSetObjectiveOther    = 0x0112b2bc, // DAT_0112b2bc
    kMsgRespawnPlayer        = 0x0112b354, // DAT_0112b354
    kMsgPlayerDied           = 0x0112b514, // DAT_0112b514
    kMsgClearGameOver        = 0x0112b35c, // DAT_0112b35c
    kMsgPlaySound            = 0x0112b55c, // DAT_0112b55c
    kMsgEnterBuilding        = 0x0112b214, // DAT_0112b214
    kMsgExitBuilding         = 0x0112f4b4, // DAT_0112f4b4
    kMsgCameraState0         = 0x0112b364, // DAT_0112b364
    kMsgCameraState1         = 0x0112b6f4, // DAT_0112b6f4
    kMsgCameraState2         = 0x0112b34c, // DAT_0112b34c
    kMsgCameraState3         = 0x0112b704, // DAT_0112b704
    kMsgCameraState4         = 0x0112b784, // DAT_0112b784
    kMsgCameraState5         = 0x0112b2c4, // DAT_0112b2c4
    kMsgCameraState6         = 0x0112b804, // DAT_0112b804
    kMsgPlayCutscene         = 0x0120e978, // DAT_0120e978
    kMsgStopCutscene         = 0x0120ea74, // DAT_0120ea74
    kMsgKeyboardAction       = 0x0112dd00, // DAT_0112dd00
    kMsgWarModeEnd           = 0x01206970, // DAT_01206970
    kMsgPauseDelayed         = 0x0112b524, // DAT_0112b524
    kMsgShowHint             = 0x0112b90c, // DAT_0112b90c
    kMsgSetGameSpeed         = 0x0112a5e0, // DAT_0112a5e0
    kMsgStartTutorial        = 0x0112b20c, // DAT_0112b20c
    kMsgStopTutorial         = 0x0112b66c, // DAT_0112b66c
    kMsgShowMissionComplete  = 0x0112b914, // DAT_0112b914
    kMsgMusicIntensityLow    = 0x0112b374, // DAT_0112b374
    kMsgMusicIntensityHigh   = 0x0112b51c, // DAT_0112b51c
    // Additional messages used later:
    kMsgUnknown1             = 0x01131028, // DAT_01131028
    kMsgUnknown2             = 0x01131020, // DAT_01131020
    kMsgUnknown3             = 0x012067dc, // DAT_012067dc
};

// Forward declarations of helper functions (invented names based on pattern):
extern bool isInFrontend();
extern bool isUIVisible();
extern bool isGameActive();
extern void showMap();
extern void hideMap();
extern void startGameUpdate();      // called when unpausing
extern void setGameSpeed(int speed); // 0 or 1
extern int getLocalPlayerID();
extern void setPlayerFocus(int playerId);
extern void updatePlayerCamera();
extern void showTooltip();
extern void setGameState(int state); // 1 or 2
extern void setObjectiveVisibility(bool visible); // (?)
extern void setObjectiveActive(bool active);
extern void showMissionCompleteScreen(bool show);
extern void startTutorial(int param); // 0x10 or 0x20
extern void stopTutorial(int param);
extern void playSound(int soundId);
extern void playCutscene();
extern void stopCutscene();
extern void onPlayerDied();
extern void onRespawnPlayer();
extern void clearGameOverFlag();
extern void enterBuilding(int param); // param_2[1]?
extern void exitBuilding();
extern void onPauseDelayed();
extern void showHint();
extern void setCameraState(int state);
extern void onMobFaceRestored();
extern void onMobFaceSave(bool save);
extern void onKeyboardAction(int key, int action);
extern void postMessage(int msgId, int param, bool lowPriority); // FUN_004035f0 pattern
extern bool isMusicIntensityLow();
extern bool isMusicIntensityHigh();
extern void setMusicIntensity(int val);
extern void fadeOutMusic();
extern void fadeInMusic();
extern void * getGameManager(); // returns this base?

// Additional internal functions:
extern void * FUN_007f63e0(int);
extern int FUN_00691810();
extern void * FUN_006bea40(int);
extern void FUN_0079ce30();
extern int FUN_0079ae70(int, int);
extern int FUN_00625050(int, int);
extern int FUN_007e24b0();
extern void * FUN_006fbc40(int, int);
extern void FUN_007f96a0(int, int, void *, int);
extern void FUN_006fbc70();
extern int FUN_006ad7f0(int);
extern int FUN_00713340(int, int);
extern bool FUN_00798eb0(int);
extern void FUN_008c3bc0(int);
extern void FUN_00420a10(int*, char*);
extern void FUN_004086d0(int*);
extern bool FUN_008a4380();
extern int FUN_009bca20(int);
extern void FUN_004d3e20(void*);
extern void FUN_004d3f10(int, int, int);
extern void FUN_009bf2f0(int, int);
extern void FUN_00481620();
extern void FUN_007a8ca0();
extern void FUN_00808540(int*);
extern void FUN_004446c0(int, int);
extern void FUN_0079d880();
extern void FUN_00707680(int);
extern void FUN_00709440();
extern void FUN_00444660(int, int);
extern int FUN_007fd760();
extern void FUN_006901b0(int);
extern void FUN_0079dcc0(int);
extern void FUN_00799c40();
extern void FUN_0079e5e0();
extern void FUN_0079e6a0();
extern void FUN_00408a00(int*, int);
extern void FUN_007cdef0();
extern void FUN_007a6920();
extern void FUN_007a8ff0(void*);
extern void FUN_007a5fe0(bool);
extern bool FUN_00690210(int);
extern void FUN_006a87f0(int);
extern void FUN_006901e0(int);

void __thiscall GodfatherGameManager::handleMessage(int *msgHeader) {
    int msgId = *msgHeader;
    void *baseThis = (char*)this - 0x3c; // Adjust to base object (vtable at base)
    void **vtable = *(void***)baseThis;  // vtable pointer at base object

    // Big switch on message ID
    if (msgId == kMsgSaveGame) {
        // Save game request
        ((void (__thiscall*)(void*, int, int))vtable[0x234 / 4])(baseThis, 4, 1);
        FUN_007f63e0(1); // likely save function
    }
    else if (msgId == kMsgResumeGame) {
        // Resume from pause or frontend
        bool canResume = isInFrontend();
        if (!canResume || (canResume = isUIVisible(), canResume == false)) {
            // Actually resume
            showMap();  // likely show map or HUD
            if (isGameActive()) {
                setGameSpeed(0); // Set game speed to normal
            }
            // Call vtable function at offset 0x304 (maybe start update)
            ((void (__thiscall*)(void*))vtable[0x304 / 4])(baseThis);
            int playerId = getLocalPlayerID();
            setPlayerFocus(playerId);
            updatePlayerCamera();
            if (isGameActive() && (*(int*)(0x0112b9b4 + 0x40) != 0)) { // global check
                showTooltip();
            }
        }
    }
    else if (msgId == kMsgPauseGame) {
        hideMap();
        if (isGameActive()) {
            setGameSpeed(1); // pause game
        }
        // Call vtable function at offset 0x308
        ((void (__thiscall*)(void*))vtable[0x308 / 4])(baseThis);
        FUN_007a07a0(); // likely stop update or pause
    }
    else if (msgId == kMsgShowMap) {
        setGameState(2); // show map state
    }
    else if (msgId == kMsgHideMap) {
        setGameState(1); // hide map state
    }
    else if (msgId == kMsgMapClosed) {
        hideMap();
    }
    else if (msgId == kMsgMapOpened) {
        showMap();
    }
    else if (msgId == kMsgStopMap) {
        *(char*)0x00e50fb5 = 0; // global flag
        hideMap();
    }
    else if (msgId == kMsgStartMap) {
        showMap();
        *(char*)0x00e50fb5 = 1; // global flag
    }
    else if (msgId == kMsgMobFaceRestore || msgId == kMsgMobFaceReload) {
        // Mob face related
        if (msgId == kMsgMobFaceRestore) {
            if (*(char*)(0x011298a0 + 0x88) == '\0') {
                // If not already restored, set up message
                FUN_00420a10(&kMsgMobFaceReload, "iMsgMobFaceSaveRestored");
            }
            else {
                // Already restored
                FUN_004086d0(&kMsgMobFaceReload);
                if (!FUN_008a4380()) {
                    int result = FUN_009bca20(-1);
                    // Prepare a local stack object (likely a scope guard)
                    int local_10 = 0;
                    int local_c = 0;
                    uint local_8 = 0;
                    code *local_4 = (code*)0x0; // function pointer
                    if (result != 0) {
                        FUN_004d3e20((void*)((char*)this + 0x274));
                        FUN_004d3f10(0, 0, 0);
                    }
                    setGameState(1); // hide map?
                    if (result != 0) {
                        FUN_004d3e20(&local_10);
                        FUN_009bf2f0(-1, (int)baseThis);
                    }
                    if (local_10 != 0) {
                        local_4(local_10); // call destructor?
                    }
                }
                else {
                    bool isInGame = FUN_00481620(); // isInGame?
                    if (isInGame) {
                        FUN_007a8ca0(); // some UI update
                    }
                }
            }
        }
        if (*msgHeader == kMsgMobFaceRestore) {
            // Post message to restore
            int param = *(int*)((char*)this + 0x28dc); // something from object
            // postMessage with ID 2 and param
            FUN_004035f0(param, 2, (uint)(this != (void*)0x3c) ? (int)this : 0);
        }
    }
    else if (msgId == kMsgMobFaceSave) {
        // Save mob face
        ((void (__thiscall*)(void*))vtable[0x128 / 4])(baseThis);
        int param = *(int*)((char*)this + 0x28dc);
        // fall through to post
    }
    else if (msgId == kMsgMobFaceSaveRestored) {
        // Already handled above fallthrough
        int param = *(int*)((char*)this + 0x28dc);
        // postMessage with ID 0x1FF and param
    }
    else {
        // Check remaining messages
        if (msgId == kMsgSetObjectivePrime) {
            setObjectiveVisibility(1);
        }
        else if (msgId == kMsgSetObjectiveOther) {
            setObjectiveActive(1);
        }
        else if (msgId == *(int*)((char*)this + 0x28b4)) { // some stored ID
            setObjectiveVisibility(1);
        }
        else if (msgId == *(int*)((char*)this + 0x28c4)) {
            setObjectiveActive(1);
        }
        else if (msgId == *(int*)((char*)this + 0x28bc)) {
            setObjectiveVisibility(0);
        }
        else if (msgId == kMsgUnknown1) {
            int result = FUN_00691810();
            int secondParam = *(int*)(msgHeader[1] + 4);
            if ((secondParam != 0) && (secondParam - 0x48 != 0)) { // -0x48 adjustment
                if (result != 0) {
                    // Check some flags and call
                    if (((*(uint*)((char*)this + 0x8a4) >> 10 & 1) != 0) &&
                        (*(char*)(result + 0x1a8) == '\x01')) {
                        void *somePtr = FUN_006bea40(secondParam - 0x48);
                        if (somePtr != 0) {
                            float health = (**(float**)(*(int*)somePtr + 0x28))(somePtr); // get health?
                            if (health > 0.0f) {
                                int state = (**(int**)(*(int*)somePtr + 0x34))(somePtr);
                                if (*(int*)(state + 0x30) == 2) { // state check
                                    FUN_0079ce30(); // some action
                                }
                            }
                        }
                    }
                }
                int check = FUN_0079ae70(secondParam - 0x48, 0xa7039c8); // hash?
                if ((check != 0) && (FUN_00625050(0xc4bc3ce7, 0) != 0) && (FUN_007e24b0() != 0)) {
                    int uVar7 = 0;
                    void *uVar3 = FUN_006fbc40(0, 0);
                    FUN_007f96a0(0, 0x40, uVar3, uVar7);
                    FUN_006fbc70();
                    int *piVar4 = (int*)FUN_006ad7f0((int)baseThis);
                    (**(void (__thiscall**)(int))(*(int*)piVar4 + 0x24))(0); // call vfunc
                }
            }
        }
        else if (msgId == kMsgUnknown2) {
            int target = *(int*)(msgHeader[1] + 4);
            if (target != 0 && target != 0x48) {
                target = target - 0x48;
                int check = FUN_00713340(target, 0x369ac561);
                if (check != 0 && FUN_00798eb0(check)) {
                    int uVar7 = 0;
                    void *uVar3 = FUN_006fbc40(0, 0);
                    FUN_007f96a0(0, 0x40, uVar3, uVar7);
                    FUN_006fbc70();
                }
            }
        }
        else if (msgId == kMsgUnknown3) {
            int result = FUN_006ebfd0();
            if (result != 0) {
                FUN_008c3bc0((int)baseThis);
            }
        }
        else {
            // Default handling: post message with certain ID?
            int param = *(int*)((char*)this + 0x28dc); // +0x28dc
            FUN_004035f0(param, 0x1ff, (uint)(this != (void*)0x3c) ? (int)this : 0);
            *(int*)((char*)this + 0x28dc) = 0;
        }
    }

LAB_007a98be: // Common exit path after processing
    FUN_00808540(msgHeader); // possibly free message or cleanup
    int newMsgId = *msgHeader; // re-read msg ID after cleanup?

    // Additional dispatch based on the same message id? Actually it's after cleanup, separate
    if (newMsgId == kMsgSetObjectivePrime) {
        FUN_004446c0(*(int*)((char*)this + 0x245c), *(int*)(*(int*)(msgHeader[1] + 4) + 4));
        return;
    }
    if (newMsgId == kMsgSetObjectiveOther) {
        FUN_0079d880();
        return;
    }
    if (newMsgId == kMsgRespawnPlayer) {
        int vehicle = *(int*)((char*)this + 0x710); // +0x710 vehicle pointer
        if (vehicle != 0 && vehicle != 0x48) {
            if ((*(uint*)((char*)this + 0x8a4) >> 10 & 1) != 0) { // flag
                if ((*(uint*)(vehicle + 0x188) >> 3 & 1) != 0) { // vehicle flag
                    FUN_00707680(0x00e448d8); // respawn with params
                    FUN_00709440();
                    return;
                }
            }
        }
    }
    else if (newMsgId == kMsgPlayerDied) {
        int vehicle = *(int*)((char*)this + 0x710);
        if (vehicle != 0 && vehicle != 0x48) {
            int ptr = (vehicle == 0) ? 0 : vehicle - 0x48;
            if (*(char*)(ptr + 0x1a8) == '\x01') {
                // Player is in vehicle (sitting)
                int seat = (vehicle == 0) ? 0 : vehicle - 0x48;
                if (*(char*)(seat + 0x1ad) != 22 && *(char*)(seat + 0x1ad) != 33) {
                    return; // not in correct seat?
                }
                ((void (__thiscall*)(void*))vtable[0x264 / 4])(baseThis);
                FUN_00444660(*(int*)((char*)this + 0x245c), *(int*)((char*)this + 0x2ab0));
                return;
            }
        }
    }
    else if (newMsgId == kMsgClearGameOver) {
        int result = FUN_007fd760();
        if (result != 0) {
            *(char*)(result + 0x1029) = 0; // cleared flag
            return;
        }
    }
    else if (newMsgId == kMsgPlaySound) {
        FUN_006901b0(0x2e); // play sound ID 0x2E
        return;
    }
    else if (newMsgId == kMsgEnterBuilding) {
        bool isInGame = FUN_00481620();
        if (isInGame) {
            bool uiVisible = isUIVisible();
            if (!uiVisible) {
                FUN_0079dcc0(0x3f); // some display?
                setObjectiveVisibility(0);
                setObjectiveActive(0);
            }
            FUN_00799c40();
            *(char*)((char*)this + 0x2020) = 1; // set flag
            return;
        }
    }
    else if (newMsgId == kMsgExitBuilding) {
        setObjectiveVisibility(0);
        return;
    }
    else if (newMsgId == kMsgCameraState0) {
        *(int*)((char*)this + 0x30e4) = 0;
        return;
    }
    else if (newMsgId == kMsgCameraState1) {
        *(int*)((char*)this + 0x30e4) = 1;
        return;
    }
    else if (newMsgId == kMsgCameraState2) {
        *(int*)((char*)this + 0x30e4) = 2;
        return;
    }
    else if (newMsgId == kMsgCameraState3) {
        *(int*)((char*)this + 0x30e4) = 3;
        return;
    }
    else if (newMsgId == kMsgCameraState4) {
        *(int*)((char*)this + 0x30e4) = 4;
        return;
    }
    else if (newMsgId == kMsgCameraState5) {
        *(int*)((char*)this + 0x30e4) = 5;
        return;
    }
    else if (newMsgId == kMsgCameraState6) {
        *(int*)((char*)this + 0x30e4) = 6;
        return;
    }
    else if (newMsgId == kMsgPlayCutscene) {
        FUN_0079e5e0(); // play cutscene
        return;
    }
    else if (newMsgId == kMsgStopCutscene) {
        FUN_0079e6a0(); // stop cutscene
        return;
    }
    else if (newMsgId == kMsgKeyboardAction) {
        if (*(char*)((char*)this + 0x1b50) != 4) { // state check
            // Set up a message buffer?
            int *buffer = (int*)(msgHeader[1]); // param_2[1] is data
            int msgType = 0x0112dd08; // some constant
            uint flags = // ... 
            FUN_00408a00(&msgType, 0); // post keyboard action
            return;
        }
    }
    else if (newMsgId != 0x01206970) { // kMsgWarModeEnd
        if (newMsgId == kMsgPauseDelayed) {
            if (this != (void*)0xfffffc90 && FUN_00625050(0xb47bb605, 0) != 0) {
                FUN_007cdef0(); // pause with delay
                return;
            }
        }
        else if (newMsgId == kMsgShowHint) {
            FUN_007a6920(); // show hint
            return;
        }
        else if (newMsgId == kMsgSetGameSpeed) {
            FUN_007a8ff0((void*)msgHeader[1]); // set speed with data
            return;
        }
        else if (newMsgId == kMsgStartTutorial) {
            (*(void (__thiscall**)(int))(*(int*)((char*)this + 0x2664) + 0))(0x10);
            (*(void (__thiscall**)(int))(*(int*)((char*)this + 0x2664) + 0))(0x20);
            return;
        }
        else if (newMsgId == kMsgStopTutorial) {
            (*(void (__thiscall**)(int))(*(int*)((char*)this + 0x2664) + 4))(0x10);
            (*(void (__thiscall**)(int))(*(int*)((char*)this + 0x2664) + 4))(0x20);
            return;
        }
        else if (newMsgId == kMsgShowMissionComplete) {
            showMissionCompleteScreen(1);
            return;
        }
        else if (newMsgId == kMsgMusicIntensityLow) {
            bool intense = FUN_00690210(0x47); // check if high intensity
            if (intense) {
                setMusicIntensity(0); // switch to low
                fadeOutMusic();
                return;
            }
        }
        else if (newMsgId == kMsgMusicIntensityHigh) {
            bool intense = FUN_00690210(0x47);
            if (!intense) {
                setMusicIntensity(1);
                fadeInMusic();
                showMissionCompleteScreen(0); // maybe hide?
            }
        }
    }
    return;
}