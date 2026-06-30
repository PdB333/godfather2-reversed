// FUNC_NAME: EntityBase::processMessage
// Address: 0x00590360
// Role: Dispatches a message to a handler based on the type field (bits 0-5) of the object.
// The object's first byte contains a 6-bit type ID. If valid (< 0x23 = 35), calls the corresponding
// function pointer from a global dispatch table. Otherwise returns 0.

// The dispatch table is at DAT_0103afc0, an array of 35 function pointers (indexed by type*4).
// Each handler receives the original parameters: param2..param7 (implementation-specific).

int __thiscall EntityBase::processMessage(byte* thisObj, int param2, int param3, int param4, int param5, int param6, int param7)
{
    int typeId = thisObj[0] & 0x3F;  // Extract 6-bit type from first byte

    if (typeId < 0x23)  // 35 possible types (0..34)
    {
        // Fetch function pointer from global dispatch table
        typedef int (*MessageHandler)(int, byte*, int, int, int, int, int);
        MessageHandler handler = (MessageHandler)(*(int*)(&DAT_0103afc0 + typeId * 4));
        
        // Call handler with the original parameters (note: 'this' is passed as second argument)
        return handler(param2, thisObj, param3, param4, param5, param6, param7);
    }

    return 0;  // Invalid type, no handler
}