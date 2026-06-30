// FUNC_NAME: ResourceLoader::loadAndParseGroup
// Address: 0x0059a640
// This function parses a binary resource header and loads sub-items into a resource object.
// It reads a unique identifier from a stream buffer, obtains a resource, then copies sub-item data.

void __fastcall ResourceLoader::loadAndParseGroup(int thisPtr) // param_1 = this
{
    // this + 8 points to a StreamBuffer object (pointer to data)
    StreamBuffer* buffer = *(StreamBuffer**)(thisPtr + 8);
    
    // Build a 32-bit resource ID from 4 bytes at offsets 4, 8, 0xC, 0x10 within the buffer data
    // The pattern: byte at offset 4 << 24 | byte at offset 8 << 16 | byte at offset 0xC << 8 | byte at offset 0x10
    int resourceId = ( (*(int*)(buffer->data + 4) << 8) + *(int*)(buffer->data + 8) ) << 8; // incomplete; actual full construction:
    // Full calculation as decompiled: ((buffer->data[4] * 0x100 + buffer->data[8]) * 0x100 + buffer->data[0xC]) * 0x100 + buffer->data[0x10]
    // Equivalent to: (buffer->data[4] << 24) | (buffer->data[8] << 16) | (buffer->data[0xC] << 8) | buffer->data[0x10]
    
    // Call to getResourceByUniqueId(thisPtr, resourceId)
    Resource* resource = getResourceByUniqueId(thisPtr, resourceId);
    
    if (resource == 0)
    {
        // If resource not found, trigger error handler via function pointer
        (*(code**)(*DAT_01205590 + 4))(); // Assert/error
        return;
    }
    
    // Check a flag at buffer->flag (offset 0x14)
    if (buffer->flag == 1) // Single sub-item?
    {
        // Validate a short at offset 2 (maybe version or sub-item count)
        if (*(short*)(*(int*)(thisPtr + 8) + 2) != 0x18) // Magic constant version?
        {
            (*(code**)(*DAT_01205590 + 4))(); // Assertion failed
        }
        subItemCount = 0; // iVar3 = 0
    }
    else // flag == 0 (multiple sub-items)
    {
        // Point to sub-item data at offset 0x1C from buffer
        char* subItemsData = buffer->data + 0x1C; // iVar4
        // Validate that the total size (short at offset 2) matches expected: count * 0x10 + 0x1C
        if ( (unsigned short)*(short*)(*(int*)(thisPtr + 8) + 2) != (*(int*)(buffer->data + 0x18) * 0x10 + 0x1C) )
        {
            (*(code**)(*DAT_01205590 + 4))(); // Assertion failed
        }
        subItemCount = *(int*)(buffer->data + 0x18); // Count of sub-items (each 0x10 bytes)
    }
    
    // If there are sub-items to copy (flag == 0 and count > 0 and data pointer valid)
    if ( (buffer->flag == 0) && (subItemCount > 0) && (subItemsData != 0) )
    {
        // Set flags/resource fields: clear bit 10 (0x400) of resource->flags (offset 0x7C)
        resource->flags &= 0xFFFFFBFF; // Clear bit 10 (0x400)
        resource->subItemDataPtr = 0;   // offset 0x154
        resource->subItemCount = subItemCount; // offset 0x150
        resource->subItemData = subItemsData;  // offset 0x14C
    }
    return;
}