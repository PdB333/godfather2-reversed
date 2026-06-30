// FUNC_NAME: ResourceHolder::releaseResources
void __thiscall ResourceHolder::releaseResources(int *this)
{
    // Free the secondary resource if present (offset +0x10) using its deleter (offset +0x1C)
    if (this[4] != 0) {
        ((void (*)(void*))this[7])((void*)this[4]);
    }
    // Free the primary resource if present (offset +0x00) using its deleter (offset +0x0C)
    if (this[0] != 0) {
        ((void (*)(void*))this[3])((void*)this[0]);
    }
}