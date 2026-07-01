// FUNC_NAME: playMenuSoundEffect

void playMenuSoundEffect(int menuAction) {
    earPlayEvent(0xc); // Generic menu sound (e.g., click)
    if (menuAction != 0x1f && menuAction != 0x22) {
        earPlayEvent(0x3a); // Confirm/select sound
        earProcess();
        return;
    }
    earPlayEvent(0x3b); // Cancel/back sound
    earProcess();
}