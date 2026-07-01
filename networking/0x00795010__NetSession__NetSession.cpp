// FUNC_NAME: NetSession::NetSession
// Address: 0x00795010
// Role: Constructor for a network session object (likely base class for connection management)
// Initializes vtable, internal state, sub-object, and callback pointer.

NetSession* __thiscall NetSession::NetSession(NetSession* this, int param2) {
    void* buffer;
    
    // Allocate a packet buffer if param2 is non-zero (e.g., server flag)
    if (param2 != 0) {
        buffer = FUN_00481610(); // Allocate buffer, possibly for packet window
    } else {
        buffer = 0;
    }
    
    // Increment reference count (shared resource management)
    FUN_0064d390(1, 1);
    
    // Set base class vtable (first vtable pointer)
    this->vtable = &PTR_LAB_00e317dc; // Base class vtable
    this->field_0x18 = 0;             // param_1[6] - clear field at +0x18
    
    // Internal initialization with possible buffer
    FUN_00454a10(buffer);
    
    this->field_0x24 = 2;             // param_1[9] - set state to 2 (e.g., ESTABLISHED)
    
    // Override vtable with derived class vtable
    this->vtable = &PTR_LAB_00d6a19c; // Derived vtable
    this->field_0x34 = 0;             // param_1[0xd] - clear field at +0x34
    
    // Set sub-object vtable pointer at +0x28
    this->subObjectVtable = &PTR_LAB_00d6a13c; // param_1[10]
    
    // Set callback function pointer at +0x30
    this->callbackFunction = &LAB_00794040;       // param_1[0xc]
    
    // Configure sub-object with argument 0
    FUN_004a8ec0(0);
    
    // Store self-referencing pointer: point to subObject field (+0x28)
    this->selfRefToSubObject = &this->subObjectVtable; // param_1[5] = param_1 + 10
    
    return this;
}