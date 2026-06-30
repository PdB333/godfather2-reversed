// FUNC_NAME: ObjectPool::getHandleOffset
int __thiscall ObjectPool::getHandleOffset(uint handle)
{
    uint original = handle;
    uint base = handle & 0xFFFFFF00;          // clear low byte (flags/type)
    FUN_005da9c0(original, base, 0, base);    // unknown helper; likely validates or updates slot state
    // m_poolBase (eax) and m_offset (edi) are set by caller, representing the pool's start and a base displacement
    return m_offset + ((m_poolBase - original) / 0x28) * 0x28; // align to 0x28 (40) byte element boundary
}