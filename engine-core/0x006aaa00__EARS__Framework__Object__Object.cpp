// FUNC_NAME: EARS::Framework::Object::Object
undefined4 __thiscall EARS::Framework::Object::Object(undefined4 this, byte allocFlag)
{
    // Call base class constructor (likely EARS::Object or core class init)
    FUN_006aa570();
    
    // If this object was allocated via operator new (allocFlag & 1), 
    // perform additional post-construction steps (e.g., register with a manager)
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}