// FUNC_NAME: GangsterNpcRequester::initFromPrototype
void __thiscall GangsterNpcRequester::initFromPrototype(void* thisPtr, void* param1, void* param2, int* prototype) // prototype in EAX
{
    int* this = (int*)thisPtr;
    int uVar4 = *(int*)0x00e2b1a4; // Some global constant (likely 0 or -1)
    int* vtable = *(int**)((int)prototype); // *prototype is vtable or something
    
    // Set up vtable and copy fields from prototype
    this[1] = *prototype; // +0x4 = prototype->field0 (maybe a pointer)
    this[3] = (int)param2; // +0xC
    this[2] = (int)param1; // +0x8
    this[0] = (int)&PTR_FUN_00e380ec; // vtable address
    this[0xd] = uVar4; // +0x34
    this[0xe] = uVar4; // +0x38
    this[0xf] = uVar4; // +0x3C
    this[0x10] = uVar4; // +0x40
    int uVar1 = *(int*)(*prototype + 0x20); // prototype->some field at offset 0x20
    this[0x13] = uVar4; // +0x4C
    this[0x11] = uVar1; // +0x44
    this[0x12] = 0; // +0x48
    this[0x14] = 0; // +0x50
    this[0x15] = 0; // +0x54
    this[0x16] = 0; // +0x58
    this[0x17] = prototype[3]; // +0x5C
    this[0x18] = prototype[4]; // +0x60
    this[0x19] = prototype[5]; // +0x64
    this[0x1a] = prototype[6]; // +0x68
    *(short*)((int)this + 0x6C) = *(short*)((int)prototype + 0x1E); // +0x6C = prototype->field at +0x1E (a short)
    *(short*)((int)this + 0x6E) = (short)prototype[7]; // +0x6E = lower 2 bytes of prototype[7]
    *(char*)((int)this + 0x70) = (char)prototype[8]; // +0x70 = type byte from prototype[8]
    this[4] = prototype[1]; // +0x10 = prototype->field4 (likely another pointer like a config object)
    this[5] = prototype[2]; // +0x14 = prototype->field8
    this[8] = uVar4; // +0x20
    this[9] = uVar4; // +0x24
    this[10] = uVar4; // +0x28
    this[0xb] = uVar4; // +0x2C
    *(short*)((int)this + 0x32) = 0; // +0x32
    *(short*)((int)this + 0x30) = 0; // +0x30 (unaff_ESI + 0xc as short)

    char type = *(char*)((int)this + 0x70); // +0x70 = type
    byte bVar2 = *(byte*)(this[4] + 0x10f); // byte from the config object at +0x10f
    if (type == 6) { // Type 6 indicates something (e.g., gangster NPC)
        int iVar5 = FUN_0050a580(); // Get some manager/player
        this[0x14] = iVar5; // +0x50 = manager pointer
        if (iVar5 == 0) goto LAB_0050e887;
        // Check something in the manager structure
        if (*(int*)(*(int*)(iVar5 + 0x90) + 0x24) == 0) {
            // Check if flag already set
            if ((*(uint*)(this[4] + 0x10c) & 0x1000000) != 0) goto LAB_0050e914;
            goto LAB_0050e887;
        }
        // Set flag on config object
        *(uint*)(this[4] + 0x10c) |= 0x1000000;
    } else {
LAB_0050e887:
        if ((bVar2 & 1) == 0) goto LAB_0050e914;
    }

    // Create child object (e.g., SimNpc)
    void* entityFactory = (void*)FUN_009c8f80(); // Get entity factory singleton
    int local_c[3] = {0, 0, 0}; // Actually local variables used as parameters to factory alloc
    int* local_8 = &local_c;
    // The call: first deref factory, then call function pointer at offset 0 with params: size 0xB0, and pointer to local struct?
    int iVar5 = (**(int(**)(int, int*))*entityFactory)(0xB0, local_8); // Allocate 0xB0 bytes
    if (iVar5 == 0) {
        iVar5 = 0;
    } else {
        iVar5 = FUN_0044daa0(0); // Construct child object (constructor, maybe SimNpc::SimNpc)
    }
    this[0x16] = iVar5; // +0x58 = child object pointer
    // Set flags on child object
    *(uint*)(iVar5 + 0x94) |= 1;
    // Check config flags from this[4] (the config object) at +0x104
    if ((*(byte*)(this[4] + 0x104) & 0x20) != 0) {
        *(uint*)(this[0x16] + 0x94) |= 0x20;
    }
    // Check value at this[1] (the first copied field) +0x1d
    char val = *(char*)(this[1] + 0x1d);
    if (val == 2) {
        *(uint*)(this[0x16] + 0x94) |= 0x80;
    } else if (val == 1) {
        *(uint*)(this[0x16] + 0x94) |= 0x10;
    }

LAB_0050e914:
    // Clear array of something (maybe child slots or attachments)
    short count = *(short*)((int)this + 0x6C); // +0x6C = count
    short sVar7 = 0;
    if (0 < count) {
        do {
            int* slot = (int*)((int)this + 0x80 + sVar7 * 8); // array at +0x80, each entry 8 bytes (two ints)
            if (slot != (int*)0x0) {
                slot[0] = 0;
                slot[1] = 0;
            }
            sVar7 = sVar7 + 1;
        } while (sVar7 < count);
    }
    if (type == 6) {
        if ((this[0x14] != 0) && (iVar5 = this[0x16], iVar5 != 0)) {
            int managerInternal = *(int*)(this[0x14] + 0x90); // Dereference manager structure
            uint idx = 0;
            if (*(int*)(managerInternal + 0x34) != 0) {
                int offset = 0;
                do {
                    // Store child pointer into array at managerInternal + 0x50 + offset
                    *(int*)(offset + 0x58 + *(int*)(managerInternal + 0x50)) = iVar5; // Actually this line is confusing: *(int*)(offset + 0x58 + base) = iVar5
                    idx++;
                    offset += 0xB0; // stride 0xB0
                } while (idx < *(uint*)(managerInternal + 0x34));
            }
        }
    } else {
        this[0x14] = 0; // Clear manager pointer for non-type6
    }
    return;
}