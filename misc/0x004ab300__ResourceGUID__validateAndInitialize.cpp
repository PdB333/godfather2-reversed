// FUNC_NAME: ResourceGUID::validateAndInitialize
int __thiscall ResourceGUID::validateAndInitialize(uint32_t* guidData) // offset +0x00: GUID data (4 uint32), offset +0x10: associated handle/refcount
{
    int result = 0;

    // Check if GUID is non-zero and not the "uninitialized" magic value (0xBA5BDBBA, 0xBEEFBEEF, 0xECA15A55, 0x91100911)
    bool isZero = (guidData[0] == 0 && guidData[1] == 0 && guidData[2] == 0 && guidData[3] == 0);
    bool isMagic = (guidData[0] == 0xBA5BDBBA && guidData[1] == 0xBEEFBEEF &&
                    guidData[2] == 0xECA15A55 && guidData[3] == 0x91100911);

    if (!isZero && !isMagic)
    {
        // If the handle/refcount at offset 0x10 has not been initialized yet, resolve and apply the GUID
        if (guidData[4] == 0)
        {
            uint32_t resolvedHandle = resolveGUID(guidData); // FUN_0044ede0 – e.g., hash lookup or string conversion
            applyGUID(resolvedHandle);                       // FUN_004ab5c0 – e.g., store handle or trigger registration
        }
        result = guidData[4];
    }
    return result;
}