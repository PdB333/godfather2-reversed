// FUNC_NAME: EARSClass::getClassID
// Function at 0x004154b0: Returns the class identifier (magic number) for this object type.
// Used for runtime type identification and serialization (likely a hash/FOURCC).
unsigned int EARSClass::getClassID()
{
    return 0xdadb34ae;
}