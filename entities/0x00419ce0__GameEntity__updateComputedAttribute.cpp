// FUNC_NAME: GameEntity::updateComputedAttribute
void __thiscall GameEntity::updateComputedAttribute(GameEntity* this, int paramObject, undefined4 param3, undefined4 param4)
{
    // this+0x4 points to the component data block
    int* componentData = *(int**)((int)this + 4);
    // Access thread-local storage to get the global game state
    int* globalState = **(int***)(__readfsdword(0x2c));
    // Read a float from a table indexed by paramObject[0x18] (likely a type/ID)
    // Table located at globalState+8 + 0x6c
    double tempDouble = (double)*(float*)(*(int*)(globalState + 2) + 0x6c + *(int*)(paramObject + 0x18));
    // Unknown math/engine function call
    FUN_00b9c041();
    // Multiply by a global tuning constant (0x01205344)
    tempDouble = (double)((float)tempDouble * _DAT_01205344);
    // Another unknown engine function
    FUN_00b9d99d();
    // Compute final float value using another global constant (0x00e2a854)
    float computedValue = (float)tempDouble * _DAT_00e2a854;
    // Call engine functions with computedValue (likely set some state)
    FUN_00b99e20(computedValue);
    FUN_00492c60(computedValue);
    // Set componentData field at +0xf8 = global constant - value from another table
    // Table at globalState+8 + 0x74, same index as before
    *(float*)(componentData + 0x3e) = DAT_00e2b1a4 - *(float*)(*(int*)(globalState + 2) + 0x74 + *(int*)(paramObject + 0x18));
    // Another engine call (probably cleanup or state finalization)
    FUN_00492bd0();
    // Call base class method (or another handler) with the remaining parameters
    FUN_004196d0(paramObject, param3, param4);
    return;
}