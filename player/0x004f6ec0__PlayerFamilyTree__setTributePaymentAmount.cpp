// FUNC_NAME: PlayerFamilyTree::setTributePaymentAmount
void PlayerFamilyTree::setTributePaymentAmount(int param_1, int param_2)
{
  int tributeAmount = 0x70; // +0x70: tribute payment amount field
  FUN_004eba90(param_1, param_2, &tributeAmount, 1);
  return;
}