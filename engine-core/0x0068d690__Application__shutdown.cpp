// FUNC_NAME: Application::shutdown
void __thiscall Application::shutdown(Application *this) {
    // Set vtable pointers to destructor-specific vtables (classes are being destructed)
    this->vtable0 = &PTR_FUN_00d5c66c;        // +0x00: first vtable
    this->vtable1 = &PTR_LAB_00d5c668;        // +0x0C: second vtable / interface pointer
    this->field14 = &PTR_LAB_00d5c664;        // +0x14: function pointer or vtable

    // Shut down a global singleton (likely EARS engine core)
    ShutdownGlobalSingleton(&g_GlobalSingleton);   // FUN_004086d0

    // Signal resource manager to enter shutdown mode (1 = active shutdown)
    SetResourceManagerShutdownFlag(1);             // FUN_0040eba0

    // Check if an optional subsystem should be torn down now
    char condition = GetShutdownCondition();       // FUN_008a4380
    if (condition == '\0') {
        OptionalSubsystemShutdown();               // FUN_009cb3d0
    }

    // Reassign vtables/function pointers for further cleanup
    this->field14 = &PTR_LAB_00d5c660;            // +0x14: update function pointer
    g_bIsShuttingDown = 0;                         // DAT_01129810: global flag cleared
    this->vtable1 = &PTR_FUN_00e32808;            // +0x0C: another destructor vtable

    // Iterate through a linked list of registered objects (at offset +0x10) and clear them
    // Each node has structure: data (0x00), next (0x04)
    LinkedListNode *current = (LinkedListNode *)this->pListHead; // +0x10
    while (current != nullptr) {
        LinkedListNode *next = current->next; // +0x04
        current->next = nullptr;              // Clear next pointer
        current->data = nullptr;              // Clear data pointer
        current = next;
    }

    // Final cleanup – likely frees internal memory or notifies other systems
    FinalShutdown(); // FUN_004083d0
}