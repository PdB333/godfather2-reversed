// FUNC_NAME: BaseObject::destroy
// Function address: 0x0081ab20
// Role: Releases a child object (if present) then calls virtual destructor.
// This is a common pattern for objects that own a single child via a pointer at +0x04.

struct BaseObject {
    void** vtable;       // +0x00
    BaseObject* child;   // +0x04

    // Virtual function table layout:
    // +0x00: (unknown)
    // +0x04: void release(int flag)
    // +0x08: (unknown)
    // +0x0C: void destructor()
};

void __thiscall BaseObject::destroy() {
    if (this->child != 0) {
        // Call virtual release on child with flag 0
        typedef void (__thiscall* ReleaseFunc)(BaseObject*, int);
        ReleaseFunc release = (ReleaseFunc)(this->child->vtable[1]); // offset 4
        release(this->child, 0);
        this->child = 0;
    }

    // Call virtual destructor (offset 0xC)
    typedef void (__thiscall* DestructorFunc)(BaseObject*);
    DestructorFunc destructor = (DestructorFunc)(this->vtable[3]); // offset 0xC
    destructor(this);
}