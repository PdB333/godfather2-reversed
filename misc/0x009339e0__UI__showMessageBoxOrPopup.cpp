// FUNC_NAME: UI::showMessageBoxOrPopup
void FUN_009339e0(void *thisOrNull)
{
  char *formattedStr;
  char *tempStr;
  int local_c;
  int local_8;
  void (*deallocFunc)(char *);
  
  if (thisOrNull == (void *)0x0) {
    FUN_00983120((char *)0x0, (void *)0x0, 0);
  }
  else {
    tempStr = (char *)0x0;
    local_c = 0;
    local_8 = 0;
    deallocFunc = (void (*)(char *))0x0;
    // Format string: "{%s}\n\n{%s}" with the message and a localization key
    FUN_004d4ad0(&tempStr, "{%s}\\n\\n{%s}", thisOrNull, "$mp_press_to_cancel");
    formattedStr = tempStr;
    if (tempStr == (char *)0x0) {
      formattedStr = &DAT_0120546e; // Fallback empty string
    }
    FUN_00983120(formattedStr, &LAB_00932650, 0);
    if (tempStr != (char *)0x0) {
      (*deallocFunc)(tempStr); // Free formatted string
      return;
    }
  }
  return;
}