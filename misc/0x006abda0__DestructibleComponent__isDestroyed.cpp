// FUNC_NAME: DestructibleComponent::isDestroyed
extern float DAT_01205228; // Global threshold (possibly max armor or invulnerability timer)

bool __fastcall DestructibleComponent::isDestroyed(void* this) {
    // +0x10: m_owner (Entity*) - must be non-null
    // +0x18: m_health (float) - current health
    // +0x2C: m_armorOrTimer (float) - compared to global threshold
    if (*(void**)((char*)this + 0x10) == nullptr) return false;
    if (*(float*)((char*)this + 0x18) > 0.0f) return false;
    if (*(float*)((char*)this + 0x2C) > DAT_01205228) return false;
    return true;
}