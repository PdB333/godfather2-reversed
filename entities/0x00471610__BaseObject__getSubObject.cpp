// FUNC_NAME: BaseObject::getSubObject
// Function at 0x00471610: Returns this + 0xD0. Used extensively as a getter for a sub-object pointer at offset 0xD0.
// This is likely a member function of a base class, returning a pointer to a member located at offset 0xD0 from 'this'.
int __fastcall getSubObject(int thisPtr)
{
    // Return pointer to sub-object (offset 0xD0 from this)
    return thisPtr + 0xD0;
}