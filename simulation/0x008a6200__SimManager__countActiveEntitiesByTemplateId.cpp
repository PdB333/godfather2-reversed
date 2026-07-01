// FUNC_NAME: SimManager::countActiveEntitiesByTemplateId
short __thiscall SimManager::countActiveEntitiesByTemplateId(void* this, int templateId)
{
    int iVar1;
    short count = 0;
    Iterator localIterator; // Initialize iterator for object list

    // Initialize iterator: begin() call, sets start and end positions
    FUN_004bab20(&localIterator, this, templateId);

    // Iterate through all objects in the list
    while ((localIterator.current != 0) || (localIterator.end != 0)) {
        // Get current object pointer from iterator (dereference function pointer)
        iVar1 = (*(code *)*localIterator.current)();

        // Check if object is active (bit 0 of +0x1c) and matches given template ID (+0x10)
        if (((*(byte *)(iVar1 + 0x1c) & 1) != 0) && (*(int *)(iVar1 + 0x10) == templateId)) {
            count = count + 1;
        }

        // Advance iterator to next object (operator++ via function pointer)
        (*(code *)localIterator.next)();
    }

    return count;
}