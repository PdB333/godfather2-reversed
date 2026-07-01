// FUNC_NAME: LoadingScreen::waitForLoad
void LoadingScreen::waitForLoad() {
    // Call base class initialization
    baseInit();

    // Set the loading screen type/hash (0x1c2b2a0d likely identifies this as a loading screen)
    setType(0x1c2b2a0d);

    // Wait until loading is complete
    while (!isLoadComplete()) {
        processLoading();
    }
}