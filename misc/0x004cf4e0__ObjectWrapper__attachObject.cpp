// FUNC_NAME: ObjectWrapper::attachObject
void __thiscall ObjectWrapper::attachObject(BaseObject* obj, int flag)
{
    // Store external object pointer at offset 0 (this->m_pObject)
    this->m_pObject = obj;

    // Call virtual function at vtable+8 (likely initialization step)
    obj->vtable->onBeginAttach();

    if (flag != 0)
    {
        // Call helper that returns a value to store at offset 4 (this->m_extra)
        this->m_extra = FUN_004265d0(flag, this->m_pObject); // unknown helper

        // Call virtual function at vtable+4 (set context/flag with argument and zero)
        obj->vtable->setContext(flag, 0);

        // Call virtual function at vtable+0xc (finalize attachment)
        obj->vtable->onFinishAttach();
    }
    else
    {
        // Clear extra value and finalize without additional setup
        this->m_extra = 0;
        obj->vtable->onFinishAttach();
    }
}