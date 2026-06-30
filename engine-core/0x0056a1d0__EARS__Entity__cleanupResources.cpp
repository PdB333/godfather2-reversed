// FUNC_NAME: EARS::Entity::cleanupResources
// Function at 0x0056a1d0: Cleans up three resources at offsets +0x334 (handle), +0x33C (pointer), and +0x338 (pointer). Closes handle, releases resource at +0x33C, then zeroes all fields.

void __fastcall EARS::Entity::cleanupResources(Entity* this)
{
    // Close the handle at +0x334 and zero the field.
    CloseHandle(*(HANDLE*)(reinterpret_cast<uint8_t*>(this) + 0x334));
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x334) = 0;

    // Release the resource at +0x33C via an internal function.
    FUN_009c8f10(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x33C));
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x33C) = 0;

    // Zero the third resource handle at +0x338.
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x338) = 0;
}