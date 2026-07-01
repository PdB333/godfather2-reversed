// FUNC_NAME: BNKStreamManager::BNKStreamManager
// Function address: 0x008b2bb0
// Purpose: Constructor for BNKStreamManager, initializes vtable and EARS audio data

void __thiscall BNKStreamManager::BNKStreamManager(BNKStreamManager *this)
{
    // Set primary vtable pointer at offset +0x00
    *this = &g_vtable_BNKStreamManager;

    // Set secondary interface vtable pointers for multiple inheritance or interface implementation
    // +0x3C (0xF * 4)
    this->field_0x3C = &g_interfaceVtable1;
    // +0x48 (0x12 * 4)
    this->field_0x48 = &g_interfaceVtable2;

    // Initialize global EARS audio data block (DAT_0112f4b4)
    FUN_004086d0(&g_earsAudioData);
    FUN_00408310(&g_earsAudioData);

    // Perform further initialization specific to BNK streaming
    FUN_008b2820();
}