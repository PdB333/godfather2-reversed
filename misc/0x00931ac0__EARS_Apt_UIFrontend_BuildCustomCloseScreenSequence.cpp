// Xbox PDB: EARS_Apt_UIFrontend_BuildCustomCloseScreenSequence
// FUN_NAME: UIScreen::showBlankFrame
void __fastcall UIScreen::showBlankFrame(int delay) {
    char moviePathBuffer[12]; // local_c, local_8, local_4: buffer for movie clip path
    // Copy global blank movie path (DAT_01130368) into local buffer
    flashStringCopy(moviePathBuffer, gBlankMoviePath, 0); // second argument 0 = no max length

    // Tell the blank movie clip to gotoAndStop at frame "fr_blank"
    flashInvokeMethod("gotoAndStop", gBlankTargetPath, 1, "fr_blank");

    // Check if the UI system is active
    if (isUIActive()) {
        // Call vtable+4 on the UI screen manager: likely closeScreen()
        gUIScreenManager->closeScreen();
    }
    // Call vtable+0x2c on the UI state object: likely stopScreen()
    gUIScreenState->stopScreen();

    // Compute delay for the transition callback
    int actualDelay = (delay == 0) ? 0 : delay + 0x14; // +20 ms
    scheduleCallback(actualDelay, blankTransitionCallback, 0);
}