// FUNC_NAME: EARSObject::~EARSObject

struct EARSObjectVTable {
    void (*unknown0)();
    void (*release)(void*, int); // vtable[1]
    void (*unknown2)();
    void (*baseDestructor)(void*); // vtable[3]
};

struct EARSObject {
    EARSObjectVTable* vtable; // +0x00
    void* child; // +0x04
};

void __fastcall EARSObject::~EARSObject(void* this) {
    EARSObject* obj = (EARSObject*)this;
    if (obj->child != 0) {
        obj->vtable->release(obj->child, 0);
        obj->child = 0;
    }
    obj->vtable->baseDestructor(this);
}