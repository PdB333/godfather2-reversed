// FUNC_NAME: Entity::setHealth
void __thiscall Entity::setHealth(Entity* this, int param2, int param3, float param4)
{
    // Check flag bit at offset 0xac (likely m_flags or m_healthState)
    if ((this->m_flags & 1) != 0) {
        // Compute base value using external helper
        float baseVal = calculateHealthBase(param2, param3, param4);
        // Compute bonus value using external helper, adding base to param4
        float bonusVal = calculateHealthBonus(param2, param3, baseVal + param4);
        // Final health = bonus + (base + param4)
        param4 = bonusVal + (baseVal + param4);
    }
    // Store computed health at +0x88 (m_currentHealth) and +0x8c (m_maxHealth)
    this->m_currentHealth = param4;
    this->m_maxHealth = param4;
    // Set flag bit 0 to indicate health is initialized
    this->m_flags |= 1;
}