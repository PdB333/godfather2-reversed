// FUNC_NAME: ResourceManager::getFieldFromHandle
// Function at 0x00411750: Generic resource lookup that retrieves a field at offset 0x2C from a structure obtained via hash lookup.
// If the lookup (FUN_004025a0) returns non-null, reads a DWORD from result+0x2C and writes to output.
// Otherwise writes the sentinel value 0xFE16702F (likely "not found" or "invalid resource").

void ResourceManager::getFieldFromHandle(uint32_t* outValue, uint32_t handle)
{
    // Attempt to resolve the handle to a resource entry structure.
    // FUN_004025a0 likely performs a hash table lookup.
    uint32_t* entry = reinterpret_cast<uint32_t*>(FUN_004025a0(handle));
    
    if (entry != nullptr)
    {
        // Read the field at offset 0x2C from the entry structure.
        // This field could be an identifier, a type tag, or a data pointer.
        *outValue = *(entry + 0x0B);  // +0x2C in bytes, offset in words = 0x2C/4 = 0x0B
    }
    else
    {
        // Sentinel value indicating no valid result.
        *outValue = 0xFE16702F;
    }
}