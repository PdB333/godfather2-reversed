// FUNC_NAME: NodeBase::NodeBase
void __thiscall NodeBase::NodeBase(NodeBase* this, unsigned int param2, unsigned int param3)
{
    this->vtable = (void**)&NodeBase_vtable; // +0x00: virtual table pointer
    this->flags1 = 0;                         // +0x04: unknown (likely flags or counter)
    this->flags2 = 0;                         // +0x08: unknown (likely flags or counter)
    this->storedValue1 = param3;              // +0x0C: first parameter stored
    this->storedValue2 = param2;              // +0x10: second parameter stored
}