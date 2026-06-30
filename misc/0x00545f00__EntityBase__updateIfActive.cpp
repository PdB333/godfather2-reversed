// FUNC_NAME: EntityBase::updateIfActive
void __thiscall EntityBase::updateIfActive(EntityBase *this) {
    bool isActive = (**(bool (__thiscall **)(EntityBase *))(*reinterpret_cast<int*>(this) + 408))(this); // vtable offset 0x198: isActive()
    if (isActive) {
        (**(void (__thiscall **)(EntityBase *))(*reinterpret_cast<int*>(this) + 600))(this); // vtable offset 600 (0x258): update()
    }
}