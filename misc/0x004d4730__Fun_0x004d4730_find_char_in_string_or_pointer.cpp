// FUNC_NAME: Fun_0x004d4730_find_char_in_string_or_pointer
char * __thiscall Fun_0x004d4730_find_char_in_string_or_pointer(undefined4 *this,char searchChar,char *inputString)
{
  char *pcVar1;
  
  pcVar1 = (char *)0x0;
  if (inputString != (char *)0x0) {
    pcVar1 = _strchr(inputString,(int)searchChar);
    return pcVar1;
  }
  if ((char *)*this != (char *)0x0) {
    pcVar1 = _strchr((char *)*this,(int)searchChar);
  }
  return pcVar1;
}