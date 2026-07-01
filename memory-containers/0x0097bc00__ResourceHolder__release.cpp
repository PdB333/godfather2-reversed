//FUNC_NAME: ResourceHolder::release
void __fastcall ResourceHolder::release(ResourceHolder* this)
{
    // +0x04: handle
    this->handle = 0;
    // +0x00: resource pointer (released via FUN_009c8f10)
    releaseResource(this->resource);
    this->resource = 0;
    // +0x08: count
    this->count = 0;
}