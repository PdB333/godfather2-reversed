// FUNC_NAME: DialogController::configureDialog
void __thiscall DialogController::configureDialog(DialogController* this, int param_2, int param_3, DialogConfig* param_4)
{
    // Initialize dialog subsystem (FUN_00603bf0)
    initializeDialogSubsystem();
    
    // Set global flag 0x1f (likely enable dialog processing)
    setDialogFlag(0x1f);
    
    // Set first config property (e.g., text label) from param_4 with key and param_2 value
    setConfigValue(param_4, &gConfigKeyDialogText, param_2);
    
    // Initialize sub-object at offset +0xA4 (e.g., animation controller)
    initializeSubObject(reinterpret_cast<SubObject*>(this + 0xa4));
    
    // Set second config property (e.g., speaker) from param_4 with key and param_3 value
    setConfigValue(param_4, &gConfigKeyDialogSpeaker, param_3);
}