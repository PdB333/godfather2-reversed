// FUNC_NAME: ComplexObject::releaseSubComponent
void __thiscall ComplexObject::releaseSubComponent(int thisPtr)
{
    // Call release on the sub-object at offset +0x1cc0 (likely a member of this class)
    subComponentRelease(thisPtr + 0x1cc0);
}