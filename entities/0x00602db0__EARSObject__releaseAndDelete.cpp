// FUNC_NAME: EARSObject::releaseAndDelete
// This function appears to be a member function (this in ESI) that performs destruction with cleanup.
// It releases two owned sub-objects via vtable[1], calls its own virtual destructor (vtable[3]), then calls a global deallocation function.
// Offsets: +0x00 = vtable pointer, +0x2c = pointer to a sub-object (unknown type), +0x2b = another pointer.
class EARSObject {
public:
    // Virtual table: entry 0 (offset 0) = unknown, entry 1 (offset 4) = release(bool), entry 2 (offset 8) = unknown, entry 3 (offset 12) = destructor
    virtual void vtableFunc0();
    virtual void release(bool);
    virtual void vtableFunc2();
    virtual ~EARSObject();

    // Unknown members, but we know at least these pointers exist
    EARSObject* member_0x2c; // +0x2c
    EARSObject* member_0x2b; // +0x2b

    // Custom deallocation (probably operator delete or EARS free)
    static void customDelete(EARSObject* obj);
};

void EARSObject::releaseAndDelete()
{
    // Release first sub-object (if non-null) with parameter 0
    if (this->member_0x2c != 0) {
        this->member_0x2c->release(0);
    }
    // Release second sub-object (if non-null) with parameter 0
    if (this->member_0x2b != 0) {
        this->member_0x2b->release(0);
    }
    // Call virtual destructor (vtable[3]) – likely destroys this object
    this->~EARSObject();
    // Global deallocation (mapped from FUN_009c8eb0)
    customDelete(this);
}