// FUNC_NAME: Entity::updateComponent
void __thiscall Entity::updateComponent(void) {
    // +0x34: pointer to a sub-component object
    int* component = *(int**)(this + 0x34);
    if (component != 0) {
        // +0x38: pointer to data passed to the virtual update function
        // Virtual function at vtable offset 0x34 (13th function) is called
        (*(void (**)(void*))(*component + 0x34))((void*)(this + 0x38));
    }
}