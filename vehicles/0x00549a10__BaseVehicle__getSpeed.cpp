// FUNC_NAME: BaseVehicle::getSpeed
// Address: 0x00549a10
// Returns the vehicle's current forward speed from its physics component
float __thiscall BaseVehicle::getSpeed(void* this) {
    // Dereference pointer at +0x18 (likely m_pPhysicsComponent)
    void* physicsComponent = *(void**)((char*)this + 0x18);
    // Read float at offset +0x18 of physics component (likely m_fSpeed)
    return *(float*)((char*)physicsComponent + 0x18);
}