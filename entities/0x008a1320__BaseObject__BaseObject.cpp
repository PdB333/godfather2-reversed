// FUNC_NAME: BaseObject::BaseObject
BaseObject::BaseObject(byte param_2) {
    // Call base class constructor or initialization function at 0x008a0e40
    baseConstructor();
    // If flag bit 0 is set, perform additional initialization (call at 0x009c8eb0)
    if (param_2 & 1) {
        additionalInit(this);
    }
}