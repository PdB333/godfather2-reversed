// FUNC_NAME: SomeClass::getValueBasedOnFlag

void __thiscall SomeClass::getValueBasedOnFlag(void *this, uint32_t *outValue)
{
    // Offset 0x4c is a boolean flag (m_flag)
    int32_t flag = *(int8_t *)((uint8_t *)this + 0x4c);
    // g_selectedValuesTable is an array of two uint32 values at 0x00d8ccf4
    *outValue = *(uint32_t *)((uint8_t *)&g_selectedValuesTable + (flag != 0) * 4);
}