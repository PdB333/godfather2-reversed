// FUNC_NAME: Entity::activate
void Entity::activate() {
    // Set active flag at offset +0x10 to 1
    *(int*)((char*)this + 0x10) = 1;
    // Call virtual function at vtable offset 0x28 (e.g., onActivate)
    void (*vfunc)() = *(void (**)())(*(int*)((char*)this + 0xc) + 0x28);
    vfunc();
}