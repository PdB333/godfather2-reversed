// FUNC_NAME: Entity::GetDataPointers
void __thiscall Entity::GetDataPointers(uint32_t* outPointer1, uint32_t* outPointer2) const
{
    // +0x8c: first pointer/uint32 field
    *outPointer1 = *(uint32_t*)(this + 0x8c);
    // +0x90: second pointer/uint32 field
    *outPointer2 = *(uint32_t*)(this + 0x90);
}