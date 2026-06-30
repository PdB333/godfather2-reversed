// FUNC_NAME: SimObject::~SimObject
// Address: 0x007256d0
// Role: Destructor for SimObject class (EA EARS engine). Releases subsystems, removes from global lists, and chains base destructor.

void __thiscall SimObject::~SimObject(SimObject* this) // this in ecx
{
    int* pId = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x12C); // +0x12C: mId (or ref count)
    SimObjectSubsystem* pSubsystem = reinterpret_cast<SimObjectSubsystem*>(this->field_0x128); // +0x128: mSubsystem pointer
    void* pChild = reinterpret_cast<void*>(this->field_0xDC);                // +0xDC: mChild (some pointer to release)
    int localList[2];                                                         // temporary list for release call
    int dummy;                                                                // unused padding

    // Set vtable pointers for base classes (multiple inheritance fragments)
    this->vtables[0] = &PTR_FUN_00d62380;   // +0x00: main vtable
    this->vtables[0xF] = &PTR_LAB_00d62370; // +0x3C: vtable for base1
    this->vtables[0x12] = &PTR_LAB_00d6236c;// +0x48: vtable for base2
    this->vtables[0x14] = &PTR_LAB_00d62368;// +0x50: vtable for base3

    // Check if the object is still "alive" (mId not null and not a sentinel)
    if (*pId != 0 && *pId != 0x48)
    {
        // Call pre-destroy virtual on subsystem (offset 0x10 from subsystem vtable)
        bool bReleaseChild = (**(bool (__thiscall**)(SimObject*))((*pSubsystem)->vtables + 0x10))(this);

        if (bReleaseChild)
        {
            if (this->field_0xDC != 0)
            {
                // Prepare temporary list and release child
                localList[0] = reinterpret_cast<int>(pChild);
                localList[1] = 0;
                FUN_00408a00(localList, 0); // Likely decRef or release
            }
            // Call post-destroy virtual on subsystem (offset 0xC)
            (**(void (__thiscall**)(SimObject*))((*pSubsystem)->vtables + 0xC))(this);
        }
    }

    // Remove this object from three global lists
    FUN_004086d0(&DAT_0120e93c); // global list1 (g_simObjectList?)
    FUN_004086d0(&DAT_012069d4); // global list2 (g_entityList?)
    FUN_004086d0(&this->field_0xCC); // +0xCC: mLink

    // Unlink/clear list entries
    FUN_00408310(&this->field_0xCC); // +0xCC: mLink
    FUN_00408310(&this->field_0xD4); // +0xD4: mLink2
    FUN_00408310(&this->field_0xDC); // +0xDC: mChild

    // Delete the ID field if it still points to allocated memory
    if (*pId != 0)
    {
        FUN_004daf90(pId); // operator delete on mId
    }

    // Set the vtable pointer for the most base class (before calling base destructor)
    this->vtables[0x14] = &PTR_LAB_00e32854; // +0x50: base vtable

    // Call base destructor (most base class)
    FUN_0046c640(); // likely SimObjectBase::~SimObjectBase
    return;
}