// FUNC_NAME: ResourceManager::releaseAllResources
void ResourceManager::releaseAllResources()
{
    int count = this->resourceCount - 1;
    if (count >= 0)
    {
        int byteOffset = count * 0x70;
        do
        {
            ResourceEntry* entry = reinterpret_cast<ResourceEntry*>(this->resourceArrayBase + byteOffset);
            if (entry->resourcePtr != nullptr)
            {
                FUN_00557020(); // release or dereference resource
                ManagedObject* obj = entry->resourcePtr;
                if (obj->refCount != 0) // offset 4 (short)
                {
                    // decrement reference count at offset 6
                    obj->refCountMinusOne = obj->refCountMinusOne - 1;
                    if (obj->refCountMinusOne == 0)
                    {
                        // virtual destructor with argument 1
                        obj->vtable->destroy(1);
                    }
                }
                entry->resourcePtr = nullptr;
            }
            count--;
            byteOffset -= 0x70;
        } while (count >= 0);
    }

    // call virtual deallocate on the manager's allocator
    this->allocator->vtable->deallocate(this->resourceArrayBase, 0);
    if (this->secondaryArray != nullptr)
    {
        this->allocator->vtable->deallocate(this->secondaryArray, 0);
    }
    this->allocator->vtable->cleanup(); // virtual at offset 0xc
}