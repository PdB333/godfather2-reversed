// FUNC_NAME: GameSettingsManager::loadConfigFromParameters
void GameSettingsManager::loadConfigFromParameters(void* background, void* opacity, void* posX, void* posY, void* scale, void* rotation, void* alpha, void* enabledFlag, void* visible, void* zOrder)
{
    // Global singleton for game settings (likely a manager)
    int* settings = DAT_01129930;

    // Copy target to current field (e.g., for interpolation or smoothing)
    // +0x1d8 and +0x1dc are offsets within the settings structure
    *(int*)(settings + 0x1d8) = *(int*)(settings + 0x1dc);

    // Set individual properties via subroutines
    setBackgroundColor(background);                          // FUN_0095cb00
    setOpacity(opacity);                                     // FUN_0095cb90
    setPositionX(posX);                                      // FUN_0095fa40
    setPositionY(posY);                                      // FUN_0095f980
    setScale(scale);                                         // FUN_0095f9e0
    setRotation(rotation);                                   // FUN_0095c310
    setAlpha(alpha);                                         // FUN_0095fa80
    setEnabled(enabledFlag, 0);                              // FUN_0095f8b0
    setVisible(visible);                                     // FUN_0095cda0
    setZOrder(zOrder);                                       // FUN_0095ccf0
}