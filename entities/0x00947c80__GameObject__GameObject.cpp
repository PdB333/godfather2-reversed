//FUNC_NAME: GameObject::GameObject
GameObject::GameObject() {
    // Initialize base memory pool or allocator with parameters (1,1)
    MemoryPool::init(1, 1);

    // Set primary vtable pointer (offset +0x00)
    this->vtable = &g_vtable_00d8b510;

    // Set secondary interface vtable (offset +0x18)
    this->pSecondaryVtable = &g_vtable_00d8b480;

    // Set function pointer for a callback or method (offset +0x1C)
    this->pCallback = &g_function_00947a80;

    // Initialize another base component with parameter 0
    ComponentBase::init(0);

    // Set self-referential pointer to point to the secondary vtable field (offset +0x14)
    this->pSelfRef = &this->pSecondaryVtable;
}