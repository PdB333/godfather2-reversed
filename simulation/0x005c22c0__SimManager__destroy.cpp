// FUNC_NAME: SimManager::destroy
void __thiscall SimManager::destroy(SimManager* this)
{
    // offset +0x00: vtable pointer
    // offset +0x04: pointer to something (free'd at end)
    // offset +0x08: pointer to something (set to 0)
    // offset +0x0C: pointer to something (set to 0)
    // offset +0x10: array of component pointers
    // offset +0x14: number of components
    // offset +0x18: some count (set to 0)
    // Component structure:
    //   +0x00: vtable
    //   +0x10: function pointer? (called at end with arg 1)
    //   +0x14: ? (free'd)
    //   +0x18: ? 
    //   +0x1C: ?
    //   +0x20: ?
    //   +0x24: ?
    //   +0x28: ?
    //   +0x2C: ?
    //   +0x4A: flags (bit 1 = active)

    this->vtable = &g_SimManagerVTable;  // PTR_FUN_00e3e880

    int componentCount = this->componentCount;  // +0x14
    if (componentCount > 0)
    {
        for (int i = 0; i < componentCount; i++)
        {
            Component* comp = this->components[i];  // +0x10 array

            // Check if component is active (bit 0x2 at +0x4A)
            if ((comp->flags & 0x2) != 0)
            {
                // Pre-destroy callback?
                unknownFunction1();

                // Free memory pointed by comp->field_0x28
                void* field28 = comp->field_0x28;
                comp->field_0x30 = 0;
                comp->field_0x2C = 0;
                if (field28 != 0)
                {
                    g_MemoryManager->free(field28, 0);
                }
                comp->field_0x28 = 0;

                // Call virtual destructor at vtable+0x04
                comp->vtable->destroy();

                // Clear fields
                comp->field_0x20 = 0;
                comp->field_0x24 = 0;
                comp->field_0x1C = 0;
                comp->field_0x18 = 0;

                // Free memory pointed by comp->field_0x14
                void* field14 = comp->field_0x14;
                if (field14 != 0)
                {
                    g_MemoryManager->free(field14, 0);
                }
                comp->field_0x14 = 0;

                // Remove component from global component list
                ComponentList* globalList = getGlobalComponentList();
                if (globalList != 0)
                {
                    int listCount = globalList->count;  // +0x0C
                    if (listCount > 0)
                    {
                        void** listArray = globalList->array;  // +0x08
                        for (int j = 0; j < listCount; j++)
                        {
                            // Compare with comp + 0x10 (pointer to field at offset 0x10)
                            if (listArray[j] == &comp->field_0x10)
                            {
                                listArray[j] = 0;
                                break;
                            }
                        }
                    }
                }

                // Clear the active flag
                comp->flags &= 0xFFFD;
            }

            // Call function at comp->field_0x10 (offset 0x10 from component start)
            // This likely is a release/cleanup function, passing 1 as argument
            comp->field_0x10->someFunc(1);
        }
    }

    // Clean up internal arrays
    this->field_0x18 = 0;
    this->componentCount = 0;
    if (this->components != 0)
    {
        g_MemoryManager->free(this->components, 0);
    }
    this->components = 0;
    this->field_0x0C = 0;
    this->field_0x08 = 0;
    if (this->field_0x04 != 0)
    {
        g_MemoryManager->free(this->field_0x04, 0);
    }

    // Remove this manager from global list
    ComponentList* globalList = getGlobalComponentList();
    if (globalList != 0)
    {
        int listCount = globalList->count;
        if (listCount > 0)
        {
            void** listArray = globalList->array;
            for (int j = 0; j < listCount; j++)
            {
                if (listArray[j] == this)
                {
                    listArray[j] = 0;
                    break;
                }
            }
        }
    }

    // Second cleanup (likely redundant)
    this->field_0x18 = 0;
    this->componentCount = 0;
    if (this->components != 0)
    {
        g_MemoryManager->free(this->components, 0);
    }
    this->components = 0;

    // Final deallocation?
    unknownFunction2();
}