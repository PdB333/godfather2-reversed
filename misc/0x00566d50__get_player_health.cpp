// FUNC_NAME: get_player_health
double get_player_health(void)
{
    // FUN_00ad8d40() likely returns a pointer to the global game manager singleton
    int *gameManager = (int *)FUN_00ad8d40();
    if (gameManager == (int *)0x0) {
        return 0.0;
    }

    // vtable +0x48: e.g., GodfatherGameManager::getCurrentPlayer()
    int *player = (int *)(**(code **)(*gameManager + 0x48))();
    if (player == (int *)0x0) {
        return 0.0;
    }

    // vtable +0x28: e.g., Player::getHealthComponent()
    int *component = (int *)(**(code **)(*player + 0x28))();
    if (component == (int *)0x0) {
        return 0.0;
    }

    // vtable +8: e.g., HealthComponent::getHealth() – returns double health value
    return (**(code **)(*component + 8))();
}