// FUNC_NAME: InputManager::loadInputConfig
undefined4 __thiscall InputManager::loadInputConfig(int this, char *configPath)
{
  char cVar1;
  char *_Dest;
  undefined4 local_c8;
  undefined4 local_c4;
  char local_c0 [192];
  
  cVar1 = FUN_0098bc00(configPath);
  if (cVar1 != '\0') {
    return 0;
  }
  if (*configPath == '\0') {
    FUN_0098ce00(1);
  }
  else {
    _strncpy(local_c0,configPath,0xc0);
    _Dest = _strrchr(local_c0,0x2f);
    if (_Dest != (char *)0x0) {
      _strncpy(_Dest,"/input",(int)&stack0x00000000 - (int)_Dest);
    }
    FUN_0098cf00(local_c0);
    if (*(int *)(this + 0x5c) != 0) {
      FUN_00926810(&local_c8,&local_c4);
      FUN_0098ab10(local_c8,local_c4);
      return 1;
    }
  }
  return 1;
}