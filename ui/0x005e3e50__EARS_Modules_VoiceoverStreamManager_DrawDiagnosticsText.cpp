// Xbox PDB: EARS::Modules::VoiceoverStreamManager::DrawDiagnosticsText
// FUNC_NAME: DialogTreeManager::processDialogActions
void DialogTreeManager::processDialogActions(int param_1)
{
  int dialogAction;
  code *actionFunc;
  
  // Process first dialog action
  FUN_004d3bc0("DIALOG");
  FUN_005dc3d0(DAT_01223508,param_1);
  if (dialogAction != 0) {
    (*actionFunc)(dialogAction);
  }
  
  // Process second dialog action (likely a follow-up or alternative)
  FUN_004d3bc0(&DAT_00e3f500);
  FUN_005dc3d0(DAT_01223508,param_1);
  if (dialogAction != 0) {
    (*actionFunc)(dialogAction);
  }
  return;
}