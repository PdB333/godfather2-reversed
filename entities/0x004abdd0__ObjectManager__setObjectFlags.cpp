// FUNC_NAME: ObjectManager::setObjectFlags
void __thiscall ObjectManager::setObjectFlags(uint flags)
{
    // this+0x18: pointer to context structure
    Context* ctx = this->m_pContext;
    Object* obj = nullptr;
    if (ctx != nullptr)
    {
        // ctx+0x04: pointer to active object
        obj = ctx->m_pActiveObject;
    }
    if (obj != nullptr)
    {
        // Begin critical section
        lockMutex();                            // FUN_004abd90
        // Resolve the object to apply flags (may return obj itself or different)
        obj = resolveObjectByFlags(flags);      // FUN_004abd50
        if (obj != nullptr)
        {
            // Combine flags into the object's flags field at +0x38
            obj->m_flags |= flags;
        }
    }
}