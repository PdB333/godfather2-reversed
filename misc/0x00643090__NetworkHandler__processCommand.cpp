// FUNC_NAME: NetworkHandler::processCommand
// Function at 0x00643090 handles incoming commands (type 5-8) and sends response packets.
// Offset 0x0c: pointer to some manager (e.g., NetSession)
// Offset 0x24: counter (decremented under certain conditions)
// Offset 0x34: threshold value (checked against in_EAX[1])

void __thiscall NetworkHandler::processCommand(int param_1, uint* param_2)
{
    int* pGameState = reinterpret_cast<int*>(/* EAX register value – likely a global or passed via EAX */);
    int iVar1;
    uint uVar2;
    uint uVar3;
    int* mgrPtr = *(int**)(param_1 + 0x0c);
    uint field1 = *(uint*)(mgrPtr + 8); // +0x8 from manager

    switch (param_2[0]) {
    case 5: // Command: some delete/increment action
        if ((*pGameState == 11) && (*(int*)(param_1 + 0x34) <= pGameState[1]) && (pGameState[1] < 250)) {
            (*(int*)(param_1 + 0x24))--; // Decrement counter
        }
        sub_00642d90(param_2[1]); // Process additional data
        return; // No response packet sent

    case 6: // Command: build and send type 8 packet
        iVar1 = sub_00642f30(); // Get some value (e.g., sequence number)
        uVar2 = ((iVar1 << 9) | param_2[1]) << 15 | 8; // Encode packet: [opcode 8]
        break;

    case 7: // Command: build and send type 7 packet
        iVar1 = sub_00642f30();
        uVar2 = ((iVar1 << 18) | param_2[1]) << 6 | 7; // Encode packet: [opcode 7]
        break;

    case 8: // Command: build and send type 9 packet with extra data
        uVar3 = sub_00642fc0(); // Get additional value
        uVar2 = (((param_2[1] << 9) | param_2[2]) << 9 | uVar3) << 6 | 9; // Encode packet: [opcode 9]
        break;

    default:
        goto checkDecrement;
    }

    // Send the constructed packet
    sub_006438e0(uVar2, field1);

checkDecrement:
    if ((*pGameState == 11) && (*(int*)(param_1 + 0x34) <= pGameState[1]) && (pGameState[1] < 250)) {
        (*(int*)(param_1 + 0x24))--; // Decrement counter
    }
    return;
}