// FUNC_NAME: EntityComponent::attachToOwner
void __thiscall EntityComponent::attachToOwner(Entity* owner, void* data) {
    // +0x04: pointer to owner entity
    this->owner = owner;
    
    // Call owner's vtable function at offset 0x08 (likely onAttach or preInit)
    owner->vtable->onAttach();
    
    if (data != nullptr) {
        // +0x08: pointer to child component created from data
        this->child = FUN_004265d0(data, this->owner);
        
        // Call owner's vtable function at offset 0x04 (init with data)
        owner->vtable->init(data, 0);
        
        // Call owner's vtable function at offset 0x0C (finalize or postInit)
        owner->vtable->finalize();
    } else {
        // No data: clear child and just finalize
        this->child = nullptr;
        owner->vtable->finalize();
    }
}