// FUNC_NAME: TNLReliableStream::init
uint32_t TNLReliableStream::init(uint32_t this)
{
    // Stack temporary values for initializing fields
    uint32_t value1 = 2;                     // Value for field at +0x02
    uint32_t* value2Ptr = &value2Data;       // Points to local data
    uint32_t value2Data = 0x800;             // Data to be stored indirectly? Actually pointer is set
    uint32_t value3 = 0xC;                   // Return value (size of object)
    uint32_t field3Value = 0x800;            // Not used? Actually local_8 holds 0x800
    
    // First virtual call: constructor (vtable[4]) – initializes vtable pointer
    (*(void (*)())(*DAT_01205590 + 0x10))();
    
    // Set field at +0x02 to 2
    field3Value = 2;                         // Overwrite local_8? Actually this will be used for field at +0x08
    (*(void (*)(uint32_t, uint32_t*))(*DAT_01205590 + 0x10))(this + 2, &value1);
    
    // Set field at +0x04 to pointer to value2Data (which is 0x800 on stack)
    (*(void (*)(uint32_t, uint32_t**, uint32_t))(*DAT_01205590 + 0x10))(this + 4, &value2Ptr, 4);
    
    // Set field at +0x08 to 2 (field3Value was set to 2)
    (*(void (*)(uint32_t, uint32_t*, uint32_t))(*DAT_01205590 + 0x10))(this + 8, &field3Value, 4);
    
    return 0xC;  // Size of the structure = 12 bytes
}