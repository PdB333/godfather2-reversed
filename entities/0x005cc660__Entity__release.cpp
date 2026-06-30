// FUNC_NAME: Entity::release
void Entity::release() {
    // +0x8c: pointer to primary component (e.g., physics or AI)
    int* component = *(int**)(this + 0x8c);
    if (component == 0) {
        // +0x88: fallback component pointer
        component = *(int**)(this + 0x88);
    }
    if (component != 0) {
        // Call virtual function at vtable+4 (likely Release or Delete) with flag 0
        (**(code**)(**(int**)(g_engineVtable + 4) + 4))(component, 0);
    }
    // Call base class release via global vtable
    (**(code**)(**(int**)(g_engineVtable + 4) + 4))();
    // Decrement global reference count for this object type
    g_refCount--;
}