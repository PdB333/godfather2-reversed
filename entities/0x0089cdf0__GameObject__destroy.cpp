// FUNC_NAME: GameObject::destroy

class GameObject {
public:
    // Offset +0x00: vtable pointer
    // Offset +0x04: possible reference count or other field
    // Offset +0x08: pointer to sub-object (e.g., data, child)
    void* m_vtable;
    int m_refCount; 
    void* m_pData;

    // Destroys the object, optionally freeing memory if flags & 1
    int __thiscall destroy(byte flags);
};

// External helper functions
void __cdecl releaseSubObjectPointer(void** ppObj);
void __cdecl deallocateObject(GameObject* obj);

int GameObject::destroy(byte flags)
{
    // If the sub-object pointer is non-null, release it
    if (m_pData != 0) {
        releaseSubObjectPointer(&m_pData);
    }

    // If the memory-deallocation flag is set, free this object
    if ((flags & 1) != 0) {
        deallocateObject(this);
    }

    return reinterpret_cast<int>(this);
}