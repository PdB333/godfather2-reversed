// FUN_005e1ca0: GameManager::constructor
void __thiscall GameManager::GameManager(void)
{
    int i;

    // Store this pointer globally (likely singleton)
    g_gameManagerInstance = this;

    // Set vtable pointer
    this->vtable = &PTR_FUN_00e3f470;

    // Initialize 5 internal sub-components (possibly arrays of something)
    i = 4;
    do {
        this->initSubComponent();
        i = i - 1;
    } while (-1 < i);

    // Initialize various fields – could represent state, flags, or counters
    this->field_0x5ce = 0;   // int at offset 0x5CE
    this->field_0x5cf = 0;   // int at offset 0x5CF
    this->field_0x5d0 = 0;   // int at offset 0x5D0
    this->byte_0x5d1 = 0;    // byte at offset 0x5D1
    this->field_0x5d2 = 1;   // int at offset 0x5D2
    this->field_0x5d3 = 5;   // int at offset 0x5D3
    return;
}