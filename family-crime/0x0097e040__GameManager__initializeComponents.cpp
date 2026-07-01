// FUNC_NAME: GameManager::initializeComponents
// Address: 0x0097e040
// This function calls six subsystem initialization methods.
// It is likely the main initializer for the game manager or core system.
// All callees are member functions of the same class, taking 'this' as ECX.

void GameManager::initializeComponents(uint param_1) // param_1 is likely 'this' as a uint for raw pointer
{
    // Initialize various subsystems in order.
    // Each sub-function sets up a specific module (audio, input, physics, etc.)
    initializeAudio(param_1);       // 0x0097de20
    initializeInput(param_1);       // 0x0097d6c0
    initializeNetworking(param_1);  // 0x0097df40
    initializePhysics(param_1);     // 0x0097d940
    initializeScripting(param_1);   // 0x0097dfa0
    initializeUI(param_1);          // 0x0097da80
    return;
}