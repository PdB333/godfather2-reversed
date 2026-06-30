// FUNC_NAME: EffectManager::triggerEffectAtPosition
// Address: 0x0054e970
// This function retrieves a 3D position from a nested pointer chain and passes it to an internal effect handler.

void __thiscall EffectManager::triggerEffectAtPosition(int param2)
{
    // Dereference nested pointers to reach the position source
    // this->field_0x14 -> some object -> field_0x30 -> another object -> field_0x18 -> position object
    int* ptrA = *(int**)((char*)this + 0x14);
    int* ptrB = *(int**)((char*)ptrA + 0x30);
    int* ptrC = *(int**)((char*)ptrB + 0x18);

    // Read position coordinates (float3) from offsets relative to ptrC
    float x = *(float*)((char*)ptrC + 0x30); // +0x30
    float y = *(float*)((char*)ptrC + 0x34); // +0x34
    float z = *(float*)((char*)ptrC + 0x38); // +0x38

    // Call internal effect function with the position pointer and additional parameters
    FUN_0054eb70(&x, param2, 0, 0, 0); // param2 likely an effect ID or target ID
}
```