// FUNC_NAME: PlayerSM::constructor
// Function address: 0x0064f490
// Role: Constructor for PlayerSM (player state machine) - initializes base class and zeroes member fields

void PlayerSM::constructor() {
    // Call base class constructor (FUN_0064dfe0)
    BaseClass::constructor(); // Assume base class constructor

    // Set vtable pointer to PlayerSM's vtable
    this->vtable = reinterpret_cast<void**>(0x00e42f48); // vtable for PlayerSM

    // Initialize all member variables to zero
    this->m_field_0x21C = 0; // +0x21C (dword)
    this->m_field_0x21C = 0; // +0x21C (duplicate assignment, possibly intentional)
    this->m_field_0x20C = 0; // +0x20C (dword)
    this->m_byte_0x208 = 0;  // +0x208 (byte)
    this->m_byte_0x209 = 0;  // +0x209 (byte)
    this->m_field_0x1FC = 0; // +0x1FC (dword)
    this->m_field_0x214 = 0; // +0x214 (dword)
    this->m_field_0x218 = 0; // +0x218 (dword)
    this->m_field_0x210 = 0; // +0x210 (dword)
    this->m_field_0x200 = 0; // +0x200 (dword)
}