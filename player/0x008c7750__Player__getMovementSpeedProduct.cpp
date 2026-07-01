// FUNC_NAME: Player::getMovementSpeedProduct
/*
 * Function address: 0x008c7750
 * Role: Computes product of two fields at offsets 0x144 and 0x184 of a component object.
 * Probably an acceleration or force multiplier for Player movement.
 */
float __thiscall Player::getMovementSpeedProduct(void* this) {
    void* component = reinterpret_cast<void*>(FUN_008c7490(this));
    if (component) {
        return *(float*)(reinterpret_cast<uintptr_t>(component) + 0x184) *
               *(float*)(reinterpret_cast<uintptr_t>(component) + 0x144);
    }
    return 0.0f;
}