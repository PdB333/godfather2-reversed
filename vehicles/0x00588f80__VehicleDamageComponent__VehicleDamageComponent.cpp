// FUNC_NAME: VehicleDamageComponent::VehicleDamageComponent
void VehicleDamageComponent::VehicleDamageComponent()
{
    // Base class constructor (likely DamageComponent or StandardDamageComponent)
    DamageComponent::DamageComponent();

    // Set vtable pointer (vtbl at 0x00e3ac3c)
    *(int**)this = (int*)&PTR_FUN_00e3ac3c;

    // Initialize all damage-related fields
    this->m_field_0x74 = 0;   // +0x74 (int)
    this->m_field_0x78 = 0;   // +0x78 (int)
    this->m_field_0x7C = 0;   // +0x7C (int)
    *(char*)((int)this + 0x70) = 0; // +0x70 (byte)
    this->m_field_0x80 = 0;   // +0x80 (int)
    this->m_field_0x8C = 0;   // +0x8C (int)
    this->m_field_0x9C = 0;   // +0x9C (int)
    this->m_field_0xA4 = 0;   // +0xA4 (int)
    this->m_field_0xB4 = 0;   // +0xB4 (int)
    this->m_field_0xB8 = 0;   // +0xB8 (int)
    this->m_field_0xBC = 0;   // +0xBC (int)
    this->m_field_0xC0 = 0;   // +0xC0 (int)
    this->m_field_0xC4 = 0;   // +0xC4 (int)
    this->m_field_0xC8 = 0;   // +0xC8 (int)
    this->m_field_0xCC = 0;   // +0xCC (int)
    this->m_field_0xD0 = 0;   // +0xD0 (int)

    // Set damage type to 4 (likely a specific damage category)
    this->m_damageType = 4;            // +0x84 (int)

    // Set health to -1 (infinite or disabled)
    this->m_health = -1;               // +0x88 (int)

    // Clear additional damage modifiers
    this->m_field_0x90 = 0;            // +0x90 (int)
    this->m_field_0x94 = 0;            // +0x94 (int)

    // Set armor/mitigation values to -1 (infinite or disabled)
    this->m_armor = -1;                // +0x98 (int)
    this->m_alternateHealth = -1;      // +0xA0 (int)

    // Clear remaining fields
    this->m_field_0xA8 = 0;            // +0xA8 (int)
    this->m_field_0xAC = 0;            // +0xAC (int)

    // Set maximum health to 32 (e.g., 32 hit points)
    this->m_maxHealth = 0x20;          // +0xB0 (int)
}