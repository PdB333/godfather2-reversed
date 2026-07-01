//FUNC_NAME: Entity::setGuidAndType
void __thiscall Entity::setGuidAndType(Entity* this, const GuidAndType* data)
{
    // Copy 8-byte GUID to offset +0x60
    *(uint64*)((uint8*)this + 0x60) = data->guid;
    // Copy 4-byte type to offset +0x68
    *(uint32*)((uint8*)this + 0x68) = data->type;
}