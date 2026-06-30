// FUNC_NAME: EARSObject::getObjectId
int EARSObject::getObjectId() {
    // Returns the object identifier stored at offset 0x8 in the object header.
    // This is commonly used for type checking or object referencing.
    return *(int*)((char*)this + 8);
}