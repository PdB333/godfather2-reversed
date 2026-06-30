// FUNC_NAME: StreamManager::handleStreamPacket
void __thiscall StreamManager::handleStreamPacket(int *this, uint param_2)
{
  int *in_EAX;
  uint uVar1;
  undefined4 uVar2;
  
  FUN_00642b00();
  switch(*in_EAX) {
  case 1: // STREAM_STATE_INIT
    FUN_00642420(1);
    in_EAX[1] = param_2;
    *in_EAX = 0xb; // STREAM_STATE_WAITING
    return;
  case 2: // STREAM_STATE_REQUESTING
  case 3: // STREAM_STATE_DOWNLOADING
    uVar1 = (uint)(*in_EAX == 2);
    uVar2 = 2;
LAB_00642cfd:
    FUN_00643990(uVar2,uVar1,0);
    break;
  case 4: // STREAM_STATE_PROCESSING
    FUN_006438e0((param_2 << 0x12 | in_EAX[1]) << 6 | 1,*(undefined4 *)(this[3] + 8));
    in_EAX[1] = param_2;
    *in_EAX = 0xb; // STREAM_STATE_WAITING
    return;
  default:
    goto switchD_00642c68_caseD_5;
  case 10: // STREAM_STATE_BUFFERING
    *(uint *)(*(int *)(*this + 0xc) + in_EAX[1] * 4) =
         *(uint *)(*(int *)(*this + 0xc) + in_EAX[1] * 4) & 0xffffff | param_2 << 0x18;
    in_EAX[1] = param_2;
    *in_EAX = 0xb; // STREAM_STATE_WAITING
    return;
  case 0xb: // STREAM_STATE_WAITING
    uVar1 = in_EAX[1];
    if (param_2 != uVar1) {
      uVar2 = 0;
      goto LAB_00642cfd;
    }
  }
  in_EAX[1] = param_2;
  *in_EAX = 0xb; // STREAM_STATE_WAITING
switchD_00642c68_caseD_5:
  return;
}