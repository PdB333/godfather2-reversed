// FUNC_NAME: Entity::setDataBlock
void __thiscall Entity::setDataBlock(void* this_ptr, uint64_t* dataPtr) // param_1 = this, param_2 = dataPtr
{
    // Copy 8 bytes from dataPtr into field at +0x60 (likely a 64-bit integer or pointer)
    *(uint64_t*)((int)this_ptr + 0x60) = *dataPtr;

    // Copy next 4 bytes (offset 8 from dataPtr) into field at +0x68 (32-bit integer)
    *(uint32_t*)((int)this_ptr + 0x68) = *(uint32_t*)(dataPtr + 1); // dataPtr + 1 advances by 8 bytes

    // Set bit 0x800 in flags field at +0xA8 (marking something as dirty/updated)
    *(uint32_t*)((int)this_ptr + 0xA8) |= 0x800;
}