// FUNC_NAME: SmartReference::SetTarget
void __thiscall SmartReference::SetTarget(void* pObj, void* pOther)
{
    // pObj is a reference-counted object with vtable
    // pOther is optional external pointer to attach
    
    // Call virtual method at vtable[2] (offset 8) – likely release previous/clear
    (*(void (__thiscall **)(void*))*((int*)pObj + 2))(pObj);
    
    void* converted = nullptr;
    if (pOther != nullptr)
    {
        converted = QueryInterface(pOther, pObj); // FUN_004265d0: cast/query
    }
    
    InternalAssign(pObj, converted); // FUN_005e1390: set internal pointer
    
    // Store pObj in this's field at +0x0C
    *(void**)((int)this + 0x0C) = pObj;
    
    // Call vtable[2] again – possibly addRef/retain
    (*(void (__thiscall **)(void*))*((int*)pObj + 2))(); // no argument (pObj implicit)
    
    if (pOther != nullptr)
    {
        void* converted2 = QueryInterface(pOther, *(void**)((int)this + 0x0C));
        *(void**)((int)this + 0x10) = converted2; // +0x10
        
        // Call vtable[1] (offset 4) with (pOther, 0) – e.g., attach/initialize
        (*(void (__thiscall **)(void*, void*, int))*((int*)pObj + 1))(pObj, pOther, 0);
        
        // Call vtable[3] (offset 12) – finalize/notify
        (*(void (__thiscall **)(void*))*((int*)pObj + 3))();
    }
    else
    {
        *(void**)((int)this + 0x10) = nullptr;
        
        // Call vtable[3]
        (*(void (__thiscall **)(void*))*((int*)pObj + 3))();
    }
}