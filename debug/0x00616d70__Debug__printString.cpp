// FUNC_NAME: Debug::printString
void Debug::printString(char *message)
{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = message;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_00ab8560(0,message,(int)pcVar2 - (int)(message + 1));
  FUN_00616720();
  return;
}