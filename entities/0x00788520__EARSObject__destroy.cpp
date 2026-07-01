// FUNC_NAME: EARSObject::destroy
int EARSObject::destroy(byte shouldDelete)
{
    // Check if the sub-object pointer at offset +0x18 is non-null
    if (m_pSubObject != 0)
    {
        // Release the sub-object, e.g., free its memory or decrement reference count
        releaseSubObject(m_pSubObject);
    }

    // If the lowest bit of shouldDelete is set, deallocate this object itself
    if ((shouldDelete & 1) != 0)
    {
        deallocateMemory(this);
    }

    return (int)this;
}