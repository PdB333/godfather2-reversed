// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::~GameObject(GameObject *this)
{
    // Restore vtable to the base class vtable during destruction
    this->vtable = (GameObjectVTable *)&PTR_LAB_00d63090;

    // If the sub-object at offset +0x68 (0x1a * 4) exists, destroy it
    if (this->subObject != nullptr)
    {
        // FUN_004daf90 is likely the destructor for the sub-object;
        // it receives the address of the sub-object member so it can clean up and null the pointer.
        FUN_004daf90(&this->subObject);
    }

    // Call global cleanup (likely base class destructor or engine‐level teardown)
    FUN_0080ea60();
}