// FUNC_NAME: Debug::printString
void __fastcall Debug::printString(int this, char *message)
{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = message;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_00ab8560(0, message, (int)pcVar2 - (int)(message + 1)); // OutputDebugString or similar
  FUN_00616720(); // Flush or update debug output
  return;
}