// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(void)
{
    undefined4 *listNode;
    undefined4 *nextNode;

    // Set vtable to base class vtable (0x00d651f8)
    *this = &PTR_LAB_00d651f8;
    // Set component vtable at offset 0x50 (component pointer)
    this[0x14] = &PTR_LAB_00d651f4;

    // Check flags at offset 0xA8 (bitfield)
    if (((uint)this[0x2a] >> 4 & 1) == 0) {
        // Bit 4 clear: perform some manager cleanup with ID 0x43
        SomeManager::cleanup(0x43);
    }
    if (((uint)this[0x2a] >> 7 & 1) != 0) {
        // Bit 7 set: release network-related resources
        releaseNetworkResources();
        releaseOtherResources();
    }
    if (((uint)this[0x2a] >> 10 & 1) != 0) {
        // Bit 10 set: clear flag at subObject+0x564 (0xfffeffff mask)
        *(uint *)(this[0x16] + 0x564) &= 0xfffeffff;
    }
    if (((uint)this[0x2a] >> 8 & 1) != 0) {
        // Bit 8 set: call virtual function 0x290 (maybe stop something) and 0x168
        (**(code **)(*(int *)this[0x16] + 0x290))(1, 0x10);
        (**(code **)(*(int *)this[0x16] + 0x168))();
    }

    // Release two sub-objects if they exist (offset 0xC0 and 0xB0)
    if (this[0x30] != 0) {
        releaseSubObject(this + 0x30);
    }
    if (this[0x2c] != 0) {
        releaseSubObject(this + 0x2c);
    }

    // Change parent component vtable to a derived class's vtable (cleanup phase)
    this[0x14] = &PTR_FUN_00e32808;

    // Clear a linked list starting at offset 0x54
    listNode = (undefined4 *)this[0x15];
    while (listNode != (undefined4 *)0x0) {
        nextNode = (undefined4 *)listNode[1];
        listNode[1] = 0;
        *listNode = 0;
        listNode = nextNode;
    }

    // Global engine shutdown routine
    shutdownGlobalSystem();
    return;
}