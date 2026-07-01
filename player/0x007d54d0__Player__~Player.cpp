// FUNC_NAME: Player::~Player

// Destructor for Player class at 0x007d54d0
// This appears to be part of a multi-inheritance destructor chain.
// It cleans up various subsystems and releases child objects.

void __thiscall Player::~Player(Player *this)
{
    int *pManager1;
    int *pManager2;
    int somePtr;

    // Set vtable to first base class (likely GameObject or similar)
    this->vtable = (void *)&PTR_LAB_00d6ef68;

    // Call base class destructor (first base)
    FUN_007d5140();

    // Clear bit 0x2000 from a global flag (probably game state flags)
    g_gameManager->flags0x5c &= 0xffffdfff;

    // Get first manager (e.g., InputDeviceManager or SimManager)
    pManager1 = (int *)FUN_007ab130();
    // Call virtual release on member at offset 0x2f (0xBC)
    (**(code **)(*pManager1 + 4))(this->m_member0x2f);

    // Get second manager (e.g., CameraManager)
    pManager2 = (int *)FUN_007ab150();
    // Call virtual release on member at offset 0x2e (0xB8)
    (**(code **)(*pManager2 + 4))(this->m_member0x2e);

    // Retrieve a pointer from member at offset 0x16 (0x58)
    somePtr = this->m_member0x16;

    // Call some function (maybe reset or cleanup)
    FUN_00798480();

    // Clear bit 0x800 from a field at offset 0x24a0 from somePtr
    *(uint *)(somePtr + 0x24a0) &= 0xfffff7ff;

    // Release child objects if they exist (using FUN_004daf90 as delete/release)
    if (this->m_member0x27 != NULL) {
        FUN_004daf90(&this->m_member0x27);
    }
    if (this->m_member0x25 != NULL) {
        FUN_004daf90(&this->m_member0x25);
    }
    if (this->m_member0x23 != NULL) {
        FUN_004daf90(&this->m_member0x23);
    }

    // Set vtable for second base class (e.g., another interface)
    this->vtableSecond = (void *)&PTR_LAB_00d6ba68;

    // Reset primary vtable to second base's vtable
    this->vtable = (void *)&PTR_LAB_00d6b95c;

    // Call second base class destructor
    FUN_0080ea60();

    return;
}