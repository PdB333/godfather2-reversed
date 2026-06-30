// FUNC_NAME: Entity::Entity
// Reconstructed constructor for the Entity class.
// Address: 0x005df2f0
// Takes a flag indicating whether to call a cleanup/deallocation function after construction.
void __thiscall Entity::Entity(char shouldDelete) {
    // Set vtable pointer to Entity's vtable (0x00e3f2d0)
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00e3f2d0);
    
    // Call base class constructor (e.g., EARSObject::EARSObject or BaseEntity::BaseEntity)
    // Address of base constructor: 0x004de130
    reinterpret_cast<void (__thiscall*)(void*)>(0x004de130)(this);
    
    // If the flag indicates that the object should be cleaned up (e.g., heap allocated),
    // invoke the cleanup/destructor function.
    // Address of cleanup function: 0x009c8eb0
    if ((shouldDelete & 1) != 0) {
        reinterpret_cast<void (__thiscall*)(void*)>(0x009c8eb0)(this);
    }
}