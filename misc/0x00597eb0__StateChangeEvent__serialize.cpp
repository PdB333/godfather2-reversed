// FUNC_NAME: StateChangeEvent::serialize
int __thiscall StateChangeEvent::serialize(void)
{
    // Global stream pointer (likely a singleton from DAT_01205590)
    Stream* gStream = *(Stream**)0x01205590;
    
    // Local variables for serialization buffer
    int count = 2;                      // Number of items? (local_10)
    int* pTypeId = &typeId;             // Points to local type ID (puStack_14)
    int size = 0x10;                     // Expected serialized size? (local_4)
    int typeId = 0x20b;                  // Event type identifier (local_8)
    
    // First call: likely writes the event type or header (no explicit arguments)
    gStream->write();                    // vtable+0x10, first call
    
    // Second call: prepares and writes the count? 
    int offset = (int)this + 2;          // Some field at offset +2 (maybe a state)
    gStream->write();                    // vtable+0x10, second call
    
    // Write three consecutive fields of this object to the stream
    gStream->write((void*)((int)this + 4), &pTypeId, 4);   // Field at +4 (e.g., type)
    gStream->write((void*)((int)this + 8), &count, 4);     // Field at +8 (e.g., count)
    gStream->write((void*)((int)this + 0xC), &offset, 4);  // Field at +0xC (e.g., data)
    
    return 0x10;                         // Return the size of the serialized structure
}