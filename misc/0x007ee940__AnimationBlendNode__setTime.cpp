// FUNC_NAME: AnimationBlendNode::setTime
void __thiscall AnimationBlendNode::setTime(int this, int newTime)
{
  undefined4 *blendNode;
  uint uVar2;
  
  *(int *)(this + 4) = newTime;  // +0x04: currentTime
  if (*(int *)(this + 8) == newTime) {  // +0x08: targetTime - reached blend point
    blendNode = *(undefined4 **)(this + 0x10);  // +0x10: blend target node pointer
    *(int *)(this + 8) = 0;  // reset targetTime
    if (blendNode != (undefined4 *)0x0) {
      *blendNode = 0;  // blendStart
      blendNode[1] = 0;  // blendEnd
      uVar2 = DAT_010c2678 & DAT_012054b4;  // random index using frame counter
      DAT_012054b4 = DAT_012054b4 + 1;  // increment frame counter
      blendNode[2] = *(float *)(&DAT_010c2680 + uVar2 * 4) *  // blend duration = random * blendScale + blendBase
                     *(float *)(DAT_0112bb50 + 0x44) +  // +0x44: blendScale factor from global config
                     *(float *)(DAT_0112bb50 + 0x40);  // +0x40: blendBase offset from global config
    }
  }
  return;
}