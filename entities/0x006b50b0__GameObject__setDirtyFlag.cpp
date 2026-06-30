// FUNC_NAME: GameObject::setDirtyFlag
void GameObject::setDirtyFlag(bool enable) {
    // Offset +0x34 is a flags field (bit 0x100000 = dirty flag)
    if (enable) {
        *(uint*)(this + 0x34) |= 0x100000;
    } else {
        *(uint*)(this + 0x34) &= ~0x100000;
    }
    // Notify the object that a dirty status changed (parameter 0 = reserved)
    FUN_006b4e30(*(void**)(this + 0x16C), 0);
}