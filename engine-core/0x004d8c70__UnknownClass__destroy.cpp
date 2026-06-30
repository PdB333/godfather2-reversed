// FUNC_NAME: UnknownClass::destroy
int __thiscall UnknownClass::destroy(byte freeMemory)
{
    // +0x14: pointer to child object of same class (possibly inner container)
    UnknownClass* child = *(UnknownClass**)(this + 0x14);
    if (child != 0) {
        // Recursively destroy child with delete flag set
        child->destroy(1);
    }

    if (freeMemory & 1) {
        // Custom deallocation (likely operator delete or pool free)
        FUN_009c8eb0(this);
    }

    return (int)this;
}