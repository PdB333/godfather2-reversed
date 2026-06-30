// FUNC_NAME: GameObject::~GameObject
// Address: 0x00498070
// Reconstructed destructor for a game object with sub-object and resource pointers.
// Offsets: this+0x0 = m_pSubObject, this+0x14 = m_pResource.
// Sub-object has a pointer at its +0x30 to a secondary child.

class GameObject
{
public:
    GameObject *m_pSubObject;  // +0x00
    void      *m_pResource;   // +0x14
    // ... other members

    // Helper functions (calls to original addresses)
    void __thiscall baseDestructor(void);                 // FUN_00498180
    static void __cdecl releasePointer(void *ptr);        // FUN_009c8f10
    static void __cdecl deleteObject(GameObject *obj);    // FUN_009c8eb0
};

__thiscall GameObject::~GameObject(void)
{
    // Base class cleanup (likely virtual table adjustment or reference counting)
    this->baseDestructor();

    // Release owned resource at offset 0x14
    GameObject::releasePointer(this->m_pResource);

    // If sub-object exists, release its child at +0x30 then delete the sub-object
    if (this->m_pSubObject != nullptr)
    {
        // Offset 0x30 within the sub-object is another pointer (e.g., a component)
        void *subChild = *(void **)((char *)this->m_pSubObject + 0x30);
        GameObject::releasePointer(subChild);
        GameObject::deleteObject(this->m_pSubObject);
    }
}