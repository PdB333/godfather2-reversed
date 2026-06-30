// FUNC_NAME: BuildingManager::~BuildingManager

void __thiscall BuildingManager::~BuildingManager()
{
    // vtable pointer update to current destructor vtable
    this->vtable = &PTR_FUN_00e39f10; // +0x00

    // Release resource at offset +0x18
    if (this->resourcePtr != 0) { // +0x18
        FUN_009e7530(this->resourcePtr);
    }
    this->resourcePtr = 0; // +0x18

    // Release first shared reference-counted object at +0x1C
    if (this->sharedResource1 != 0) { // +0x1C
        uint32_t* refObj = *(uint32_t**)(this->sharedResource1 + 0x10);
        if (*(short*)(refObj + 1) != 0) {
            if (--*(short*)((int)refObj + 6) == 0) {
                // Call virtual destructor at vtable entry 0 with arg 1
                (**(code**)*refObj)(1);
            }
        }
        FUN_009f01a0(); // Release or unreference shared resource
    }

    // Release second shared reference-counted object at +0x20
    if (this->sharedResource2 != 0) { // +0x20
        uint32_t* refObj = *(uint32_t**)(this->sharedResource2 + 0x10);
        if (*(short*)(refObj + 1) != 0) {
            if (--*(short*)((int)refObj + 6) == 0) {
                (**(code**)*refObj)(1);
            }
        }
        FUN_009f01a0();
    }

    // Release object at +0x14 via virtual destructor
    if (this->someObject != 0) { // +0x14
        (**(code**)**(uint32_t**)this->someObject)(1);
    }

    // Remove list head from singly linked circular list at +0xD8
    int iVar2 = this->listHead; // +0xD8
    if (iVar2 != 0) {
        uint32_t* puVar1 = *(uint32_t**)(iVar2 + 4); // next pointer from head
        if (puVar1 == &this->listHead) { // list empty (self-loop)
            *(uint32_t*)(iVar2 + 4) = this->listTail; // +0xDC
            this->vtable = &PTR_LAB_00e39ea4; // +0xBC, base class vtable
            return;
        }
        // Traverse to find the node whose next points to the head
        uint32_t* puVar3 = (uint32_t*)puVar1[1];
        while (puVar3 != &this->listHead) {
            puVar1 = (uint32_t*)puVar1[1];
            puVar3 = (uint32_t*)puVar1[1];
        }
        puVar1[1] = this->listTail; // update previous node's next to tail
    }

    // Set vtable to base class
    this->vtable = &PTR_LAB_00e39ea4; // +0xBC
}