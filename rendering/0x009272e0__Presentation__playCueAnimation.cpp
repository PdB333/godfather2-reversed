// FUNC_NAME: Presentation::playCueAnimation
void __fastcall Presentation::playCueAnimation(int this)
{
    undefined4 uVar1;
    
    if (*(char *)(this + 0x3a0) == '\0') {
        if (*(char *)(this + 0x3a1) == '\0') {
            return;
        }
    }
    else if (*(char *)(this + 0x3a1) == '\0') {
        FUN_00927870(); // Presentation::initializeAnimation
        uVar1 = _DAT_00d5c458; // Global animation time
        *(undefined4 *)(this + 0x3ac) = _DAT_00d5c458; // +0x3ac animationStartTime
        *(undefined4 *)(this + 0x3b0) = uVar1; // +0x3b0 animationEndTime
        *(undefined4 *)(this + 0x3a4) = DAT_00d87a9c; // +0x3a4 animationDuration
        uVar1 = DAT_00d87a98; // Animation speed
        *(undefined1 *)(this + 0x3a1) = 1; // +0x3a1 animationActive
        *(undefined4 *)(this + 0x3a8) = uVar1; // +0x3a8 animationSpeed
        FUN_005c0260(this + 0x10, &LAB_00927270, 1); // SimManager::registerEvent
        if (DAT_01206978 != 0) { // Sound hash
            FUN_00408900(this + 0x4c, &DAT_01206978, 0x8000); // AudioManager::playSound
        }
        FUN_005c1880(); // SimManager::processEvents
        uVar1 = FUN_00610df0("ui_cursor", 0); // ResourceManager::findResource
        uVar1 = FUN_00610df0(&DAT_00d87a18, uVar1); // ResourceManager::resolveResource
        uVar1 = FUN_00611000(uVar1); // ResourceManager::getResourceData
        *(undefined4 *)(this + 0x3d0) = uVar1; // +0x3d0 cursorResource
        FUN_0069e660(&LAB_00926d50); // Presentation::triggerTimeline
        *(undefined1 *)(this + 0x3a3) = 1; // +0x3a3 animationStarted
        return;
    }
    *(undefined1 *)(this + 0x3a3) = 1; // +0x3a3 animationStarted
    return;
}