// FUNC_NAME: SimNpc::startConversation
void SimNpc::startConversation(undefined4 param_1)

{
  int npcPtr;
  
  FUN_006a7890(&npcPtr, &param_1);
  if (npcPtr != 0) {
    param_1 = *(undefined4 *)(npcPtr + 4);
    FUN_00949d90();
    return;
  }
  return;
}