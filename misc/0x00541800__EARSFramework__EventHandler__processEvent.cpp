// FUNC_NAME: EARSFramework::EventHandler::processEvent
// Address: 0x00541800
// Role: Dispatches an event to a handler stored in a function pointer table.
// The table is referenced at this+0xd0, and the specific handler is at offset 0x5c within that table.
void __thiscall EARSFramework::EventHandler::processEvent(void* this, void* arg0, void* arg1) {
    // Engine-wide initialization or required preamble for event handling
    FUN_009f2000();

    // Retrieve the function pointer table (e.g., vtable or dispatch array)
    void** tablePtr = *(void***)((char*)this + 0xd0); // +0xd0: pointer to table

    // The handler function pointer is at offset 0x5c within the table (index 23 assuming 4-byte pointers)
    void (*handler)(void*, void*) = (void (*)(void*, void*))tablePtr[0x5c / 4];

    // Invoke the handler with the provided arguments
    handler(arg0, arg1);
}