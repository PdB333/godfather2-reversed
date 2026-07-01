// FUNC_NAME: NetConnection::processConnectionResponse
void __fastcall NetConnection::processConnectionResponse(int this)
{
    char cVar1;
    unsigned short uVar2;
    int *piVar3;
    char *pcVar4;
    char *pcVar5;
    int *piVar6;
    int iVar7;
    undefined4 uVar8;
    undefined4 unaff_EBX;
    undefined4 unaff_EBP;
    undefined1 *puVar9;
    undefined4 uVar10;
    undefined1 auStack_20[4];
    undefined1 auStack_1c[4];
    undefined1 auStack_18[24];

    // Get global network manager (DAT_0113d220 +0x34 returns pointer to a manager)
    piVar3 = (int *)(**(code **)(*DAT_0113d220 + 0x34))();

    // Get connection target string (e.g. IP/hostname)
    pcVar4 = (char *)getTargetString();
    uVar2 = (**(code **)(*piVar3 + 0x2c))(); // Probably get port or socket handle

    if (pcVar4 != (char *)0x0) {
        // Check if string is empty (length == 1 means empty string with null terminator)
        pcVar5 = pcVar4;
        do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        if (pcVar5 == pcVar4 + 1) {
            piVar6 = (int *)(**(code **)(*DAT_0113d1fc + 0x48))(); // Get global session
            iVar7 = (**(code **)(*piVar6 + 0x28))(); // Check if session is active
            if (iVar7 == 0) goto LAB_00b45d25;
        }

        // Allocate memory for a new packet/stream (size 0xD0)
        iVar7 = allocateMemory(0xd0);
        if (iVar7 == 0) {
            uVar8 = 0;
        }
        else {
            // Create packet using stored state at this+0x8c (likely connection ID)
            uVar8 = createPacket(*(undefined4 *)(this + 0x8c));
        }
        *(undefined4 *)(this + 0x98) = uVar8; // Store packet pointer

        // Validate connection with the given socket/port
        cVar1 = validateConnection(*(undefined4 *)(this + 0x90), uVar2);
        if (cVar1 != '\0') {
            piVar6 = (int *)(**(code **)(*DAT_0113d1fc + 0x48))();
            iVar7 = (**(code **)(*piVar6 + 0x28))();
            if (iVar7 == 0) {
                // Build reliable packet from template (all zeros)
                initPacketBuilder(0, 0, 0, 0);
                uVar8 = *(undefined4 *)(*(int *)(*(int *)(this + 0x98) + 0xcc) + 0x48);
                uVar10 = 0;
                puVar9 = auStack_18;
                (**(code **)(*DAT_0113d1fc + 0x48))((int)puVar9, uVar8, 0, pcVar4);
                buildReliablePacket(puVar9, uVar8, uVar10, pcVar4);
                finalizeSend();
            }

            // Check game state (DAT_0113d238 + 8 returns an integer; 5 means something)
            iVar7 = (**(code **)(*DAT_0113d238 + 8))();
            if (iVar7 != 5) {
                // Prepare and trigger a reliable send operation
                (**(code **)(*piVar3 + 0x4c))((int)auStack_1c, (int)auStack_20);
                (**(code **)(**(int **)(this + 0x88) + 0x34))(); // Likely get send buffer
                uVar8 = (**(code **)(*piVar3 + 0x88))(unaff_EBX, unaff_EBP);
                uVar10 = (**(code **)(*piVar3 + 0x24))(uVar8);
                handleReliableSend(uVar10, uVar8, unaff_EBX, unaff_EBP);
            }

            // Set status to success (3 = connected/success)
            *(undefined4 *)(this + 0x198) = 3;
            return;
        }
    }

LAB_00b45d25:
    // Failure path: set error code and status
    *(undefined4 *)(this + 0x19c) = 0xffffff2d; // -211, e.g. CONNECTION_FAILED
    *(undefined4 *)(this + 0x198) = 5;          // 5 = error state
    return;
}