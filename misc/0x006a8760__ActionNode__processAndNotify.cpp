// FUNC_NAME: ActionNode::processAndNotify
void __thiscall ActionNode::processAndNotify(int *this)
{
  int *linkedNode;
  int *targetObject;
  
  linkedNode = (int *)*this;
  if (linkedNode != 0) {
    targetObject = (int *)this[2];
    if (targetObject != 0) {
      *(byte *)(targetObject + 0x21) = *(byte *)(targetObject + 0x21) | 4; // set bit 2 (processed)
      if ((*(byte *)(targetObject + 0x21) & 2) != 0) { // check bit 1 (pending)
        FUN_006a8100(linkedNode, targetObject, 0, 1, 0); // send notification/update
      }
    }
  }
}