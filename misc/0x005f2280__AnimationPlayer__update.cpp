// FUNC_NAME: AnimationPlayer::update
uint AnimationPlayer::update(float dt)
{
  int iVar1;
  uint state;
  float fVar3;
  
  state = *(uint *)(in_EAX + 0x68); // state field at +0x68
  if (state == 4) { // STATE_PAUSED
LAB_005f2430:
    return CONCAT31((int3)(state >> 8),1); // return true
  }
  if (state == 5) { // STATE_FINISHED
    return 0;
  }
  FUN_005f2fd0(); // updateAnimationTime
  state = *(uint *)(in_EAX + 0x8c); // current frame index pointer
  if (state < *(uint *)(in_EAX + 0x88)) { // total frames
    do {
      fVar3 = (float)**(ushort **)(in_EAX + 0x8c) * DAT_00e2e210; // frame time * time scale
      if (*(float *)(in_EAX + 0x74) <= fVar3 && fVar3 != *(float *)(in_EAX + 0x74)) {
        *(float *)(in_EAX + 0x74) = *(float *)(in_EAX + 0x74) + dt; // advance time
        goto LAB_005f2430;
      }
      FUN_005dbc10(*(undefined1 *)(in_EAX + 100),*(undefined4 *)(in_EAX + 0x5c),
                   *(undefined1 *)(in_EAX + 0x65),*(undefined1 *)(*(int *)(in_EAX + 8) + 2),
                   *(undefined1 *)(in_EAX + 0x66)); // process animation event
      FUN_005dbc10(**(undefined2 **)(in_EAX + 0x8c),
                   *(undefined1 *)(*(undefined2 **)(in_EAX + 0x8c) + 1)); // process frame event
      iVar1 = *(int *)(in_EAX + 0x8c); // current frame data
      switch(*(undefined1 *)(iVar1 + 2)) { // frame command type
      case 1: // CMD_POSE
        FUN_005f1860(); // applyPose
        break;
      case 2: // CMD_TRANSFORM
        FUN_005f18d0(); // applyTransform
        break;
      case 3: // CMD_SOUND
        FUN_005f1bc0(); // playSound
        break;
      case 4: // CMD_SPEED
        *(float *)(in_EAX + 0x54) = (float)*(int *)(iVar1 + 4) * _DAT_00e4463c; // set speed
        FUN_005dbc10(*(undefined1 *)(in_EAX + 0x65)); // process speed event
        break;
      case 5: // CMD_FRAME
        *(float *)(in_EAX + 0x58) = (float)*(int *)(iVar1 + 4); // set frame
        break;
      case 6: // CMD_TIME_SCALE
        fVar3 = (float)*(int *)(iVar1 + 4) * _DAT_00e4463c;
        *(ushort *)(in_EAX + 0x4a) = *(ushort *)(in_EAX + 0x4a) | 2; // set flag
        *(float *)(in_EAX + 0x3c) = fVar3; // set time scale
        FUN_005dbc10(*(undefined1 *)(in_EAX + 100),*(undefined4 *)(in_EAX + 0x5c),
                     *(undefined1 *)(in_EAX + 0x65)); // process time scale event
      }
      state = (uint)*(ushort *)(in_EAX + 0x6c); // flags at +0x6c
      *(undefined4 *)(in_EAX + 0x74) = 0; // reset elapsed time
      if ((*(ushort *)(in_EAX + 0x6c) & 1) == 0) { // not looping
        *(int *)(in_EAX + 0x8c) = *(int *)(in_EAX + 0x8c) + 8; // advance to next frame
      }
      else {
        state = state & 0xfffe; // clear loop flag
        *(short *)(in_EAX + 0x6c) = (short)state;
      }
    } while (*(uint *)(in_EAX + 0x8c) < *(uint *)(in_EAX + 0x88)); // more frames
  }
  if (*(char *)(in_EAX + 0x67) != -1) { // has callback
    FUN_005f2150(); // fireAnimationCallback
    *(undefined1 *)(in_EAX + 0x67) = 0xff; // clear callback
    return (uint)(*(int *)(in_EAX + 0x68) != 5); // return true if not finished
  }
  if ((*(ushort *)(in_EAX + 0x6c) & 0x78) == 0) { // no flags set
    *(undefined4 *)(in_EAX + 0x68) = 5; // STATE_FINISHED
  }
  else if ((*(ushort *)(in_EAX + 0x6c) & 0x100) == 0) { // not paused
    *(undefined4 *)(in_EAX + 0x68) = 4; // STATE_PAUSED
    return (uint)(*(int *)(in_EAX + 0x68) != 5);
  }
  return (uint)(*(int *)(in_EAX + 0x68) != 5);
}