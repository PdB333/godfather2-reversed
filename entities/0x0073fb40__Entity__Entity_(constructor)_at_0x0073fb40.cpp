// FUNC_NAME: Entity::Entity (constructor) at 0x0073fb40
// Role: Initializes an entity object, registers it with the global simulation manager (FUN_0071e270), and sets up flags based on parent entity state.

Entity* Entity::Entity(Entity* parent, EntityData* config)
{
    // Base class constructor call
    BaseEntity::BaseEntity(parent, config);

    // Initialize vtable
    this->vtable = &PTR_LAB_00d63910;  // Class VTable

    // Linked list node fields (offset 0x70 to 0x84)
    this->listNode.next = 0;   // +0x70
    this->listNode.prev = 0;   // +0x74
    this->listNode.data = 0;   // +0x78
    // ... other fields
    this->field_0x7c = 0;      // +0x7c
    this->field_0x80 = 0;      // +0x80
    this->flags = 1;           // +0x84 (initially has bit 0 set)

    // Store the parent pointer from config? or from base? (offset 0x5c)
    int* parentObj = this->field_0x5c;  // +0x5c: some pointer to another object

    // Clear additional flags field
    this->field_0x88 = 0;      // +0x88

    // Get the global simulation manager (FUN_0071e270 returns a pointer to it)
    int* simManager = GetSimManager();  // Returns SimManager* from some global
    int* listNodeFromManager = 0;
    if (simManager != 0) {
        listNodeFromManager = simManager + 0x48 / sizeof(int);  // +0x48 offset to a list node within manager
    }

    // Insert this object's list node into the manager's list (linked list insertion)
    int** listHeadPtr = &this->listNode.next;  // pointer to the next field of our list node
    if (*listHeadPtr != listNodeFromManager) {
        if (*listHeadPtr != 0) {
            ListRemoveNode(listHeadPtr);  // Remove from old list if any (FUN_004daf90)
        }
        *listHeadPtr = listNodeFromManager;  // Point to manager's list node
        if (listNodeFromManager != 0) {
            this->listNode.prev = *(int**)(listNodeFromManager + 4);  // set prev pointer
            *(int**)(listNodeFromManager + 4) = listHeadPtr;  // adjust manager's list head
        }
    }

    // Get the manager object (node - 0x48) and call its init function
    SimManager* managerFromNode = 0;
    if (*listHeadPtr != 0) {
        managerFromNode = (SimManager*)((int)*listHeadPtr - 0x48);
    }
    SimManagerInit(managerFromNode);  // FUN_0071e1d0

    // If we are registered in a manager
    if (*listHeadPtr != 0 && *listHeadPtr != 0x48) {  // Check non-null and non-trivial?
        SimManager* mgr = (SimManager*)((int)*listHeadPtr - 0x48);
        // Call a method on the parent object (offset 0x20 from vtable) passing previous parentObj
        (mgr->vtable[0x20])(parentObj);  // Virtual function at index 0x20 (offset 0x80? Actually 0x20*4=0x80)

        // Copy a flag from manager's internal state
        this->flags |= (int)(managerFromNode->internalFlag);  // +0x116 of manager object

        // Check a specific bit (0x4000?) in manager's flags
        if ((managerFromNode->flags2 & 0x8000) != 0) {  // +0x110, bit 15
            if ((*(int*)(this->field_0x50 + 0x4a4) & 0x40) != 0) {  // +0x50 points to another object, +0x4a4 is a flag
                this->flags |= 4;  // Set bit 2
                // Call a virtual function at index 0x290 (offset 0xA40)
                (this->parentObject->vtable[0x290 / 4])(0, 1);  // +0x290 relative to parent object vtable
            }
            this->flags |= 2;  // Set bit 1
        }

        // Call some update function (FUN_00461290) - twice?
        SomeUpdateFunction();  // FUN_00461290
        SomeUpdateFunction();  // FUN_00461290
    }

    // Check manager again for another flag
    if (*listHeadPtr != 0 && *listHeadPtr != 0x48) {
        SimManager* mgr = (SimManager*)((int)*listHeadPtr - 0x48);
        if (mgr->someHandle != -0x1e98fd1 && mgr->someHandle != 0) {  // +0xA0
            this->flags |= 0x10;  // Set bit 4
        }
    }

    // Set a flag on the object pointed by parentObj (offset 0x5c4)
    int* flagPtr = (int*)(parentObj + 0x5c4 / 4);  // +0x5c4 from parentObj
    *flagPtr |= 2;

    return this;
}