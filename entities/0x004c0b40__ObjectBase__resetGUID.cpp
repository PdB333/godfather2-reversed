// FUNC_NAME: ObjectBase::resetGUID
void ObjectBase::resetGUID(void)
{
    // Zero out fields at +0x20 and +0x24 (likely counters or flags)
    *(int32_t *)(this + 0x20) = 0;
    *(int32_t *)(this + 0x24) = 0;

    // Initialize subobject at +0x28 (likely a GUID/RID struct)
    // First call: constructor
    GUID::constructor(this + 0x28);
    // Second call: clear/zero
    GUID::clear(this + 0x28);

    // If the pointer at +0x30 is non-null, it points to a source GUID
    if (*(void ***)(this + 0x30) != (void **)0x0)
    {
        // Extract first DWORD from the source's first field into a temporary GUID
        uint32_t tempGuid[3] = { (***(uint32_t **)(this + 0x30)), 0, 0 };
        // Assign that GUID (with zeros after first DWORD) to something
        GUID::assign(&tempGuid, 0);
    }
}