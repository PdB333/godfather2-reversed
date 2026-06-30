// FUNC_NAME: EARSObject::releaseOwnedObject
void __thiscall EARSObject::releaseOwnedObject()
{
    // Save pointer to owned child object at +0x20
    EARSObject* ownedObject = this->ownedObject;
    // Mark this object as released (flag at +0x00 set to 1)
    this->releaseFlag = 1;

    if (ownedObject != nullptr)
    {
        // If the owned object also has a child, release that reference
        if (ownedObject->ownedObject != nullptr)
        {
            releaseChildReference(1); // static helper for grandchild release
        }
        // Free the owned object's memory
        EARS_freeMemory(ownedObject);
    }
    // Clear the pointer to the owned object
    this->ownedObject = nullptr;
}