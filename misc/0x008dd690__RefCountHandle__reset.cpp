// FUNC_NAME: RefCountHandle::reset
void __fastcall RefCountHandle::reset(void)
{
    this->refCount = 0;              // +0x04: reference count
    FUN_009c8f10(this->ptr);         // release existing pointer (if any)
    this->ptr = nullptr;             // +0x00: owned pointer
    this->flags = 0;                 // +0x08: state flags
}