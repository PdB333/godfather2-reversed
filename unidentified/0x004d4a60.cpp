// FUN_NAME: EngineObject::EngineObject
EngineObject * __thiscall EngineObject::EngineObject(EngineObject *this, int unusedParam, int initParam)
{
    // Zero first three DWORDs (likely a linked list node or base info)
    this->field_0x00 = 0;  // +0x00: first DWORD
    this->field_0x04 = 0;  // +0x04: second DWORD
    this->field_0x08 = 0;  // +0x08: third DWORD

    // Call sub-constructor for further initialization
    EngineObject::internalConstruct(this, initParam);  // FUN_004d4a90

    return this;
}