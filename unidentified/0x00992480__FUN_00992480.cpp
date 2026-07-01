// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00992480
// Destructor: cleans up sub-objects, switches vtable chain, and triggers global shutdown
void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to base class vtable for proper virtual dispatch during destruction
    this->m_vtable = &BASE_VTABLE;        // +0x00: vtable pointer
    // Set class descriptor to base class descriptor (common EARS pattern)
    this->m_classDescriptor = &CLASS_DESC_BASE; // +0x18: class descriptor pointer

    // Release sub-objects (likely pointers to dynamically allocated components)
    // Offset +0x24 (param_1[9])
    releaseComponent(this->m_component1);
    // Offset +0x28 (param_1[10])
    releaseComponent(this->m_component2);
    // Offset +0x2C (param_1[0xB])
    releaseComponent(this->m_component3);
    // Offset +0x4C (param_1[0x13])
    releaseComponent(this->m_component4);
    // Offset +0x68 (param_1[0x1A])
    releaseComponent(this->m_component5);

    // Switch to derived class descriptor (likely part of virtual inheritance chain)
    this->m_classDescriptor = &CLASS_DESC_DERIVED; // +0x18

    // Global shutdown flag (likely used by a singleton manager)
    g_engineShutdownFlag = 0; // _DAT_0113093c

    // Perform engine-level shutdown or cleanup
    engineShutdownProcedure(); // FUN_005c0190
}