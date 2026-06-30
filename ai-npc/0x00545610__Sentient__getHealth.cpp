// FUNC_NAME: Sentient::getHealth
float __thiscall Sentient::getHealth(Sentient* this) {
    // Check if the sentient is alive via virtual function at vtable+0x198
    bool isAlive = (*(bool (__thiscall**)(Sentient*))(*(uint32_t*)this + 0x198))(this);
    if (isAlive) {
        // Access health component at offset 0x360 (this->healthComponent)
        // The health component has a virtual function at vtable+0x28 that returns current health
        void* healthComponent = *(void**)((uint8_t*)this + 0x360);
        float health = (*(float (__thiscall**)(void*))(*(uint32_t*)healthComponent + 0x28))(healthComponent);
        return health;
    }
    return 0.0f;
}