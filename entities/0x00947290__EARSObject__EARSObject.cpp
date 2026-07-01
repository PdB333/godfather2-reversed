// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this, undefined4 param) {
    // Initialize sub-object at offset 0x8 with the provided parameter
    // Likely a copy constructor or assignment for a member like m_name or m_data
    initSubObject1(&this->field_0x8, param);
    // Initialize sub-object at offset 0x1c with default values
    // Likely a default constructor for a member like m_transform or m_bounds
    initSubObject2(&this->field_0x1c);
}