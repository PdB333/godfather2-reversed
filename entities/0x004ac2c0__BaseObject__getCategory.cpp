// FUNC_NAME: BaseObject::getCategory
// Function at 0x004ac2c0: Gets a category/type identifier from an object's component chain.
// Returns a uint with low byte indicating presence of a specific component.
uint __fastcall BaseObject::getCategory(BaseObject* this)
{
    // Read pointer to sub-object at +0x48 (likely a child component)
    uint* pSubObj = *(uint**)((char*)this + 0x48);

    // Compute parent of the sub-object (if non-null) by subtracting the offset where it's stored
    BaseObject* parent = (pSubObj != 0) ? (BaseObject*)((char*)pSubObj - 0x48) : 0;

    uint result = (uint)pSubObj & 0xFFFFFF00; // Preserve high 3 bytes of pSubObj

    // Check if parent has a valid pointer at +0x218
    if (parent != 0 && *(void**)((char*)parent + 0x218) != 0)
    {
        // Double dereference: from that pointer, check field at +0x124
        void* innerPtr = *(void**)(*(void**)((char*)parent + 0x218) + 0x124);
        if (innerPtr != 0)
        {
            // Call external function to get a new category value
            return FUN_00572530();
        }
    }

    // If the inner pointer chain failed, set low byte to 1 (flag "present")
    result |= 1;
    return result;
}