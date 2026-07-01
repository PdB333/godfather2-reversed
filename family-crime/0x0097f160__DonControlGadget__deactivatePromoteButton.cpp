// FUNC_NAME: DonControlGadget::deactivatePromoteButton
void __thiscall DonControlGadget::deactivatePromoteButton(DonControlGadget *this)
{
  bool bButtonActive;
  char *local_c;          // +0x00: pointer to string buffer
  char local_8[4];         // unused padding
  char local_4;            // unused byte
  
  resetPromoteState();
  bButtonActive = *(int *)((char *)this + 100) != 0;   // offset 0x64 (100): some flag
  if (!bButtonActive) {
    local_c = (char *)DAT_01130308;                    // global string constant
    *(int *)local_8 = 0;                               // clear unused
    local_4 = 0;
    stringBuilder(&local_c, 0);                        // construct command string
    handleDeactivation();
    sendUICommand("DeactivateButton", 0, &DAT_00d8fe44, 1, PTR_s__tree_promote_button_00e575d0);
    bButtonActive = *(int *)((char *)this + 100) != 0;   // re-read flag after command
  }
  if (!bButtonActive) {
    setButtonState(3, 1);                              // e.g., set state to 3, sub-parameter 1
  }
}