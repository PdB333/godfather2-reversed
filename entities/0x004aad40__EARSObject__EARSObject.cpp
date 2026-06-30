// FUNC_NAME: EARSObject::EARSObject
void * __thiscall EARSObject::EARSObject(bool isInternalAllocation) {
    // Call base class constructor (EARSObjectBase)
    baseConstructor();

    // If the object was internally allocated (via new), perform additional initialization
    if (isInternalAllocation) {
        // Potentially set up reference counting or register in a global list
        registerObject(this);
    }

    return this;
}