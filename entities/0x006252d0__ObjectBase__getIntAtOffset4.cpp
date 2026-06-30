// FUNC_NAME: ObjectBase::getIntAtOffset4
int __fastcall ObjectBase::getIntAtOffset4() const
{
    // Returns the integer value stored at offset +0x04 from this object.
    return *(int*)((char*)this + 4);
}