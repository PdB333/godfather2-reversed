// FUNC_NAME: Entity::setProperty
void __thiscall Entity::setProperty(int thisPtr, int key, int value)
{
    // Iterate through the property pointer array stored at +0x230 to +0x234.
    // Each element is a pointer to a property structure.
    int **propIter = *(int ***)(thisPtr + 0x230);
    int **propEnd  = *(int ***)(thisPtr + 0x234);
    
    while (propIter != propEnd)
    {
        // +0x30 holds the key (property identifier).
        if (*(int *)(*propIter + 0x30) == key)
        {
            // +0x38 holds the value to set.
            *(int *)(*propIter + 0x38) = value;
            return;
        }
        propIter++;
    }
    // If key not found, silently return without modifying anything.
}