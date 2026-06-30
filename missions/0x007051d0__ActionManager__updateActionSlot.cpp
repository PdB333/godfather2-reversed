// FUNC_NAME: ActionManager::updateActionSlot
undefined1 __thiscall ActionManager::updateActionSlot(ActionManager* this, uint slotIndex, Character* entity, uint forceFlag)
{
    char cVar1;
    uint uVar2;
    uint uVar3;
    int dt;
    int tmp;
    int slotAddr;
    int slotBase;
    int* actionObj;
    
    // Slot structure: each slot is 20 bytes (5 ints) at this+4, index formula: slotIndex*5+5
    int slotOffset = slotIndex * 5 + 5;
    int* slotPtr = (int*)((char*)this + 4 + slotOffset * 4); // Address of the first member of the slot structure?
    // Actually the code does: iVar5 = *(int*)(this+4+slotOffset*4); iVar4 = this + slotOffset*4;
    // So the pointer is at (this+4+slotOffset*4), and the slot base address (iVar4) is at (this+slotOffset*4).
    // This implies the slot structure starts at (this+slotOffset*4) and the pointer stored at (this+4+slotOffset*4) is the 2nd int (offset 4) inside the slot.
    // So slot structure: [unknown? (4 bytes)], [pointer (4 bytes)], [more fields...]
    // We'll treat slotAddr as base of the slot structure.
    slotAddr = (int)this + slotOffset * 4;
    int slotPointer = *(int*)((char*)this + 4 + slotOffset * 4); // The stored pointer (iVar5)
    
    // Derived action object: subtract 0x48 to get the owning object
    if (slotPointer != 0) {
        actionObj = (int*)(slotPointer - 0x48);
        if (actionObj == (int*)0x0) {
            actionObj = nullptr; // Null check
        }
    } else {
        actionObj = nullptr;
    }
    
    // If no action object (or null derived), proceed with initialization path
    if (actionObj == nullptr) {
        // Reset some state
        FUN_007014d0(0);
        FUN_00702b20(*(int*)((char*)this + 0xf0)); // Deactivate current action? param = this->field_0xf0
        
        // Update aiming/angle bits on entity based on a flag
        if (*(char*)((char*)this + 0xf4) == '\0' && ((*(int*)((char*)entity + 0x2d8) >> 6 & 1) == 0)) {
            *(int*)((char*)entity + 0x2d8) &= ~(1 << 5); // Clear bit 5 (aiming? cover?)
        } else {
            *(int*)((char*)entity + 0x2d8) |= 1 << 5; // Set bit 5
        }
        FUN_00704ca0(entity); // Update animation/state
        
        // Set slot timer values
        if (*(uint*)(slotAddr + 0x10) < 2) {
            *(uint*)(slotAddr + 0xc) = *(uint*)(slotAddr + 0x10);
        } else {
            *(uint*)(slotAddr + 0xc) = 1;
        }
        FUN_00704590(entity); // Update physics?
        
        // If there is a context object (this->0xf0)
        if (*(int*)((char*)this + 0xf0) == 0) {
            goto LAB_007053d6;
        } else {
            cVar1 = FUN_00481640(); // Is game running?
            if (cVar1 == '\0') goto LAB_007053d6;
            int contextAddr = *(int*)((char*)this + 0xf0);
            int contextObj = (contextAddr != 0) ? (contextAddr - 0x48) : 0;
            if (contextObj != (int)entity) goto LAB_007053d6;
        }
        FUN_00707ea0(); // Finalize initialization?
    }
    else {
        // There is an existing action object
        cVar1 = FUN_00704920(entity, actionObj); // Can action be applied?
        if ((cVar1 == '\0') && ((*(byte*)((char*)entity + 0x1d4) & 1) == 0)) { // Not a special case
            uVar2 = FUN_00701340(); // Current time?
            uVar3 = FUN_00701360(); // Action duration?
            if (uVar2 < uVar3) {
                dt = FUN_007013c0(); // Get delta time
                // Virtual call: actionObj->vtable+0x178 -> tick action
                (*(void (__thiscall**)(Character*))(*(int*)*actionObj + 0x178))(entity);
                int newDt = FUN_007013c0();
                if (dt < newDt) {
                    cVar1 = FUN_00481620(); // Check if player controlled? (maybe in combat)
                    if (cVar1 != '\0') {
                        FUN_0093aaa0(newDt - dt, slotIndex); // Log delta?
                    }
                }
                // Check if entity has flag (shooting/action state)
                if ((*(int*)((char*)entity + 0x1d0) >> 6 & 1) != 0) {
                    FUN_00707ec0(); // Some effect
                    FUN_004a91e0(*(int*)((char*)entity + 0x298)); // Play sound/spawn fx (weapon?)
                    FUN_00707ed0(*(int*)((char*)this + 0xf0)); // Update context state
                }
                *(int*)((char*)entity + 0x1d0) &= ~(1 << 1); // Clear bit 1
                FUN_004088c0((int)((char*)entity + 0x3c)); // Reset entity timer at +0x3c
                return 0;
            } else {
                FUN_00939df0(slotIndex); // Force end action?
                return 0;
            }
        }
        // If action cannot be applied or entity is in special state
        FUN_007014d0(0);
        FUN_00702b20(*(int*)((char*)this + 0xf0));
        FUN_00705100(actionObj, entity, slotAddr); // Start action on entity
        // Update aiming/angle bits again
        if (*(char*)((char*)this + 0xf4) == '\0' && ((*(int*)((char*)entity + 0x2d8) >> 6 & 1) == 0)) {
            *(int*)((char*)entity + 0x2d8) &= ~(1 << 5);
        } else {
            *(int*)((char*)entity + 0x2d8) |= 1 << 5;
        }
        FUN_00707ed0(*(int*)((char*)this + 0xf0));
        FUN_00707f60(*(int*)((char*)this + 0xf0));
    }
    
    // Common after path: clear the slot's active bit in this->0x114 bitmask
    *(int*)((char*)this + 0x114) &= ~(1 << (slotIndex & 0x1f));
    
LAB_007053f9:
    cVar1 = FUN_00481620(); // In combat?
    if (cVar1 != '\0') {
        cVar1 = FUN_00481660(); // Some condition (e.g., not already in specific state)
        if ((cVar1 == '\0') && (*(uint*)((char*)entity + 0x510) > 1)) { // Entity has weapon type > 1
            if (((*(int*)((char*)entity + 0x1d0) >> 6 & 1) != 0) && ((char)forceFlag != '\0')) {
                uVar6 = FUN_00701720(); // Random value
                uint randomVal;
                cVar1 = FUN_008934e0(uVar6, &randomVal); // Compare probability
                if ((cVar1 != '\0') && ((float)(randomVal & DAT_00e44680) <= DAT_00e44598)) {
                    FUN_0093f6c0(5, slotIndex & 0xffff | (*(int*)((char*)entity + 0x510) << 0x10), 0); // Send event
                }
            }
            FUN_0079f100(0x34, 0); // Play animation 0x34
            FUN_00702120(); // Clear some state
        }
    }
    return 1;
}