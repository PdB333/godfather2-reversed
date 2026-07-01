// FUNC_NAME: Player::Player
// Function address: 0x007cfc90
// Constructor for Player class (derived from Entity/Sentient)
// Initialises player-specific fields, random seed, and subsystems.

Player* __thiscall Player::Player(Player* this, uint param_2, uint param_3)
{
    // Call base entity constructor (0x007ab5e0)
    Entity* baseEntity = reinterpret_cast<Entity*>(this);
    baseEntity->Entity(param_2, param_3);

    // Set vtable for Player (from PTR_LAB_00d6ed08)
    this->m_vtable = &g_PlayerVtable;

    // Initialise unused flags / fields to zero (offsets 0x74 to 0x84)
    this->m_zeroFlags1 = 0;  // +0x74
    this->m_zeroFlags2 = 0;  // +0x78
    this->m_zeroFlags3 = 0;  // +0x7C
    this->m_zeroFlags4 = 0;  // +0x80
    this->m_zeroFlags5 = 0;  // +0x84

    // Generate random float for timing/seeding (FUN_00799230)
    this->m_randomSeed = (float)FUN_00799230(); // +0x88

    // More zero-initialised fields (offsets 0x8C to 0xA0)
    this->m_zeroFlags6 = 0;  // +0x8C
    this->m_zeroFlags7 = 0;  // +0x90
    this->m_zeroFlags8 = 0;  // +0x94
    this->m_zeroFlags9 = 0;  // +0x98
    this->m_zeroFlags10 = 0; // +0x9C
    this->m_zeroFlags11 = 0; // +0xA0

    // Additional field at offset 0xAC
    this->m_zeroFlags12 = 0; // +0xAC

    // Initialise subsystems
    FUN_006da9d0();           // core initialisation
    FUN_007f6300(0);          // set controller index (player 0)
    FUN_007f63e0(0x5f);       // set some flag (0x5f)
    FUN_007ac4f0(0);          // set network slot to 0
    FUN_007ac510(0);          // set network ID to 0
    FUN_007ac790(_DAT_00e52f98); // attach global reference

    // Remaining fields (offsets 0xA4, 0xA8, 0xB0, 0xB4, 0xB8)
    this->m_zeroFlags13 = 0;          // +0xA4
    this->m_zeroFlags14 = 0;          // +0xA8
    *(unsigned char*)((unsigned int)this + 0xB0) = 0; // +0xB0 (byte)
    this->m_globalValue1 = _DAT_00e52fd8; // +0xB4
    this->m_globalValue2 = _DAT_00e52fdc; // +0xB8

    return this;
}