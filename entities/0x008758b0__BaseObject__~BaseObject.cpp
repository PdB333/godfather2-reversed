// FUNC_NAME: BaseObject::~BaseObject

void __thiscall BaseObject::~BaseObject(BaseObject *this)
{
    // Destructor: free two pointer members at +4 and +12, then set vtable to sentinel.
    if (this->member_at_12 != 0) { // param_1[3] (offset 12)
        releaseResource(&this->member_at_12);
    }
    if (this->member_at_4 != 0) { // param_1[1] (offset 4)
        releaseResource(&this->member_at_4);
    }
    // Set virtual function table pointer to a special sentinel (likely marking object as destroyed)
    this->vtablePtr = &PTR_LAB_00e2f0c0; // +0x00
}