// FUNC_NAME: NetSession::processIncomingPacket
void __thiscall NetSession::processIncomingPacket(int thisPtr, int *packetData)
{
  uint *puVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *ediPtr; // was unaff_EDI (likely 'this' reassignment)
  int fsOffset; // was unaff_FS_OFFSET

  someSubroutine_0x533cc0();
  *ediPtr = &PTR_FUN_00e371e8; // vtable setup
  
  if (*(char *)(thisPtr + 0xd) == '\0') { // +0x0D: some flag (connection not closing?)
    // Circular buffer operations on DAT_01194790 (likely packet window/sequence buffer)
    iVar6 = DAT_0119478c + -1;
    iVar8 = DAT_0119478c + 2;
    if (iVar6 < 0) {
      iVar6 = 0x13; // buffer size = 20 (0x14)
    }
    else if (0x13 < iVar8) {
      iVar8 = DAT_0119478c + -0x12;
    }
    (&DAT_01194790)[iVar6] = (&DAT_01194790)[iVar6] + (&DAT_01194790)[iVar8]; // accumulate window data
    DAT_0119478c = iVar6; // update window index

    // Check for ACK/sequence processing
    if (((((*param_2 != 0 || param_2[1] != 0) || (param_2[2] != 0 || param_2[3] != 0)) &&
         (uVar7 = FUN_004e9270(), uVar7 != 0)) && ((uVar7 != 0xffffffff && (uVar7 < 0x1000)))) &&
       ((uVar7 * 0x38 != -0x11a0f28 &&
        (piVar3 = *(int **)(&DAT_011a0f38 + uVar7 * 0x38), piVar3 != (int *)0x0)))) {
      *piVar3 = *piVar3 + 1; // increment reference count or counter
    }

    FUN_004e5310(ediPtr); // process reliable/reliable sequenced data

    // Check for out-of-order or duplicate packet handling
    if ((*(char *)((int)param_2 + 0x11) != '\0') && // +0x11: packet flag (reliable?)
       (uVar7 = (*(code *)PTR_FUN_0110ac0c)(), (*(uint *)(ediPtr[1] + 0x84) & uVar7) == 0)) { // +0x84: connection flags
      *(undefined1 *)(thisPtr + 0xc) = 1;
      return;
    }

    // Store packet data for deferred processing
    ediPtr[10] = 0;  // +0x28 (depending on pointer size)
    ediPtr[0xb] = 0; // +0x2C
    uVar4 = DAT_00e2b1a4; // likely a static timestamp/sequence
    ediPtr[9] = param_2; // +0x24: store packet pointer
    ediPtr[0xc] = uVar4; // +0x30: store timestamp

    // Update packet sequence fields
    *(undefined1 *)(ediPtr + 0x17) = 0; // +0x5C: clear some flag
    cVar2 = (char)param_2[4]; // packet type byte
    if ((cVar2 == '\n') || (cVar2 == '\x04')) { // packet types: 0x0A (newline?) or 0x04
      uVar5 = 0xffff;
    }
    else {
      uVar5 = *(ushort *)(*(int *)(ediPtr[1] + 0x10) + 0x1e); // connection's sequence state
      if ((cVar2 == '\x03') && ((uVar5 & 0x300) == 0x100)) { // check for specific packet subtype
        uVar5 = uVar5 & 0xfeff; // clear a bit
      }
    }
    *(ushort *)(ediPtr + 3) = uVar5 & 0x7ff | 0x1000; // +0x0C: store sequence bits

    // Multiple calls to some buffer/progress function (likely advancing stream)
    FUN_004ebb40(); // progress stream
    FUN_004ebb40();
    FUN_004ebb40();
    FUN_004ebb40();
    FUN_004ebb40();

    // Check for special connection flag (likely encrypted/compressed)
    if ((*(byte *)(param_2 + 5) & 0x10) != 0) { // +0x14: packet flags
      puVar1 = (uint *)(*(int *)(**(int **)(fsOffset + 0x2c) + 8) + ediPtr[4]); // thread-local storage? or session data
      *puVar1 = *puVar1 | 0x20000000; // set flag
    }
  }
  return;
}