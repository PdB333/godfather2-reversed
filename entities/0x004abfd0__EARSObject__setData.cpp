// FUNC_NAME: EARSObject::setData
// Function at 0x004abfd0: Simple setter for a 4-byte field at offset 0x1c. 
// Likely stores an identifier, pointer, or state value. Called from multiple 
// engine subsystems (animation, object management, etc.).
void __thiscall EARSObject::setData(unsigned int data)
{
    this->field_1C = data; // +0x1c: generic data field
}