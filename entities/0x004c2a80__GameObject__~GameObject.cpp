// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::~GameObject(GameObject* this)
{
    // Set vtable pointer to the destructor vtable (address 0x00e36220)
    *(void***)this = (void**)&PTR_FUN_00e36220;

    // Call base class destructor (likely EARSObject or similar)
    FUN_004c29a0(this);

    // Release the child resource object stored at offset 0x208 (0x82 * 4)
    // This is a pointer to another managed object or resource
    if (this->m_pChildResource != nullptr) {
        FUN_009c8f10(this->m_pChildResource);
    }

    // Perform final cleanup / deallocation (e.g., free memory, notify system)
    FUN_004c27f0(this);
}