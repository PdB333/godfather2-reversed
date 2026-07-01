// FUNC_NAME: DebugVariable::DebugVariable
DebugVariable *__thiscall DebugVariable::DebugVariable(DebugVariable *this, char *name, int arg0, int arg1, int arg2) {
    // Call base class constructor (likely DebugVariableBase or similar)
    FUN_0064cc90();
    
    // Set vtable pointer (EARS object vtable)
    this->vtable = (void *)0x00d79bf8; // +0x00
    
    // Copy name into buffer at offset +0x20 (max 63 chars + null)
    strncpy((char *)(this + 8), name, 0x3f); // this+8 offset is 0x20 bytes from start
    // Note: (this + 8) as char* gives address of name buffer
    
    // Initialize fields from constructor parameters
    this->field_0x04 = arg0;   // +0x04
    this->field_0x0C = arg1;   // +0x0C
    this->field_0x08 = arg2;   // +0x08
    
    // Zero out intermediate fields
    this->field_0x10 = 0;      // +0x10
    this->field_0x14 = 0;      // +0x14
    this->field_0x18 = 0;      // +0x18
    
    // Link into global linked list (head stored at DAT_012059ec)
    this->next = s_head;       // +0x1C
    s_head = this;            // update global head
    
    return this;
}

// Global pointer for linked list root
static DebugVariable *s_head = (DebugVariable *)0x012059ec; // DAT_012059ec