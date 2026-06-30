// FUNC_NAME: PlayerBehavior::update
void __thiscall PlayerBehavior::update(int *this, int gameState, undefined4 context) {
    char inputF, input38, inputB8;
    uint slotIndex;

    // +0x00: vtable, +0x20: virtual method (e.g., preUpdate)
    (*(void (__thiscall **)(int))(*(int *)this + 0x20))(context);

    // this[1] is likely a message dispatcher object (e.g., EventManager)
    // +0x0c: virtual method (e.g., sendMessage) with message ID 0x25
    (*(void (__thiscall **)(int))(*(int *)this[1] + 0xc))(0x25);

    // Dispatch based on some state (extraout_DH from previous call? Possibly return value of above)
    slotIndex = (uint)(byte)(extraout_DH - 1);
    if ((int)slotIndex < DAT_01217d80) { // global max slot count
        (*(void (__thiscall **)(int, int, int, int, int))(&DAT_01217d84[slotIndex * 2]))(this, gameState, context, (&DAT_01217d88)[slotIndex * 2], 0);
    }

    // Check input states for three action buttons (0xf=15=Tab?, 0x38=56=Alt?, 0xb8=184=unknown)
    inputF = FUN_00b93170(0xf);   // e.g., isAction1Pressed
    input38 = FUN_00b93170(0x38); // e.g., isAction2Pressed
    inputB8 = FUN_00b93170(0xb8); // e.g., isAction3Pressed

    // +0x1bb: bool flag for "using item" or "aiming"
    if (*(char *)((int)this + 0x1bb) == '\0') {
        if (inputF != '\0') {
            goto setFlagTrue;
        }
        // fall through: flag remains 0
        inputF = '\0';
    } else {
        if (inputF == '\0') {
setFlagTrue:
            if ((input38 == '\0') && (inputB8 == '\0')) {
                // all inputs released -> clear flag
                goto setFlagFalse;
            }
        }
        inputF = '\x01'; // flag should be set because at least one input held
    }
    *(char *)((int)this + 0x1bb) = inputF; // update flag

    if (inputF == '\0') {
        // Flag cleared: process action bits
        // +8: flags byte (bit0=move, bit1=action, bit2=targetSelect)
        char actionFlags = *(char *)((int)this + 8); // int pointer offset 2 = byte offset 8
        if (actionFlags & 1) {
            FUN_0049abe0(this, gameState); // handle movement
        }
        if ((actionFlags >> 1) & 1) {
            FUN_0049ad60(gameState, context); // handle action
        }
        if ((actionFlags >> 2) & 1) {
            // Reset target slot
            this[0x62] = 0; // offset 0x62*4 = 0x188: targetSlot
            this[99] = 0;   // offset 99*4 = 0x18c: targetFlags
            slotIndex = 0;
            if (*(int *)(gameState + 0x10) != 0) { // number of entities/players
                do {
                    char slotActive = FUN_00b930b0(slotIndex); // check if slot valid
                    if (slotActive != '\0') {
                        this[0x62] = slotIndex & 0xff;
                        this[99] = 0x300ff; // specific target flags (lock-on?)
                        break;
                    }
                    slotIndex++;
                } while (slotIndex != *(uint *)(gameState + 0x10));
            }
        }
    }

    // Second message dispatch with ID 0x2a
    (*(void (__thiscall **)(int))(*(int *)this[1] + 0xc))(0x2a);

    slotIndex = (uint)(byte)(extraout_DH_00 - 1);
    if ((int)slotIndex < DAT_01217d80) {
        (*(void (__thiscall **)(int, int, int, int, int))(&DAT_01217d84[slotIndex * 2]))(this, gameState, context, (&DAT_01217d88)[slotIndex * 2], 0);
    }
}