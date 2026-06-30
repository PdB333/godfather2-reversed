// FUNC_NAME: TNLConnection::getPacketTime
void TNLConnection::getPacketTime(undefined4 param_1)

{
  code *pcVar1;
  int iVar2;
  int unaff_ESI;
  
  iVar2 = *(int *)(unaff_ESI + 0xc);
  if (iVar2 == 0x116) { // PacketType::ConnectionStart
    iVar2 = *(int *)(unaff_ESI + 0x10) + 0x10; // Get time from header + offset
  }
  else if (iVar2 - 0x11dU < 2) { // PacketType::Reliable or PacketType::UnorderedReliable (0x11D-0x11E)
    iVar2 = **(int **)(unaff_ESI + 0x28); // Get time from reliable packet header
  }
  else if (iVar2 < 0x101) { // PacketType::GameData (first packet types)
    iVar2 = FUN_00636c00(&DAT_00e4242c,iVar2); // Get from connection stats array
  }
  else { // Other packet types
    iVar2 = *(int *)(&DAT_00e2a4bc + iVar2 * 4); // Get from packet type lookup table
  }
  FUN_00638b20(param_1,iVar2,*(undefined4 *)(unaff_ESI + 4)); // Set packet time
  pcVar1 = (code *)swi(3); // Software interrupt 3 (likely debug break)
  (*pcVar1)();
  return;
}