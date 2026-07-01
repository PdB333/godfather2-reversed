//FUNC_NAME: Entity::isDead
// Function address: 0x00956b70
// Checks if the entity's health (or timer) at offset +0x80 is <= 0.0
bool __thiscall Entity::isDead(void) {
    // +0x80: health or expiration timer
    if (*(float *)(this + 0x80) <= 0.0f) {
        return true;
    }
    return false;
}