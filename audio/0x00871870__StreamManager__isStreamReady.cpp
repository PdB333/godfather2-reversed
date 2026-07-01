// FUNC_NAME: StreamManager::isStreamReady
bool __fastcall StreamManager::isStreamReady(int this)
{
  int *pStreamState;
  
  pStreamState = (int *)(this + 8);
  FUN_00851440(*(undefined4 *)(this + 4), pStreamState, &DAT_00e54120, 0xb);
  FUN_00851210(*pStreamState);
  return *pStreamState != 0;
}