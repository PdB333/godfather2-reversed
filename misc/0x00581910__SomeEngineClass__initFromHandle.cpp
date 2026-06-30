// FUNC_NAME: SomeEngineClass::initFromHandle

void SomeEngineClass::initFromHandle()
{
    // Local triple used as a handle container
    int handleParts[3] = {0, 0, 0};

    // Call engine function to resolve a handle (likely returns an object ID or reference)
    int resultHandle = FUN_004265d0(handleParts); // returns something stored at this+0x0C

    this->field_0x0C = resultHandle;               // +0x0C : handle
    this->field_0x10 = this->associatedObject;      // +0x10 : pointer to another object (passed via EDI in calling convention)

    // Call virtual function at offset 8 (vtable index 2) on the associated object
    // This likely performs initialization linking (e.g., attach to parent, increment ref)
    this->associatedObject->vtable[2]();

    // Zero out the first three fields (maybe reference count, state flags, or links)
    this->field_0x00 = 0;   // +0x00
    this->field_0x04 = 0;   // +0x04
    this->field_0x08 = 0;   // +0x08
}