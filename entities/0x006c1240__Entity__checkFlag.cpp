// FUNC_NAME: Entity::checkFlag
uint Entity::checkFlag(uint flagId) {
    int outValue = 0; // output parameter for virtual function (unused in this wrapper)
    // Call virtual function at vtable offset 0x10 (4th entry)
    auto func = reinterpret_cast<char (__thiscall *)(void*, uint, int*)>(*(uintptr_t*)(*(uintptr_t*)this + 0x10));
    char result = func(this, flagId, &outValue);
    // If virtual function returns non-zero, return original flagId; otherwise 0
    return (result != 0) ? flagId : 0;
}