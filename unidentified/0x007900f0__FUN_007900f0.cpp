// FUNC_NAME: SomeComponent::modifyReferenceCount (at 0x007900f0) - increments or decrements reference count at offset 0x74 based on param_2
void __thiscall SomeComponent::modifyReferenceCount(bool increment)
{
    int *refCount = reinterpret_cast<int*>(this + 0x74); // +0x74: reference count field
    if (increment)
    {
        *refCount += 1;
    }
    else
    {
        *refCount -= 1;
    }
}