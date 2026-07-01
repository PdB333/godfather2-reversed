// FUNC_NAME: RefCountedObject::~RefCountedObject
void __fastcall RefCountedObject::~RefCountedObject(RefCountedObject *this)
{
    // Destroy sub-object at offset +0x18 (likely a reference counter or embedded object)
    FUN_008aea70(this + 0x18);
    // Call cleanup routine stored at +0x08 with pointer at +0x10 and flag at +0x14
    // This is a custom deleter pattern: (*(void(**)(void*, char))(&this->deleter))(this->ptr, this->flag);
    this->deleter(this->ptr, this->flag);
}