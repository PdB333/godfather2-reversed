// FUNC_NAME: ZoneRenderCollision::ZoneRenderCollision
ZoneRenderCollision* __thiscall ZoneRenderCollision::ZoneRenderCollision(ZoneRenderCollision* this, uint param_2, uint param_3)
{
    uint uVar2;
    uint uVar3;
    bool bVar4;

    // Call base class constructor (likely from another class)
    baseConstructor(param_2, param_3);

    // Set primary vtable
    this->vtable = (void*)&VTABLE_ZoneRenderCollision;

    // Set flags at word offset 5 (byte 0x14)
    this->flags |= 0x4000000;

    // Cache global values
    uVar2 = g_globalFlag1;
    uVar3 = g_globalFlag2;

    // Get pointer to sub-object (offset 0x3c from this)
    void* subObj = (void*)(this + 0xf);

    // Set multiple vtable pointers (likely for multiple interfaces)
    this->interfaceVtable[0] = (void*)&VTABLE_ZoneRenderCollision_Interface1; // +0x3c
    this->interfaceVtable[1] = (void*)&VTABLE_ZoneRenderCollision_Interface2; // +0x48
    this->interfaceVtable[2] = (void*)&VTABLE_ZoneRenderCollision_Interface3; // +0x50
    this->interfaceVtable[3] = (void*)&VTABLE_ZoneRenderCollision_Interface4; // +0x54
    this->interfaceVtable[4] = (void*)&VTABLE_ZoneRenderCollision_Interface5; // +0x58

    // Set bit at byte offset 0x15e (in a ushort field)
    *(ushort*)((uint)this + 0x15e) |= 0x80;

    // Check global condition
    bVar4 = (g_conditionFlag == 0);

    // Initialize various fields
    this->field_0x194 = 0;
    *(byte*)((uint)this + 0x19d) = 0;
    this->field_0x1a4 = uVar3;
    this->field_0x1a8 = 0;
    this->field_0x198 = 2;
    *(byte*)((uint)this + 0x19e) = 1;
    *(byte*)((uint)this + 0x19f) = 0;
    *(byte*)((uint)this + 0x1a0) = 0;
    this->field_0x1b0 = uVar2;
    *(byte*)((uint)this + 0x1a1) = 0;
    *(byte*)((uint)this + 0x1a2) = 0;

    // Set field_0x1a4 based on condition
    if (bVar4) {
        this->field_0x1a4 = uVar3;
    } else {
        this->field_0x1a4 = 0;
    }

    // Assign singleton pointer
    this->field_0x1b4 = g_singletonPtr;

    // Register message for zone render collision activation
    uint msgId = resolveMessageId("iMsgZoneRenderCollisionActivated");
    addMessageHandler((void*)&g_messageHandlerGlobal, msgId);

    // Attach child objects to the sub-object if they exist
    if (g_attachedObj1 != 0) {
        attachChildObject(subObj, (void*)g_attachedObj1);
    }
    if (g_attachedObj2 != 0) {
        attachChildObject(subObj, (void*)g_attachedObj2);
    }

    return this;
}