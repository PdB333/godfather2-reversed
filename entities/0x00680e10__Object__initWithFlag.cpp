// FUNC_NAME: Object::initWithFlag
// Function at 0x00680e10
// Initializes the object and optionally calls its destructor if the low bit of flag is set.
// Used for placement-new or object pool reuse with conditional cleanup.

undefined4 __thiscall Object::initWithFlag(byte destroyFlag) {
    globalInit(); // +0x00: Global initialization (e.g., reference count bump)
    if ((destroyFlag & 1) != 0) {
        destructor(this); // +0x04: Calls destructor if flag bit0 is set
    }
    return (undefined4)this;
}