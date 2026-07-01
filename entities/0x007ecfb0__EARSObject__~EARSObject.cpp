//FUNC_NAME: EARSObject::~EARSObject
// Address: 0x007ecfb0
// Role: Destructor – releases a resource via virtual function and clears pointer
void __fastcall EARSObject::~EARSObject(void* this)
{
    // Call base class destructor (FUN_007ecdd0)
    FUN_007ecdd0();

    // Call virtual release function (vtable[1]) on the resource at offset +0x18
    // The constant 0x24 likely indicates the size or type of the resource
    (this->vtable[1])(this->field_0x18, 0x24);

    // Clear the resource pointer to prevent double deletion
    this->field_0x18 = 0;
}