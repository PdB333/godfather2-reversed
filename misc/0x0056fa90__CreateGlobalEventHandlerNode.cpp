// FUNC_NAME: CreateGlobalEventHandlerNode
void CreateGlobalEventHandlerNode(SomeObject* obj, int handle)
{
    // Allocate structure of 5 32-bit fields (20 bytes)
    GlobalEventHandlerNode* node = (GlobalEventHandlerNode*)FUN_009c8e50(0x14);
    if (node != nullptr)
    {
        node->m_handle = handle;       // +0x10
        node->m_pObject = obj;         // +0x00
        int local_c = 2;
        int local_8 = 0x10;
        int local_4 = 0;
        // Call first virtual method on obj with handle and a request structure
        int result = obj->vtable->SomeMethod(handle, &local_c);
        node->m_result1 = result;      // +0x08
        node->m_result2 = result;      // +0x0C
        node->m_counter = 0;           // +0x04
        g_globalNode = node;
    }
    else
    {
        g_globalNode = nullptr;
    }
}