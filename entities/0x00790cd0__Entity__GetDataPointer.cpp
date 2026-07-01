// FUNC_NAME: Entity::GetDataPointer
int __thiscall Entity::GetDataPointer()
{
    // +0x9C: object type identifier
    int type = *(int*)(this + 0x9C);

    // 0x48 is a special type (e.g., character or vehicle) that bypasses the global buffer logic
    if (type != 0 && type != 0x48 && IsTypeValid())
    {
        // Valid non-zero, non-0x48 type; returns a global buffer offset by 0x30
        return GetGlobalBufferBase() + 0x30;
    }
    else
    {
        // Default: return pointer to the local buffer at +0x50
        return reinterpret_cast<int>(this + 0x50);
    }
}