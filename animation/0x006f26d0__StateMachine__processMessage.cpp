// FUNC_NAME: StateMachine::processMessage

void __thiscall StateMachine::processMessage(int thisPtr, int *msg)
{
    int **vtable = (int **)(thisPtr - 0x3c);
    int msgID = *msg;
    int msgData = msg[1];
    char isActive = ((bool (__thiscall *)(void *))(*vtable[7]))();  // vtable+0x1c

    if (isActive) {
        if (msgID == g_MSG_ACTIVE) {
            if (*(byte *)(thisPtr + 0x50) & 4) {
                if (*(float *)(thisPtr + 0x3c) > 0.0f) {
                    *(float *)(thisPtr + 0x3c) -= DAT_01206800;
                } else {
                    ((void (__thiscall *)(void *, char))(*vtable[10]))(thisPtr, *(char *)(thisPtr + 0x51));  // vtable+0x28
                    *(byte *)(thisPtr + 0x50) &= ~4;
                }
            }
        } else if (msgID == *(int *)(thisPtr + 0x24)) {
            ((void (__thiscall *)(void *))(*vtable[11]))();  // vtable+0x2c
        } else if (msgID == *(int *)(thisPtr + 0x1c)) {
            ((void (__thiscall *)(void *, int))(*vtable[9]))(thisPtr, 1);  // vtable+0x24
        }
        goto finalCheck;
    }

    // Not active: handle reset/initialize message
    if (msgID == *(int *)(thisPtr + 0x88)) {
        int tmp = 0;
        bool processReset = false;
        if ((*(uint *)(thisPtr + 0x14) & 0x100) && msgData != 0) {
            tmp = getAnimationResource();  // FUN_006f1e40
            if (tmp) {
                playAnimation(tmp);  // FUN_0043a750
                processReset = true;
            }
        } else if ((*(uint *)(thisPtr + 0x14) & 0x200) != 0) {
            // Check some global conditions
            if ((DAT_012233a0) && (*(int *)(DAT_012233a0 + 4) != 0)) {
                int temp2 = *(int *)(DAT_012233a0 + 4) - 0x1f30;
                if (temp2 != 0) {
                    temp2 = getComponent(temp2);  // FUN_006ad7f0
                    if (temp2 != 0) {
                        temp2 = getSomePointer();  // FUN_009a9520
                        if (temp2 != 0) {
                            tmp = temp2 + 0x20;
                            if (tmp) {
                                playAnimation(tmp);
                                processReset = true;
                            }
                        }
                    }
                }
            }
        }

        if (processReset) {
            if (g_MSG_ACTIVE != 0) {
                sendMessage(thisPtr, &g_MSG_ACTIVE, 0x8000);  // FUN_00408900
            }
            *(byte *)(thisPtr + 0x50) |= 1;
            *(char *)(thisPtr + 0x51) = 0;
            float maxTimer = *(float *)(thisPtr + 0xb8);
            if (maxTimer < 0.0f) maxTimer = 0.0f;
            *(float *)(thisPtr + 0x3c) = maxTimer;
            *(byte *)(thisPtr + 0x50) |= 4;
        }
    }

finalCheck:
    if (*msg == *(int *)(thisPtr + 0x2c)) {
        toggleVisibility(true);  // FUN_006f0910(1)
        *(byte *)(thisPtr + 0x50) |= 0x10;
    } else if (*msg == *(int *)(thisPtr + 0x34)) {
        toggleVisibility(false);  // FUN_006f0910(0)
        *(byte *)(thisPtr + 0x50) &= ~0x10;
    }
}