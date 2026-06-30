// FUNC_NAME: EARS::Framework::BaseObject::destroy
int __thiscall BaseObject::destroy(unsigned char flags)
{
    // +0x0C: pointer to a child object
    // +0x18: function pointer for child object's destruction
    if (m_childObject != 0) {
        m_childDestructor(m_childObject);
    }
    if ((flags & 1) != 0) {
        memFree(this); // likely operator delete / custom deallocator at FUN_009c8eb0
    }
    return this;
}