// FUNC_NAME: Entity::removeFromGlobalList
void __fastcall Entity::removeFromGlobalList(Entity* this)
{
    // Set vtable to a destroy-stage vtable (first pass)
    this->vtable = (void**)&PTR_FUN_00e37ea0;

    // If a child object exists at offset 0x28 (e.g., a component or sub-object),
    // set a flag at that child's offset 0x10 to mark it for destruction
    if (this->childObject != 0)
    {
        uint32_t* childFlags = (uint32_t*)((uint8_t*)this->childObject + 0x10);
        *childFlags |= 1;
    }

    // Switch vtable to a base or destroyed-class vtable
    this->vtable = (void**)&PTR_FUN_00e37110;

    // If the object is linked into a global list (offset 0x10 / 0x14), remove it
    if (this->listNode != 0)
    {
        // Global list head stored at DAT_01206880 + 0x14
        // The list appears to be a pointer-based stack or linked list using sentinel labels
        int** listHeadPtr = (int**)(*(int*)(DAT_01206880 + 0x14));
        // Write sentinel label into the list head
        *listHeadPtr = (int*)&PTR_LAB_01123be8;
        // Advance list head (each entry takes two 4-byte slots?)
        listHeadPtr++;
        // Write the object's node pointer itself into the list
        *listHeadPtr = (int*)this->listNode;
        listHeadPtr++;
        // Update global list head pointer
        *(int*)(DAT_01206880 + 0x14) = (int)listHeadPtr;
        // Clear the object's list linkage fields
        this->listNode = 0;
        this->listPrev = 0;
    }
}