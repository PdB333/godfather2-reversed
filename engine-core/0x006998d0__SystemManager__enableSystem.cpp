// FUNC_NAME: SystemManager::enableSystem
void SystemManager::enableSystem() {
    this->initializeSystem();
    g_systemEnabled = 1;  // Global flag at 0x01129f88
}