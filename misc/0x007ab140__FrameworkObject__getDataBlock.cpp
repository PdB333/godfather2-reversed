// FUNC_NAME: FrameworkObject::getDataBlock
int __fastcall FrameworkObject::getDataBlock(void)
{
    // +0x58: pointer to internal manager or sub-object
    // Returns pointer to a data block at offset 0x26a0 within that manager
    return *(int *)((uint8_t *)this + 0x58) + 0x26a0;
}