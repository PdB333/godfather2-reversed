// FUNC_NAME: Object::IsActive
uint32_t __thiscall Object::IsActive(void)
{
    // Check the lowest bit of flags at +0x04
    return *(uint32_t *)((uint8_t *)this + 4) & 1;
}