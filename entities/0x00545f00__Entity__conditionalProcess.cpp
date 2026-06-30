// FUNC_NAME: Entity::conditionalProcess
void Entity::conditionalProcess() {
    // Call virtual function at vtable offset 0x198 (likely isConditionMet or shouldUpdate)
    bool condition = (this->*(void (__thiscall **)(Entity*))(*(uint32_t*)this + 0x198))();
    if (condition) {
        // Call virtual function at vtable offset 600 (0x258) (likely executeUpdate or process)
        (this->*(void (__thiscall **)(Entity*))(*(uint32_t*)this + 600))();
    }
}