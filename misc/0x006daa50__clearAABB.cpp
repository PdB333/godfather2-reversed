// FUNC_NAME: clearAABB
void __fastcall clearAABB(void* p)
{
    // Zero-initializes an axis-aligned bounding box (two 4-float vectors at offsets 0x10 and 0x20)
    // This is called from various class constructors to reset a member AABB.
    *(int32_t*)((char*)p + 0x10) = 0; // minX (or vector 0)
    *(int32_t*)((char*)p + 0x14) = 0; // minY
    *(int32_t*)((char*)p + 0x18) = 0; // minZ
    *(int32_t*)((char*)p + 0x1c) = 0; // minW (padding)
    *(int32_t*)((char*)p + 0x20) = 0; // maxX (or vector 1)
    *(int32_t*)((char*)p + 0x24) = 0; // maxY
    *(int32_t*)((char*)p + 0x28) = 0; // maxZ
    *(int32_t*)((char*)p + 0x2c) = 0; // maxW (padding)
}