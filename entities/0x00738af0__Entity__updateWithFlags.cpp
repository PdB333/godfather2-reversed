// FUNC_NAME: Entity::updateWithFlags
// Address: 0x00738af0
// Role: General update/dispatch function for Entity objects, handles reset and event dispatch based on flags.

void __thiscall Entity::updateWithFlags(EventManager* this, Entity* entity, uint updateFlags)
{
    char cVar1;
    int* piVar2;
    int iVar3;
    float10 fVar4;
    undefined4 uVar5;
    undefined4 local_30;
    undefined*** local_2c;
    undefined1 local_28;
    undefined** local_24;
    int local_20;
    int local_1c[2]; // event structure buffer
    undefined8 local_14;
    undefined4 local_c;
    uint local_8;
    undefined4 local_4;

    if (entity != nullptr) {
        if (updateFlags == 0) {
            updateFlags = getDefaultFlags(this); // FUN_00801760
        }
        if ((updateFlags & 1) == 0) {
            if ((updateFlags & 2) != 0) {
                // Initialize event structure
                local_c = 0;
                local_14 = 0;
                local_24 = &PTR_FUN_00d5dbbc; // event handler table
                local_1c[0] = 0;
                // Compute some value based on entity field at +0x23a (0x8E8) – bit 0x19 (bit 25) 
                local_20 = (-(uint)(((byte)((uint)entity[0x23a] >> 0x19) & 1) != 0) & 0xeefb2317) + 0x736760b2;
                local_1c[1] = 0;
                local_8 = local_8 & 0xffffff00;
                local_4 = DAT_01205228;

                // Get pointer to entity's data at offset +0x71e (0x1C78)
                if (entity[0x71e] == 0) {
                    iVar3 = 0;
                } else {
                    iVar3 = entity[0x71e] + -0x48;
                }
                invokeEvent(iVar3); // FUN_0044b210

                if ((local_1c[0] == 0) || (local_1c[0] == 0x48)) {
                    if (**(int**)(DAT_012233a0 + 4) == 0) {
                        iVar3 = 0;
                    } else {
                        iVar3 = **(int**)(DAT_012233a0 + 4) + -0x1f30;
                    }
                    invokeEvent(iVar3);
                }

                // Get current time or state info
                iVar3 = getCurrentTimeInfo(); // FUN_00471610
                local_8 = CONCAT31(local_8._1_3_, 1);
                local_14 = *(undefined8*)(iVar3 + 0x30);
                local_c = *(undefined4*)(iVar3 + 0x38);
                local_2c = &local_24;
                local_30 = DAT_0112ad8c;
                local_28 = 0;

                if (this == nullptr) {
                    piVar2 = nullptr;
                } else {
                    piVar2 = (int*)this + 0xf; // offset 0x3C – possibly array of event handlers
                }
                fireEvent(&local_30, piVar2, 0); // FUN_00408bf0

                if (local_1c[0] != 0) {
                    cleanupEvent(local_1c); // FUN_004daf90
                }
            }
        } else {
            resetEntity(entity, 0); // FUN_007303e0
        }

        // Check virtual function at vtable+0xbc (e.g., isAlive or getSomethingFloat)
        fVar4 = (this->vtable->func0xBC)(entity); // (**)(*this+0xbc)(entity)
        if (fVar4 == 0.0f) {
            uVar5 = 0;
        } else {
            uVar5 = 1;
            iVar3 = checkCondition(); // FUN_00806440
            if (iVar3 != 1) {
                iVar3 = (entity->vtable->func0x2C8)(); // virtual on entity
                if (iVar3 != 0) {
                    sendEvent(entity, iVar3, 0x3911ea42, 0x971ed07a); // FUN_00730740
                }
                if (entity[0x7ba] != 0) { // offset 0x1EE8 – pointer to another object
                    sendEvent(entity, entity[0x7ba], 0x71dd8113, 0xcfea674b); // FUN_00730740
                }
            }
        }

        cVar1 = entity->vtable->func0x1BC(); // virtual returning bool
        if (cVar1 != '\0') {
            (this->vtable->func0x31C)(entity, uVar5); // virtual on this with entity and flag
        }

        cVar1 = entity->vtable->func0x10(0x383225a1, &stack0x00000000); // virtual with interface ID
        if ((cVar1 != '\0') && (local_8 != 0)) {
            handleSpecificEvent(local_8, uVar5); // FUN_00737ea0
            return;
        }

        finalizeUpdate(entity, uVar5); // FUN_00734d80
    }
    return;
}