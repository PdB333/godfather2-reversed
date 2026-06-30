//FUNC_NAME: Entity::initialize
void Entity::initialize(int param_2) {
    // Static initialization (likely singleton or global state)
    initializeStaticData();

    // Store global manager pointer (unused in this function, but kept for context)
    SomeManager* pManager = g_pSomeManager; // DAT_00e2b1a4

    // Fill a 12-byte buffer using member at offset 0x40 and the input parameter
    char buffer[12]; // local_20
    fillBuffer(reinterpret_cast<char*>(this) + 0x40, buffer, param_2); // FUN_0056b420
}