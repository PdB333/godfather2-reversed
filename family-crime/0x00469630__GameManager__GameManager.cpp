// FUNC_NAME: GameManager::GameManager
class GameManager {
public:
    GameManager();
    // Offset +0x00: primary vftable pointer
    // Offset +0x04: secondary vftable pointer (likely base class)
};

GameManager* g_gameManager; // 0x01223478

GameManager::GameManager() {
    // Setup vtable pointers in order observed in disassembly
    this->vftable = (void*)&PTR_FUN_00e320ac;          // Primary vtable
    this->baseVftable = (void*)&PTR_LAB_00e320bc;      // Temporary base vtable (overwritten)
    this->baseVftable = (void*)&PTR_LAB_00e320b8;      // Final secondary vtable

    // Store instance in global singleton
    g_gameManager = this;

    // Call base class constructor / initializer
    FUN_0043e2e0(this);
}