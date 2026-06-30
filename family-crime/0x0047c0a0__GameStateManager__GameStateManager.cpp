// FUNC_NAME: GameStateManager::GameStateManager
void __thiscall GameStateManager::GameStateManager(GameStateManager* this)
{
    // +0x00: primary vtable pointer
    this->vtable = &PTR_FUN_00e3314c;
    // +0x3C: secondary vtable / function dispatch table
    this->field_3C = &PTR_LAB_00e33168;
    // +0x48: tertiary vtable / function dispatch table
    this->field_48 = &PTR_LAB_00e33178;
    // Construct embedded sub-object at offset +0x50 (size unknown)
    SubState* sub = reinterpret_cast<SubState*>((char*)this + 0x50);
    sub->construct();      // FUN_004086d0
    sub->postConstruct();  // FUN_00408310
    // Perform global state initialization
    GlobalStateInit();     // FUN_0046c640
}