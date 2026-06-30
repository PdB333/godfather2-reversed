// FUNC_NAME: ResourceHolder::release
void __fastcall ResourceHolder::release()
{
    // Release the resource at offset +0x10
    if (this->resource != 0) {
        resourceFree(this->resource);
    }
    // Call the release function on the target at offset +0x00
    if (this->target != 0) {
        this->releaseFunc(this->target);
    }
}