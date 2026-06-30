// FUNC_NAME: Character::updateAnimationState
void Character::updateAnimationState(void) {
    // this is assumed from unaff_ESI
    // +0x00: vtable?
    // +0x04: unknown
    // +0x08: m_pComponent (pointer)
    // +0x30: m_pSomething (pointer)
    // +0x4a: m_someShort (short)
    // +0x5c: m_animParam (int32)
    // +0x64: m_animType (int8)
    // +0x65: m_animFlag (int8) - note: offset 0x65 is right after 0x64
    // +0x68: m_state (int32)
    // +0x6c: m_movementFlags (int8)
    // +0x74: m_timer (float)
    // +0x7b: m_attackFlag (int8)

    if ((this != NULL) && (this->m_pComponent != NULL) && (this->m_pSomething != NULL)) {
        // First animation update
        setAnimation((int8_t)this->m_animType, this->m_animParam, (int8_t)this->m_animFlag);
        this->m_someShort = 0;
        updatePhysics();           // FUN_005f20c0
        this->m_timer = 0.0f;

        // Randomize timer if game time is below threshold
        // DAT_00e44598 likely g_gameTime (float)
        // *(float *)(this->m_pComponent + 0x18) is threshold
        if (g_gameTime < *(float *)((uint8_t *)this->m_pComponent + 0x18)) {
            uint32_t idx = g_randomIndex & g_randomMask;  // DAT_010c2678 & DAT_012054b4
            g_randomMask++;                                // DAT_012054b4
            // DAT_00e44564 is g_baseTime (float)
            // DAT_010c2680 is array of random floats
            // DAT_00e2e210 is g_someMultiplier (float)
            this->m_timer = g_baseTime - g_randomValues[idx] * *(float *)((uint8_t *)this->m_pComponent + 0x18) * g_someMultiplier;
        }

        // Set attack flag based on sign bit of movement flags (bit7)
        // (int8_t) >> 7: 0 or -1, then * -2 gives 0 or 2
        this->m_attackFlag = (int8_t)(this->m_movementFlags >> 7) * -2;
        this->m_state = 2;
        playSound(3);              // FUN_005e5200(3)
        // Second animation update (same as first)
        setAnimation((int8_t)this->m_animType, this->m_animParam, (int8_t)this->m_animFlag);
    }
}