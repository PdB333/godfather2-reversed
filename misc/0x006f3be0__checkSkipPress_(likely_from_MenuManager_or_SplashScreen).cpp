// FUNC_NAME: checkSkipPress (likely from MenuManager or SplashScreen)
char checkSkipPress(void) {
    char result;

    // Repeatedly check for a button press on the first controller.
    // The multiple calls may serve as a debounce or require multiple frames of input.
    result = isControllerButtonPressed(0); // +0x00: parameter is controller index 0
    if (result == '\0') {
        result = isControllerButtonPressed(0);
        if (result == '\0') {
            result = isControllerButtonPressed(0);
            if (result == '\0') {
                result = isControllerButtonPressed(0);
                if (result == '\0') {
                    return 0;
                }
            }
        }
    }
    return 1;
}