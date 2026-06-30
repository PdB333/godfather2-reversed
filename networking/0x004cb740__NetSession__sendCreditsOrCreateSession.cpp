// FUNC_NAME: NetSession::sendCreditsOrCreateSession
void NetSession::sendCreditsOrCreateSession(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int *in_EAX;
  int iVar3;
  int iVar4;
  
  _DAT_01205a30 = _DAT_01205a30 + 1;
  iVar4 = 0;
  htonl(0);
  (**(code **)(*in_EAX + 0xc))();
  cVar2 = FUN_004cb6e0(param_1); // Check if already has session
  if (cVar2 == '\0') {
    iVar3 = FUN_009c8e50(0x230); // Allocate memory (0x230 bytes)
    if (iVar3 != 0) {
      iVar4 = FUN_004bf850(); // Create new session object
    }
    uVar1 = *(undefined4 *)(param_1 + 0x84); // +0x84: some session property
    *(undefined4 *)(iVar4 + 0xb4) = *(undefined4 *)(param_1 + 0x88); // +0x88: source, +0xb4: destination
    *(undefined4 *)(iVar4 + 0xb0) = uVar1; // +0xb0: assign property
    FUN_00653fd0(); // Start session timer or send
  }
  _DAT_01205a30 = _DAT_01205a30 + -1;
  return;
}