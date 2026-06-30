// FUNC_NAME: ObjectBase::verifyMask
uint ObjectBase::verifyMask(int *this, uint mask)
{
    int unused;
    char result;
    
    result = (**(code **)(*this + 0x10))(mask, &unused);
    return (-(result != '\0') & mask); // returns mask if condition true, else 0
}