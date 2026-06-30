// FUNC_NAME: FloatProperty::setValue
void __thiscall FloatProperty::setValue(float newValue)
{
    // Compare new value with stored value at +0x10
    if (newValue != m_value)
    {
        // Set dirty flag at +0x28
        m_dirtyFlag = 1;
        // Update the stored value
        m_value = newValue;
    }
}