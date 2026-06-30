// FUNC_NAME: Entity::handleDeactivationCheck

void __thiscall Entity::handleDeactivationCheck() {
    // Check flag at offset +0x98 (likely m_active)
    if (!*(char*)((uintptr_t)this + 0x98)) {
        // If flag is zero (inactive), call deactivation logic (address 0x006b9f10)
        this->onDeactivate();
    }
}