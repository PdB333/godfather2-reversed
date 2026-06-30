// FUNC_NAME: Player::handleEvent

class Player {
public:
    void handleEvent(const InputEvent& event);
};

// Event structure based on usage (partial)
struct InputEvent {
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    void* targetObject;   // +0x0C - pointer to a game object (or 0/0x48 sentinel)
    // +0x10: unknown (16 bytes)
    // +0x30: int eventType
    int eventType;        // +0x30
    int flags;            // +0x44
};

void Player::handleEvent(const InputEvent& event) {
    char cVar1;
    uint targetHandle;
    undefined4 uVar3;
    int iVar4, iVar5;
    uint local_38;
    // Stack-based scope guard for exception safety (simplified)
    // Original code sets up a destructor callback and a local variable tracking
    // We omit the intricate pointers but note the cleanup behavior.

    // Call some initialization / cleanup on event (FUN_00800490)
    FUN_00800490(&event);  // likely event->vtable method or manager

    // Set a flag on this object (0x20000000)
    *(uint*)(this + 0x1DF8) |= 0x20000000;

    // Extract a game object handle from event.targetObject
    if (event.targetObject == nullptr || event.targetObject == (void*)0x48) {
        targetHandle = 0;
    } else {
        int* piVar6;
        if (event.targetObject == nullptr) {
            piVar6 = nullptr;
        } else {
            piVar6 = (int*)((char*)event.targetObject - 0x48);  // Adjust pointer back to containing struct
        }
        local_38 = 0;
        // Virtual call to get an identifier (hash?) from the object
        cVar1 = (**(code**)(*piVar6 + 0x10))(0x383225a1, &local_38);
        targetHandle = -(uint)(cVar1 != 0) & local_38;
    }

    // If target handle valid, event type 1 (e.g., button press), and conditions met:
    // - target object at +0x74c is non-null and not 0x48
    // - target has a particular flag (bit 10 at +0x8e0)
    // - that object has another flag (bit 3 at +0x188)
    // - event flags bit 7 at +0x44 is zero
    if (targetHandle != 0 &&
        event.eventType == 1 &&
        (iVar5 = *(int*)(targetHandle + 0x74C)) != 0 && iVar5 != 0x48 &&
        ((*(uint*)(targetHandle + 0x8E0) >> 10 & 1) != 0) &&
        ((*(uint*)(iVar5 + 0x188) >> 3 & 1) != 0) &&
        ((*(uint*)(&event.flags) >> 7 & 1) == 0))
    {
        if (*(char*)(this + 0xC94) == 0) {
            FUN_00709440();  // Possibly stop or reset audio
        }
        FUN_0072c050(0xC);  // Play sound ID 0xC
    }

    // Scope guard initialization (simplified)
    // ... (omitted the stack pointer manipulation for brevity)

    // Another call to UI / game state function
    FUN_00892af0(0);

    // Copy event data into local buffer (16 bytes)
    byte local_copy[16];
    FUN_0072f1b0(local_copy, &event);

    // Second set of conditions: same object checks, event type 2, etc.
    if (targetHandle != 0 &&
        (iVar5 = *(int*)(targetHandle + 0x74C)) != 0 && iVar5 != 0x48 &&
        ((*(uint*)(targetHandle + 0x8E0) >> 10 & 1) != 0) &&
        *(char*)(iVar5 + 0x160) == 1 &&
        event.eventType == 2)
    {
        switch (*(char*)(iVar5 + 0x165)) {
        case 0x14: uVar3 = 0x14; break;
        case 0x15: uVar3 = 0x15; break;
        case 0x16: uVar3 = 0x16; break;
        case 0x17: uVar3 = 0x17; break;
        case 0x18: uVar3 = 0x13; break;
        default: goto switchD_00733208_default;
        }
        FUN_0072c050(uVar3);  // Play sound based on sub-type
    }
switchD_00733208_default:
    // Set flags based on event flags and state
    if ((*(uint*)(&event.flags) >> 5 & 1) != 0) {
        *(uint*)(this + 0x1DF4) |= 0x1000000;
    }
    if (event.eventType == 7) {
        *(uint*)(this + 0x1DF4) |= 8;
    }
    cVar1 = FUN_007f7b90();  // Check some game state (e.g., suppression?)
    if (cVar1 != 0) {
        *(uint*)(this + 0x1DF4) |= 0x100;
    }

    // Complex conditions: if target valid and some flags allow
    if (targetHandle == 0 ||
        ((*(uint*)(this + 0x1800) >> 7 & 1) == 0) ||
        (*(int*)(this + 0x1C1C) != 0 ||
         ((*(int*)(this + 0xC5C) != 0 && *(int*)(this + 0xC5C) != 0x48) ||
          ((*(uint*)(this + 0x1DF4) >> 2 & 1) != 0))))
    {
        iVar5 = event.eventType;
        if (iVar5 == 3 && ((*(uint*)(this + 0x550) >> 0x16 & 1) != 0)) {
            *(uint*)(this + 0x1DF4) |= 0x10;
        } else if (iVar5 == 4) {
            *(uint*)(this + 0x1DF4) |= 0x800;
        } else if (iVar5 == 5 || iVar5 == 6) {
            *(uint*)(this + 0x1DF4) |= 0x400;
        } else if (iVar5 == 9) {
            *(uint*)(this + 0x1DF8) |= 0x800000;
        } else if (iVar5 == 10) {
            FUN_0072c050(0x38);  // Play sound ID 0x38
        }
        goto LAB_00733361;
    }

    // Alternative branch if previous condition false
    uVar3 = FUN_00806440();  // Get current game state / phase (returns 0-3)
    switch (uVar3) {
    case 0:
    case 1:
        uVar3 = 0xFE825136;  // Hash?
        goto play_sound_with_hash;
    case 2:
        uVar3 = 0x25D50973;
play_sound_with_hash:
        FUN_00894c40(uVar3, local_copy);  // Play sound with hash and data
        break;
    case 3:
        if (*(int*)(this + 0x1B40) != 0x637B907) {
            uVar3 = 0xEEA482AF;
            goto play_sound_with_hash;
        }
        break;
    }
    if (/* some condition on stack byte */) {
        FUN_0072c050(2);  // Play sound ID 2
    }

LAB_00733361:
    // Check another flag (bit 14 in +0x1BC8)
    if ((*(uint*)(this + 0x1BC8) >> 0xe & 1) == 0) {
        if (targetHandle != 0) {
            if (event.eventType == 2) {
                iVar5 = *(int*)(targetHandle + 0x74C);
                if (iVar5 != 0 && iVar5 != 0x48 &&
                    ((*(uint*)(targetHandle + 0x8E0) >> 10 & 1) != 0 &&
                     *(char*)(iVar5 + 0x160) == 1))
                {
                    if (*(int*)(this + 0x1C1C) == 2 &&
                        (*(int*)(this + 0xC5C) == 0 || *(int*)(this + 0xC5C) == 0x48))
                    {
                        FUN_0072c050(0xD);  // Play sound ID 0xD
                    }
                    if (*(char*)(iVar5 + 0x160) == 1 &&
                        (*(int*)(this + 0xC5C) == 0 || *(int*)(this + 0xC5C) == 0x48))
                    {
                        uVar3 = 0x12;
                        goto play_sound_final;
                    }
                }
            } else if (event.eventType == 1 &&
                       (cVar1 = FUN_007f7b90(), cVar1 == 0) &&
                       *(char*)(this + 0x1A74) != 0x1C &&
                       *(char*)(this + 0x1A74) != 0x1D)
            {
                if (*(char*)(this + 0xC64) == 2 &&
                    *(int*)(this + 0xC5C) != 0 &&
                    *(int*)(this + 0xC5C) != 0x48)
                {
                    iVar5 = FUN_0043b490();
                    iVar4 = FUN_0043b490();
                    if (iVar5 == iVar4) {
                        uVar3 = 0xF;
                        goto play_sound_final;
                    }
                }
                uVar3 = 0xE;
play_sound_final:
                FUN_0072c050(uVar3);  // Play sound ID
            }
            goto LAB_0073346c;
        }
    } else {
        *(uint*)(this + 0x1DF8) |= 0x2000000;
LAB_0073346c:
        if (targetHandle != 0) {
            FUN_00732130(targetHandle);  // Update object state?
            goto LAB_007334ac;
        }
    }

    // Final condition: if event target is valid and a global object has certain flag
    if (event.targetObject != nullptr && event.targetObject != (void*)0x48 &&
        (iVar5 = FUN_0043b870(DAT_01131040), iVar5 != 0) &&
        ((*(byte*)(iVar5 + 0x44) & 0x80) != 0))
    {
        *(uint*)(this + 0x1DF8) |= 0x4000000;
    }

LAB_007334ac:
    // Scope guard cleanup (omitted)
    return;
}