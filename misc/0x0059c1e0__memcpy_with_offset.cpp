// FUNC_NAME: memcpy_with_offset
int __fastcall memcpyWithOffset(void *dest, void *src, int size)
{
    _memcpy(dest, src, size);
    return (int)dest + size;
}