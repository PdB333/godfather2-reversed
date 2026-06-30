// FUNC_NAME: TransformNode::updateWorldTransform
void __fastcall TransformNode::updateWorldTransform(TransformNode *this)
{
  byte flags;
  undefined4 *matrixData;
  undefined4 localMatrix[16]; // 4x4 matrix
  int resultCode;
  
  flags = *(byte *)(this + 0x31);
  if ((flags & 1) == 0) {
    return;
  }
  
  if ((flags & 2) != 0) {
    if ((flags & 4) != 0) {
      return; // already processed
    }
    *(byte *)(this + 0x31) = flags | 4; // mark as processed
  }
  
  // Check if local position/rotation is non-zero (4 floats at +0x10)
  if ((*(int *)(this + 0x10) != 0) || (*(int *)(this + 0x14) != 0) ||
      (*(int *)(this + 0x18) != 0) || (*(int *)(this + 0x1c) != 0)) {
    
    // Get the parent's world transform (virtual call on object at +0x0C)
    // Object at +0x0C is a pointer to a parent transform or scene node
    matrixData = (undefined4 *)((*(code **)(**(int **)(*(int *)(this + 0x0C)) + 0x60))());
    // Copy 16 floats (4x4 matrix) to stack
    localMatrix[0] = matrixData[0];
    localMatrix[1] = matrixData[1];
    localMatrix[2] = matrixData[2];
    localMatrix[3] = matrixData[3];
    localMatrix[4] = matrixData[4];
    localMatrix[5] = matrixData[5];
    localMatrix[6] = matrixData[6];
    localMatrix[7] = matrixData[7];
    localMatrix[8] = matrixData[8];
    localMatrix[9] = matrixData[9];
    localMatrix[10] = matrixData[10];
    localMatrix[11] = matrixData[11];
    localMatrix[12] = matrixData[12];
    localMatrix[13] = matrixData[13];
    localMatrix[14] = matrixData[14];
    localMatrix[15] = matrixData[15];
    
    if (*(int *)(this + 0x20) == 0) { // no override transform
      if (*(char *)(this + 0x30) == '\x01') {
        // Special case: use a different transform source
        int *someObj = *(int **)(this + 8);
        void *func = **(code ***)(someObj + 2); // virtual call at +0x24? Actually offset 8+8=16? Wait: **(int **)(*(int *)(this+8)+8) then +0x24
        // Simpler: same pattern as above but with different offsets
        int vtable = **(int **)(*(int *)(this + 8) + 8);
        undefined4 uVar3 = (*(code **)(vtable + 0x24))(0, 0); // call function, returns something
        uVar3 = FUN_00475550(&resultCode, this + 0x10, uVar3);
      } else {
        undefined4 uVar3 = FUN_004151d0(); // some default function
        uVar3 = FUN_00414ef0(&resultCode, this + 0x10, localMatrix, uVar3); // combine local pos with parent matrix
      }
      FUN_00414db0(uVar3); // store result back to this?
      if (resultCode != 0) {
        *(undefined4 *)(resultCode + 8) = 0; // clear some field
      }
      if (*(int *)(this + 0x20) == 0) {
        return;
      }
    }
    
    if (*(int *)(this + 0x24) != 0) {
      FUN_004df7f0((int *)(this + 0x24)); // cleanup/release
    }
  }
}