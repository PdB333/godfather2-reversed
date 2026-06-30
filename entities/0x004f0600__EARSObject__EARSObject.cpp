// FUNC_NAME: EARSObject::EARSObject
EARSObject * EARSObject::EARSObject(byte flag) {
    // Call base class constructor (FUN_004f02a0) - likely Object::Object()
    baseConstructor();

    // If the lowest bit of flag is set, run a cleanup/deallocation function
    // (FUN_009c8eb0) - possibly operator delete or custom destructor
    if (flag & 1) {
        deallocateConstructor(this);
    }

    return this;
}