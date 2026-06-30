// FUNC_NAME: BaseObject::BaseObject

void __thiscall BaseObject::BaseObject(BaseObject* this)
{
    // Virtual call at vtable[1] (offset 0x04) – likely returns a resource handle or identifier
    int handle = this->vtable->vfunc1();
    
    // Convert handle to internal ID (e.g., resource index, handle->object mapping)
    this->m_internalId = FUN_0060d740(handle);
    
    // Virtual call at vtable[4] (offset 0x10) – post-initialization, e.g., OnCreate()
    this->vtable->vfunc4();
    
    // Insert into global singly linked list (stack-like, prepend)
    this->m_next = g_objectListHead;       // +0x04
    g_objectListHead = this;                // Update global head
    
    // Assign a monotonically increasing instance ID
    g_nextId++;
    this->m_instanceId = g_nextId;          // +0x0C
}