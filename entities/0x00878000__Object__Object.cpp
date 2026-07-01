// FUNC_NAME: Object::Object

struct Object {
    void **vtable;          // +0x00
    void *subObject;        // +0x04  (sub-object pointer, checked before release)
    // additional members follow...
};

// external functions
void releaseSubObject(void *subObj);
void registerObject(Object *obj);

extern void *gObjectVTable; // from data ref PTR_LAB_00e2f0c0

Object * __thiscall Object::Object(Object *this, byte flag)
{
    if (this->subObject != 0) {
        releaseSubObject(this->subObject);
    }
    this->vtable = &gObjectVTable;
    if ((flag & 1) != 0) {
        registerObject(this);
    }
    return this;
}