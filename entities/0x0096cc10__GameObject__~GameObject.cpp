// FUNC_NAME: GameObject::~GameObject
void __thiscall GameObject::destructor(int this) {
    // Call global/static cleanup
    cleanupStaticResources();

    // Release resource at offset +0x6c (e.g., a texture or audio handle)
    releaseObject(*(void**)(this + 0x6c));

    // Check for sub-object at +0x58 (e.g., a child component)
    int* subObj = *(int**)(this + 0x58);
    if (subObj != nullptr) {
        // Release resource at subObj+8 (e.g., a reference counter)
        releaseObject(*(void**)(subObj + 8));
        // Destroy the sub-object itself
        deleteSubObject(subObj);
    }

    // Release resource at offset +0x4c (e.g., another handle or pointer)
    if (*(int*)(this + 0x4c) != 0) {
        releaseObject(*(void**)(this + 0x4c));
    }

    // Final cleanup (e.g., decrement global reference count)
    finalizeCleanup();
}