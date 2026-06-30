// FUNC_NAME: Entity::~Entity

// Destructor for base Entity class.
// Sets vtable pointers to base class versions, deletes allocated members, removes from lists.
void __thiscall Entity::~Entity(Entity* this)
{
    int* piVar1; // pointer to member at +0xB4
    int* piVar2; // temporary
    undefined4* puVar3; // list walker
    undefined4* puVar4; // list walker
    char cVar5; // debug flag
    int iVar6; // scratch
    int* piVar7; // pointer to something

    // Set vtable to base class (destructor ensures no derived virtual calls)
    this->vtable = &PTR_FUN_00e394d8; // +0x00
    // Set other interface vtables to base class versions
    this->iface1_vtable = &PTR_LAB_00e396f4; // +0x3C (offset 0xF*4)
    this->iface2_vtable = &PTR_LAB_00e39704; // +0x48 (offset 0x12*4)
    this->iface3_vtable = &PTR_LAB_00e39708; // +0x50 (offset 0x14*4)
    this->iface4_vtable = &PTR_LAB_00e39710; // +0x54 (offset 0x15*4)
    this->iface5_vtable = &PTR_LAB_00e39770; // +0x58 (offset 0x16*4)

    // Destroy dynamically allocated member at +0x2B8 (0xAE * 4)
    iVar6 = this->someDynamicPtr; // +0x2B8
    if (iVar6 != 0) {
        // Custom deallocation (likely uses memory pool) with size parameter 8 and a label
        FUN_0040cd70(iVar6, 8, *(undefined4*)(iVar6 - 4), &LAB_0044a000);
        // Destroy the object at (iVar6 - 4) — note the 4-byte header
        FUN_009c8f10(iVar6 - 4);
    }

    // Remove this node from the linked list at +0x2D0 (0xB4*4)
    piVar1 = &this->listNode; // +0x2D0
    this->listNode.next = 0; // +0x2D8? Actually +0xB6 is set to 0 (offset 0xB6*4 = 0x2D8)
    // Check if the node is linked
    if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
        // *piVar1 is the head of list? Actually it's the 'next' pointer of this node
        // If we are about to unlink, and this node's prev points back to the head (piVar1)
        // Get the object that contains this node (offset -0x48 for base pointer)
        if (*piVar1 == 0) {
            piVar7 = (int*)0x0;
        } else {
            piVar7 = (int*)(*piVar1 - 0x48);
        }
        // Call virtual function (offset 0x1c) on that object
        (**(code**)(*piVar7 + 0x1c))(0);
        if (*piVar1 == 0) {
            iVar6 = 0;
        } else {
            iVar6 = *piVar1 - 0x48;
        }
        // Call another virtual function (offset 0x3c then +8)
        (**(code**)(*(int*)(iVar6 + 0x3c) + 8))();

        // Debug/logging: increment counter if debug flag is set
        if ((g_debugFlag != 0) && (cVar5 = FUN_00402080(&g_debugFlag), cVar5 == '\0')) {
            g_debugCounter = g_debugCounter + 1;
            FUN_004084d0(&g_debugFlag, 0x8000);
        }
    }

    // Unlink from doubly linked list at +0x2D0
    iVar6 = *piVar1; // next pointer
    if (iVar6 != 0) {
        piVar7 = *(int**)(iVar6 + 4); // prev pointer of next node
        if (piVar7 == piVar1) {
            // this is head: set head's next to this->next
            *(undefined4*)(iVar6 + 4) = this->listNode.prev; // +0x2D4
        } else {
            piVar2 = (int*)piVar7[1];
            while (piVar2 != piVar1) {
                piVar7 = (int*)piVar7[1];
                piVar2 = (int*)piVar7[1];
            }
            piVar7[1] = this->listNode.prev; // +0x2D4
        }
    }

    // Unlink from another linked list at +0x2B0 (0xAC*4)
    iVar6 = this->otherListNode; // +0x2B0
    if (iVar6 != 0) {
        puVar3 = *(undefined4**)(iVar6 + 4); // prev of next
        if (puVar3 == &this->otherListNode) {
            *(undefined4*)(iVar6 + 4) = this->otherListNode.prev; // +0x2B4
            FUN_0045db70();
            return;
        }
        puVar4 = (undefined4*)puVar3[1];
        while (puVar4 != &this->otherListNode) {
            puVar3 = (undefined4*)puVar3[1];
            puVar4 = (undefined4*)puVar3[1];
        }
        puVar3[1] = this->otherListNode.prev; // +0x2B4
    }

    FUN_0045db70();
    return;
}