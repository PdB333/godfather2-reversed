// FUNC_NAME: GodfatherGameManager::setPlayerColor
void __fastcall GodfatherGameManager::setPlayerColor(unsigned int *param_1)

{
  _DAT_0121b850 = *param_1;
  _DAT_0121b854 = param_1[1];
  _DAT_0121b858 = param_1[2];
  _DAT_0121b85c = param_1[3];
  if (((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b874 != 0)) &&
     (*(int *)(&DAT_0121ba14 + DAT_0121b878 * 4) != 0)) {
    FUN_0060add0(DAT_0121b754,*(int *)(&DAT_0121ba14 + DAT_0121b878 * 4),&DAT_0121b850);
  }
  return;
}