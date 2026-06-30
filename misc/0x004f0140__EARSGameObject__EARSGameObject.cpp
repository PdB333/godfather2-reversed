// FUNC_NAME: EARSGameObject::EARSGameObject
// Address: 0x004f0140
// Constructor for a game object in EA EARS engine.
// param_2 likely a template/blueprint pointer (with flags at +0xc/+0xd)
// unaff_EDI is passed in EDI register, possibly an attributes/properties block.
// Calls base class constructor, then sets vtable, then processes template.

EARSGameObject* __thiscall EARSGameObject::EARSGameObject(EARSGameObject* this, int param_2, void* param_edi)
{
    int iVar1;
    int local_2c;
    
    // Call base class constructor (likely EARSObject or similar)
    baseConstructor();
    
    // Set vtable pointer (derived class)
    this->vtable = &EARSGameObject_vtable;
    
    // Initialize field at offset 0x24 (9th int) to 0
    this->field_0x24 = 0;
    
    // Check flag at param_2+0xd (0 = not processed yet)
    if (*(char*)(param_2 + 0xd) == 0) {
        // Access internal pointer at offset 0x4 from this (param_1[1])
        // This pointer likely points to some shared data (e.g., game object manager)
        iVar1 = *(int*)(*(int*)((char*)this + 4) + 0xc4);
        
        // Determine if a template object is valid (local_2c may be index or pointer)
        if ((iVar1 == 0) ||
            ((local_2c = iVar1 - 0x48, local_2c != 0 && (*(int*)(iVar1 + 0x11c) == 0)))) {
            local_2c = 0;
        }
        
        // Store the parameter from EDI into field at 0x24
        this->field_0x24 = param_edi;
        
        // Perform three initialization steps (e.g., setup resources)
        initStep();
        initStep();
        initStep();
        
        // If no valid template, mark param_2 as constructed and return
        if (local_2c == 0) {
            *(char*)(param_2 + 0xc) = 1;
            return this;
        }
        
        // Otherwise, call a more detailed constructor with many arguments
        // param_1 + 0x10 is likely a transform/position from internal pointer
        // local_2c + 0x54 is offset into template data
        // param_edi fields are interpreted as properties
        detailedConstructor(
            this,
            *(int*)(*(int*)((char*)this + 4) + 0x10),  // position/transform from manager
            local_2c + 0x54,                            // template data offset
            *(int*)param_edi,                            // property block+0x00
            *(int*)((char*)param_edi + 4),               // property block+0x04
            CONCAT44(*(int*)((char*)param_edi + 36), *(int*)((char*)param_edi + 8)), // two 32-bit values combined
            *(longlong*)((char*)param_edi + 0x4c),       // 64-bit value at offset 0x4c
            *(int*)((char*)this + 0x10),                 // this->field_0x10
            *(int*)((char*)this + 0x14)                  // this->field_0x14
        );
    }
    
    return this;
}