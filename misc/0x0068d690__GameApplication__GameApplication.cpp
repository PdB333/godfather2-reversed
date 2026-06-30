// FUNC_NAME: GameApplication::GameApplication
void __fastcall GameApplication::GameApplication(GameApplication* this)
{
    // Set up vtable pointers for multiple inheritance
    this->vtable0 = (void*)&PTR_FUN_00d5c66c;          // +0x00: primary vtable
    this->vtable3 = (void*)&PTR_LAB_00d5c668;          // +0x0C: secondary vtable? (offset 3*4)
    this->vtable5 = (void*)&PTR_LAB_00d5c664;          // +0x14: tertiary vtable? (offset 5*4)

    // Initialize global subsystems
    MemoryManager::init(&DAT_01206940);                 // Global memory manager init
    InputManager::setEnabled(true);                     // Enable input controller

    char isDebug = IsDebugBuild();                      // Check debug/retail mode
    if (isDebug == '\0') {
        ExitGame();                                     // Exit if not debug? Or maybe abort if debug?
    }

    // Replace last vtable slot
    this->vtable5 = (void*)&PTR_LAB_00d5c660;          // +0x14: final vtable

    g_bInitialized = 0;                                 // Global initialization flag

    this->vtable3 = (void*)&PTR_FUN_00e32808;          // +0x0C: updated secondary vtable

    // Clear linked list of registered objects (starting at this->listHead)
    Node* node = (Node*)this->listHead;                 // +0x10: pointer to first node
    while (node != nullptr) {
        Node* next = (Node*)node->next;                 // node[1] = next pointer
        node->next = nullptr;                           // detach
        node->value = 0;                                // zero out data
        node = next;
    }

    MemoryManager::shutdown();                          // Final cleanup
}