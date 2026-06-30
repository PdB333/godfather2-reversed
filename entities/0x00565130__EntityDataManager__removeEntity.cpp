// FUNC_NAME: EntityDataManager::removeEntity

void __fastcall EntityDataManager::removeEntity(int this)
{
    uint count = *(uint *)(this + 0x124);
    if (count == 0)
        return;

    // Find the entity in the list by matching ID at offset 0x3C
    int **iter = (int **)(this + 0x24);
    uint index = 0;
    while (*(int *)(*iter + 0x3C) != *(int *)(unaff_EDI + 0x3C))
    {
        ++index;
        ++iter;
        if (count <= index)
            return; // Not found
    }

    // Remove the entity from the array (swap with last element if not last)
    if (index < count - 1)
    {
        *(int **)(this + 0x24 + index * 4) = *(int **)(this + 0x20 + count * 4);
    }
    --(*(uint *)(this + 0x124));

    // Destroy the entity's children (child1 at +0x24, child2 at +0x14)
    if (*(int *)(unaff_EDI + 0x24) != 0)
    {
        // Call function pointer at +0x30 with child1 as argument
        (*(void (**)(void *))(unaff_EDI + 0x30))(*(void **)(unaff_EDI + 0x24));
    }
    if (*(int *)(unaff_EDI + 0x14) != 0)
    {
        // Call function pointer at +0x20 with child2 as argument
        (*(void (**)(void *))(unaff_EDI + 0x20))(*(void **)(unaff_EDI + 0x14));
    }

    // Global cleanup (likely memory or reference counting)
    FUN_009c8eb0();
}