// FUNC_NAME: EARSObject::DestroyChildren
void __fastcall EARSObject::DestroyChildren(EARSObject *this)
{
    // Set vtable to base class vtable to prevent virtual dispatch issues during destruction
    this->vtable = &PTR_FUN_00e408cc; // Base class vtable (0x00e408cc)

    // Release child objects via the manager object at offset +0x0c
    // Each call: manager->ReleaseChild(child, 0) where 0 is likely a release flag
    this->manager->ReleaseChild(this->child1, 0); // child1 at +0x20
    this->manager->ReleaseChild(this->child2, 0); // child2 at +0x1c
    this->manager->ReleaseChild(this->child3, 0); // child3 at +0x18

    // Call manager's final release method (takes no arguments)
    this->manager->ReleaseAll(); // +0x0c of manager vtable

    // If a custom destructor callback object exists (at +0x24), call its destructor via function pointer (at +0x30)
    if (this->destructorCallbackObject != 0) {
        this->destructorFunction(this->destructorCallbackObject); // Call destructor function on the object
    }

    // Global cleanup function (likely engine heap drain or reference decrement)
    GlobalCleanupFunction(); // FUN_004083d0
}