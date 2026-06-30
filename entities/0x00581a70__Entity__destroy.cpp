// FUNC_NAME: Entity::destroy
void __fastcall Entity::destroy(Entity *this)
{
    // offset +0x64: pointer to a sub-object (likely a child entity or resource)
    Entity *subObject = (Entity *)this->field_0x64;

    // Set vtable to a specific base vtable for cleanup (likely base class)
    this->vtable = (VTablePtr)&PTR_FUN_00e3ac24;

    if (subObject != nullptr)
    {
        // Call release/decRef on the main subObject (vtable+4, first method)
        subObject->release();

        // If there is a second sub-object at offset 0x0C from the first sub-object
        Entity *secondSub = (Entity *)((int *)subObject)[3]; // offset 0x0C
        if (secondSub != nullptr)
        {
            secondSub->release();
        }

        // Call virtual destructor on subObject (vtable+12, third method)
        subObject->destroySubObject();

        // Call memory manager to deallocate subObject
        gMemoryManager->deallocate(subObject);
    }
}