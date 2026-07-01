// FUNC_NAME: SomeManager::initEventConnections
// Function address: 0x00974030
// This function appears to initialize event handler connections for an object.
// It registers five different signal handlers with callbacks at specific offsets within the object.
void __fastcall SomeManager::initEventConnections(SomeManager* this)
{
    // Initialize base or perform initial setup
    baseSetup();  // FUN_005c1740 - likely a base class initialization

    // Register event handlers using connect functions with global signal slots
    // The offsets (this+0x50, this+0x54, etc.) are likely m_pfnCallbackX member function pointers

    connectEvent(&g_signalSlot1, this + 0x50, 0, 0, 1);  // FUN_005c0400 - connect with immediate flag
    connectEvent(&g_signalSlot2, this + 0x54, &g_lambda_target, 0, 0);  // FUN_005c0400 with a static target (LAB_00973fb0)
    connectEventWithPriority(&g_signalSlot3, this + 0x58, 0, 0, 1);  // FUN_005c0460 - different variant
    connectEvent(&g_signalSlot4, this + 0x5c, 0, 0, 1);
    connectEvent(&g_signalSlot5, this + 0x60, 0, 0, 1);
}