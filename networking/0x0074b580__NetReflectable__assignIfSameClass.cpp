// FUNC_NAME: NetReflectable::assignIfSameClass
void __thiscall NetReflectable::assignIfSameClass(NetReflectable *this, NetReflectable *targetObj)
{
    int classId;

    classId = targetObj->vtable->getClassId();  // Virtual function at offset 0
    if (classId != 0xCF840186)                  // Expected class ID (hash or enum)
    {
        handleTypeMismatch(targetObj);          // Call default handler (FUN_0074ad10)
        return;
    }

    // Copy 12 bytes: 8 bytes at +0x74, 4 bytes at +0x7C
    *(uint64_t *)((uint8_t *)targetObj + 0x74) = *(uint64_t *)((uint8_t *)this + 0x74);
    *(uint32_t *)((uint8_t *)targetObj + 0x7C) = *(uint32_t *)((uint8_t *)this + 0x7C);
}