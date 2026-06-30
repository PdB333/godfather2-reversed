// FUNC_NAME: Entity::shutdown
void Entity::shutdown() {
    // +0x20: pointer to a registered object (e.g., listener, component)
    if (this->m_pRegisteredObject != nullptr) {
        // +0x0c: resource identifier (e.g., handle, ID)
        releaseResource(this->m_resourceId);
        // Get manager singleton (e.g., EventManager, ComponentManager)
        int* manager = getManager();
        // Call global unregister callback with manager's data and this object's pointer
        g_pUnregisterCallback(*(int*)(manager + 0x0c), &this->m_pRegisteredObject);
    }
    // Global cleanup step (e.g., decrement reference count, release shared resources)
    globalCleanup();
    // Release another resource using +0x1c (e.g., secondary handle)
    releaseAnotherResource(this->m_anotherId);
    // Final destructor call (likely calls base class destructor or frees memory)
    finalizeDestructor(this);
}