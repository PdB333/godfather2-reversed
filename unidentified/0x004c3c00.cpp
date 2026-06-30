// FUN_004c3c00: LoadableObject::processLoad

void __fastcall LoadableObject::processLoad(LoadableObject* this)
{
    // Base class initialization
    FUN_004c3b40(this);

    // Copy resource identifier from offset +0x30
    int resourceId = *(int*)((char*)this + 0x30);

    // Resolve resource handle from ID
    // local_4 is set by this function (output parameter)
    int resourcePtr;
    FUN_004986e0(&resourceId, &resourcePtr);

    // Check if resource is valid and its +8 field is non-null
    if (resourcePtr != 0 && resourcePtr + 8 != 0)
    {
        int state = *(int*)((char*)this + 0x20); // +0x20: type/state (1 or 2)
        if (state == 1)
        {
            FUN_004c3cc0();
        }
        else if (state == 2)
        {
            FUN_004c3d10(resourcePtr + 8);
        }
    }
    return;
}