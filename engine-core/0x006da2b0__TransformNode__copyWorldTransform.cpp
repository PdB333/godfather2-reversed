// FUNC_NAME: TransformNode::copyWorldTransform
void __fastcall TransformNode::copyWorldTransform(int this)
{
  int sourceNode;
  
  if ((*(int *)(this + 0x10) != 0) && (*(int *)(this + 0x10) != 0x48)) {
    if (*(int *)(this + 0x10) == 0) {
      sourceNode = 0;
    }
    else {
      sourceNode = *(int *)(this + 0x10) + -0x48;
    }
    // Copy 6 doubles (48 bytes) of transform data from source to this
    *(undefined8 *)(this + 0x20) = *(undefined8 *)(sourceNode + 0x60);
    *(undefined8 *)(this + 0x28) = *(undefined8 *)(sourceNode + 0x68);
    *(undefined8 *)(this + 0x30) = *(undefined8 *)(sourceNode + 0x70);
    *(undefined8 *)(this + 0x38) = *(undefined8 *)(sourceNode + 0x78);
    *(undefined8 *)(this + 0x40) = *(undefined8 *)(sourceNode + 0x80);
    *(undefined8 *)(this + 0x48) = *(undefined8 *)(sourceNode + 0x88);
  }
  return;
}