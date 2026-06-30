// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject* this)
{
    // Default constructor – delegates to the parameterized init with zero defaults.
    // The three zero values likely represent flags, subtype, or initialization state.
    this->init(0, 0, 0);
}