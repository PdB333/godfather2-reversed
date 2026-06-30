// FUNC_NAME: Sentient::canDamageTarget
// Function address: 0x006a8b50
// Checks if this entity can damage a target, considering team affiliation and special flags.

// Assumed class offsets (this):
// +0x10: m_isAlive (char / bool)
// +0x14: m_weapon (void*)
// +0x1c: m_secondaryWeapon (void*)
// +0x20: m_teamFlags (byte, bitmask of teams this entity belongs to)

// AttackInfo structure (param_2):
// +0x00: owner (void*) - the originating entity (should match this)
// +0x04: unused/reserved
// +0x08: target (void*) - entity to be attacked
// +0x0c: ...

// Target entity offsets (via param_2[2]):
// +0x20: m_teamFlags (byte)
// +0x21: m_flags (byte, bit 2 = 0x04 indicates special vulnerability check)

bool Sentient::canDamageTarget(AttackInfo* info) {
    // If any prerequisite is missing, attack cannot proceed
    if (!m_isAlive) return false;
    if (!info->owner) return false;
    Sentient* target = info->target;
    if (!target) return false;
    if (!m_weapon || !m_secondaryWeapon) return false;

    // Check target's flags: bit 2 (0x04) might mean "requires team validation" (e.g., player)
    if (target->m_flags & 0x04) {
        if (m_teamFlags == 0) return false;
        if (target->m_teamFlags == 0) return false;
        // If they share any team mask, it's a friendly and cannot be attacked
        if (m_teamFlags & target->m_teamFlags) return false;
    }

    return true;
}