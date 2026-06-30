// FUNC_NAME: SomeClass::computeTotalOffset
float __thiscall SomeClass::computeTotalOffset(void* this, void* other) {
    // Get pointer to a sub-object (e.g., an interface or component) at this+0x58
    void* subObj = *(void**)((int_ptr)this + 0x58);  // sub-object's 'this' pointer
    // From the sub-object's vtable (at this+0x58 -> vtable pointer), call method at vtable offset 0x2C4
    // This method likely returns a float (e.g., GetBaseValue)
    typedef float (__thiscall* GetValueFunc)(void*);
    GetValueFunc getter = *(GetValueFunc*)(*(int_ptr*)subObj + 0x2C4);
    float baseValue = getter(subObj);

    // Add this->fieldC4 (e.g., m_extraOffset) and other->field18 (e.g., m_modifier)
    float thisField = *(float*)((int_ptr)this + 0xC4);   // +0xC4
    float otherField = *(float*)((int_ptr)other + 0x18); // +0x18

    return baseValue + thisField + otherField;
}