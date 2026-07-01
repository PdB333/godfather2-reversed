// FUNC_NAME: AnimationLayer::sychronizeTime
void __thiscall AnimationLayer::sychronizeTime(int thisPtr, int* pOtherLayer)
{
    float tempFloat;
    int engineObject;

    // If no other layer is provided, just copy this layer's transform to the engine
    if (pOtherLayer == (int*)0x0) {
        engineObject = FUN_0041d1f0();  // Get engine object pointer (maybe player transform)
        *(undefined4*)(engineObject + 0x20) = *(undefined4*)(thisPtr + 0x7c); // copy some quaternion/rotation
        *(undefined4*)(engineObject + 0x2c) = *(undefined4*)(thisPtr + 0x80);
        *(undefined4*)(engineObject + 0x10) = *(undefined4*)(thisPtr + 0x84);
        *(undefined4*)(engineObject + 0x14) = *(undefined4*)(thisPtr + 0x88);
        *(undefined4*)(engineObject + 0x18) = *(undefined4*)(thisPtr + 0x8c);
        return;
    }

    // Temporarily save engine state (likely quaternion/rotation)
    undefined4 saved_uVar4 = DAT_00e44630;
    undefined4 saved_uVar3 = DAT_00d6471c;
    undefined4 saved_uVar2 = DAT_00d5ef88;
    undefined4 saved_uVar1 = _DAT_00d5cf70;

    FUN_008334a0(); // Some update function
    FUN_00835e20(); // Another update function

    // Global current time reference
    tempFloat = _DAT_00d5780c; // Current audio/animation time

    // If the layer IDs match, adjust current time by the other layer's offset
    if (*(int*)(*pOtherLayer + 0xc) == *(int*)(thisPtr + 0xc)) {
        tempFloat = _DAT_00d5780c - (float)pOtherLayer[1]; // Subtract delta time
        FUN_00835e40(*pOtherLayer + 0x30, pOtherLayer[1]); // Set other layer's time to its offset
    }

    // Set this layer's time to the computed value
    FUN_00835e40(thisPtr + 0x30, tempFloat);

    // Restore engine state with the saved values (order is shuffled)
    engineObject = FUN_0041d1f0();
    *(undefined4*)(engineObject + 0x20) = saved_uVar2;
    *(undefined4*)(engineObject + 0x2c) = saved_uVar3;
    *(undefined4*)(engineObject + 0x10) = saved_uVar1;
    *(undefined4*)(engineObject + 0x14) = saved_uVar4;
    *(undefined4*)(engineObject + 0x18) = saved_uVar1;
}