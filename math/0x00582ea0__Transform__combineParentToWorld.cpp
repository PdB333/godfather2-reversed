// FUNC_NAME: Transform::combineParentToWorld
// Address: 0x00582ea0
// Role: Combines two transforms (parent and this) into a world transform.
//   Calls internal helper (FUN_0056cba0) to combine orientation, then adds position
//   components (x,y,z) and sets homogeneous component (w) from global constant.

void __thiscall Transform::combineParentToWorld(int param_1, int param_2)
{
    // param_1: pointer to parent transform object (contains pointer to its data at +0x4)
    // param_2: pointer to output transform object (data pointer at +0x4)
    // this: pointer to child/local transform object (data pointer at +0x4 via in_EAX)

    int pParentData = *(int *)(param_1 + 4);  // parent transform data block
    int pOutputData = *(int *)(param_2 + 4);  // output transform data block
    int pThisData   = *(int *)(in_EAX + 4);   // this transform data block

    // Internal helper: likely combines orientation/scaling (e.g., quaternion multiply)
    FUN_0056cba0(pParentData, pThisData, pOutputData);

    // Read position components from parent and this data blocks
    float parentX = *(float *)(pParentData + 0x10);
    float parentY = *(float *)(pParentData + 0x14);
    float parentZ = *(float *)(pParentData + 0x18);
    float parentW = *(float *)(pParentData + 0x1c); // homogeneous, not used in sum

    float thisX = *(float *)(pThisData + 0x10);
    float thisY = *(float *)(pThisData + 0x14);
    float thisZ = *(float *)(pThisData + 0x18);
    float thisW = *(float *)(pThisData + 0x1c);

    // Sum positions to produce world position
    *(float *)(pOutputData + 0x10) = parentX + thisX;
    *(float *)(pOutputData + 0x14) = parentY + thisY;
    *(float *)(pOutputData + 0x18) = parentZ + thisZ;

    // Override homogeneous component with a constant (likely 1.0f for standard transformation)
    *(float *)(pOutputData + 0x1c) = (float)DAT_00e2b1a4; // global constant (e.g., 1.0f)
    return;
}