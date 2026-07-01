// FUNC_NAME: Entity::activate
// Function address: 0x008d9890
// Role: Activates the entity, initializing components and returning a pointer to the parent object.
// Offsets:
//   +0x190 (400): bool m_isActivated (guard flag)
//   +0x1b0 (432): void* m_pSubObject (pointer to a sub-object, parent at offset -0x48)
//   +0x25c (604): uint32_t m_activationFlags (bitfield, ORed with 1 or 2)
//   +0x224 (548): void* m_pEventTarget (pointer to an event target, sentinel 0x48)
//   +0x198 (408): void* m_pResource (pointer to a resource to release)
//   +0x204 (516): void* m_pComponent (pointer to a component to clear)

int __thiscall Entity::activate(void* thisPtr, char enable)
{
    int* parentPtr;
    struct {
        int field0;
        int field4;
        char field8;
    } eventData;

    // Guard against re-entry
    if (*(char*)((int)thisPtr + 0x190) != '\0')
        goto return_parent;

    *(char*)((int)thisPtr + 0x190) = 1;

    // If sub-object pointer is valid and not sentinel 0x48, call its parent's virtual function at vtable+0x14
    if (*(int*)((int)thisPtr + 0x1b0) != 0 && *(int*)((int)thisPtr + 0x1b0) != 0x48)
    {
        if (*(int*)((int)thisPtr + 0x1b0) == 0)
            parentPtr = (int*)0;
        else
            parentPtr = (int*)(*(int*)((int)thisPtr + 0x1b0) - 0x48);
        (**(code**)(*parentPtr + 0x14))(); // call parent's onActivate
    }

    // Set activation flags: OR with 1 if enable==false, OR with 2 if enable==true
    *(uint32_t*)((int)thisPtr + 0x25c) |= (enable != '\0') + 1;

    // Handle event target
    if (*(int*)((int)thisPtr + 0x224) == 0 || *(int*)((int)thisPtr + 0x224) == 0x48)
    {
        goto handle_event;
    }
    else if (enable != '\0')
    {
        FUN_007281f0(); // some event handler
        goto handle_event;
    }

handle_event:
    if (enable != '\0')
    {
        eventData.field0 = DAT_0112b38c; // global constant
        eventData.field4 = 0;
        eventData.field8 = 0;
        FUN_00408a00(&eventData, 0); // send activation event
    }

    // Release resource if present
    if (*(int*)((int)thisPtr + 0x198) != 0)
    {
        FUN_005e6660(*(int*)((int)thisPtr + 0x198)); // release resource
        *(int*)((int)thisPtr + 0x198) = 0;
    }

    // Clear component if present
    if (*(int*)((int)thisPtr + 0x204) != 0)
    {
        FUN_004df600(); // clear component
    }

return_parent:
    // Return pointer to parent object (sub-object base minus 0x48)
    if (*(int*)((int)thisPtr + 0x1b0) != 0)
        return *(int*)((int)thisPtr + 0x1b0) - 0x48;
    return 0;
}