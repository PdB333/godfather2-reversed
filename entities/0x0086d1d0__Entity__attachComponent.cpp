// FUNC_NAME: Entity::attachComponent
undefined1 __thiscall Entity::attachComponent(int *this, int *newComponent)
{
  int *currentNode;
  char cmpResult;
  int *targetNode;
  int attachedObj;
  undefined1 result;
  int *nodePtr;
  undefined4 savedFlags;
  int *tempNode;
  undefined4 localFlags;
  int queryResult[3];
  int globalState;

  nodePtr = (int *)0x0;
  tempNode = (int *)0x0;
  savedFlags = (uint)(uint3)savedFlags; // original stack value
  if (newComponent != (int *)0x0) {
    queryResult[0] = 0;
    cmpResult = (**(code **)(*newComponent + 0x10))(0xa5975eb2, queryResult);
    // QueryInterface for a specific interface (hash 0xa5975eb2)
    tempNode = (int *)(-(uint)(cmpResult != '\0') & queryResult[0]);
  }
  currentNode = this + 0x14;
  if (this[0x14] == 0) {
    targetNode = (int *)0x0;
  }
  else {
    targetNode = (int *)(this[0x14] + -0x48); // embedded node container offset
  }
  if (tempNode != targetNode) {
    // Detach old component if present
    if ((undefined4 *)this[0x1b] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)this[0x1b])(1); // virtual destructor? 
      this[0x1b] = 0;
    }
    if (tempNode != (int *)0x0) {
      nodePtr = tempNode + 0x12; // node offset 0x12 within the component
    }
    if ((int *)*currentNode != nodePtr) {
      // Remove old linked list entry
      if ((int *)*currentNode != (int *)0x0) {
        FUN_004daf90(currentNode); // list removal helper
      }
      *currentNode = (int)nodePtr;
      if (nodePtr != (int *)0x0) {
        this[0x15] = nodePtr[1]; // save back-pointer
        nodePtr[1] = (int)currentNode; // set new back-pointer to owner's list head
      }
    }
  }
  if (tempNode == (int *)0x0) {
    this[0x1a] = 0;
    return (undefined1)((uint)savedFlags >> 24); // return part of original savedFlags
  }
  // Query for additional flags
  queryResult[1] = 0;
  cmpResult = (**(code **)(*tempNode + 0x10))(0xfb67a6e2, queryResult + 1);
  this[0x1a] = -(uint)(cmpResult != '\0') & savedFlags; // set some flag
  // Notify the component of attachment
  (**(code **)(*tempNode + 0x1a4))(this);
  // Allocate small context object if not already present
  if (this[0x1b] == 0) {
    savedFlags = 2;
    queryResult[0] = 0x10;
    queryResult[1] = 0;
    attachedObj = FUN_009c8ed0(0x28, &savedFlags);
    if (attachedObj == 0) {
      attachedObj = 0;
    }
    else {
      attachedObj = FUN_00871800(tempNode); // constructor with component
    }
    this[0x1b] = attachedObj;
    if (attachedObj == 0) {
      result = (undefined1)((uint)unaff_ESI >> 0x18);
      goto LAB_0086d2e6;
    }
  }
  // Update self
  (**(code **)(*this + 0x30))(); // virtual function (onAttach?)
  FUN_00871870(); // global post-processing
  result = 1;
LAB_0086d2e6:
  // Iterate over children or listeners
  nodePtr = (int *)FUN_00446100(this + 0x16, 0);
  if (nodePtr != (int *)0x0) {
    (**(code **)(*nodePtr + 0x10))(0x38523fc3, &stack0xffffffe4);
  }
  // Check global state
  if ((*(int *)(globalState + 0xf2c) == 1) && (this[0x31] != 0)) {
    this[0x31] = 0;
    FUN_0086cb20(); // notify UI or similar
  }
  return result;
}