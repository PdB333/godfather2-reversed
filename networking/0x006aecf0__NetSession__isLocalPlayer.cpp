// FUNC_NAME: NetSession::isLocalPlayer
undefined4 __thiscall NetSession::isLocalPlayer(int this, int player, undefined4 param_3, undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  if (*(int *)(player + 0x1ee8) == 0) {
    iVar2 = FUN_00471610(); // likely getLocalPlayerIndex or similar
    cVar1 = FUN_006ae680(iVar2 + 0x30,param_3,param_4); // likely compare player IDs
    if (cVar1 != '\0') {
      return 1;
    }
  }
  else if (*(int *)(player + 0x1ee8) == *(int *)(this + 0x184)) { // +0x184: local player ID
    return 1;
  }
  return 0;
}