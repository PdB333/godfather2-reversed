// FUNC_NAME: ComponentBase::ComponentBase
// Address: 0x00776020
// Role: Constructor for a component class with embedded sub-object at offset 0x48.
// Calls base class constructor, sets vtable, computes container pointer from embedded object pointer,
// and optionally acquires a resource from a global manager.

void* __thiscall ComponentBase::ComponentBase(ComponentBase* this, void* arg2, void* arg3)
{
    // Call base class constructor (likely a generic object constructor)
    BaseClass::constructor(arg2, arg3);

    // Set vtable pointer for this class
    this->vtable = (void*)0x00d680e8;  // VTable for ComponentBase

    // Offset 0x48: embeddedObjectPtr (pointer to an embedded sub-object)
    // If non-null, compute the container pointer by subtracting the offset of the embedded object
    // within its containing structure (0x48 bytes).
    if (this->embeddedObjectPtr != nullptr)
    {
        // containerPointer = embeddedObjectPtr - sizeof(container header up to embedded object)
        this->containerPointer = this->embeddedObjectPtr - 0x48;
    }
    else
    {
        this->containerPointer = nullptr;
    }

    // Offset 0x50: containerPointer (now set)
    // Offset 0x54: resourceHandle (handle from global manager)
    if (this->containerPointer != nullptr)
    {
        // Acquire resource from global manager (DAT_0112af58) via FUN_0043b870
        this->resourceHandle = acquireResource(g_globalManager);
    }
    else
    {
        this->resourceHandle = nullptr;
    }

    return this;
}