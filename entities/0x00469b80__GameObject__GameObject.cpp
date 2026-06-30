// FUNC_NAME: GameObject::GameObject
GameObject::GameObject() {
    // Set vtable pointer to this class's vtable (+0x00)
    this->vtable = &g_vtable_00e322ec;

    // Call base initialization (likely RefCountedObject or SimObject constructor)
    this->initBase();
}