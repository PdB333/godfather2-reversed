// FUNC_NAME: ManagedObject::~ManagedObject
void __fastcall ManagedObject::~ManagedObject(ManagedObject* this)
{
    // First vtable switch to base class destructor phase
    this->vtable = (void*)&BASE_VTABLE_1;           // +0x00
    this->baseVtable = (void*)&BASE_VTABLE_2;       // +0x4C

    // Release manager resource if still held
    if (this->hasManager)                            // +0x80 (bool)
    {
        ReleaseGlobalResource(&g_globalManager);     // FUN_004086d0
        this->hasManager = false;
    }

    // Second vtable switch to final base class
    this->vtable = (void*)&BASE_VTABLE_3;           // +0x00
    this->baseVtable = (void*)&BASE_VTABLE_4;       // +0x4C

    // Destroy embedded sub‑objects (two at +0x58 and +0x68)
    // SubObjectType is small (likely a string or handle)
    SubObjectType* objA = (SubObjectType*)((char*)this + 0x58);
    SubObjectType* objB = (SubObjectType*)((char*)this + 0x68);
    objA->~SubObjectType();                         // FUN_00408310
    objB->~SubObjectType();                         // FUN_00408310

    // Call base class destructor
    BaseClassDestructor();                          // FUN_004083d0

    // Post‑destruction cleanup (e.g., deregister from object list)
    PostDestructCleanup();                          // FUN_008d2680
}