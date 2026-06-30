// FUNC_NAME: EARSObject::updateIfActive
void __thiscall EARSObject::updateIfActive(void)
{
    // m_bIsActive at offset +0x70
    if (this->m_bIsActive == false) {
        return;
    }
    // internal update/process function (FUN_00b99fcb)
    this->processInternal();
}