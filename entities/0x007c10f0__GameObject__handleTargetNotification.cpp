// FUNC_NAME: GameObject::handleTargetNotification
void __fastcall GameObject::handleTargetNotification(int this) {
    // +0x91: active flag (byte)
    if (*(char*)(this + 0x91) == '\0')
        return;

    // +0x58: pointer to controller object
    int* pController = *(int**)(this + 0x58);

    // +0x98: pointer to a field inside the target object (offset 0x48 from target base)
    int targetFieldPtr = *(int*)(this + 0x98);

    // Sentinel value 0x48 indicates no valid target
    if (targetFieldPtr == 0 || targetFieldPtr == 0x48)
        return;

    // Recover base of target object by subtracting the field offset 0x48
    int* pTarget = (int*)(targetFieldPtr - 0x48);

    // +0x68c in target: some uint data (e.g., ID or flags)
    uint targetData = *(uint*)(pTarget + 0x68c);

    // Local buffer for data exchange with target's virtual function
    uint local_10 = targetData;          // copy for possible modification
    char local_c[12] = {0};             // 12‑byte buffer

    // vtable offset 0xa4 on target: likely a "getData" or "serialize" method
    (*(void (**)(char*, uint*))(*(int*)pTarget + 0xa4))(local_c, &local_10);

    // Extra local for second call's stack parameter
    char stack_buffer[4];

    // vtable offset 0x1e8 on controller: e.g., "sendEvent" or "processNotification"
    // Parameters: target object, event type (7), shifted data, stack buffer, 0, 0, 1
    (*(void (**)(int, int, uint, char*, int, int, int))(*(int*)pController + 0x1e8))(
        (int)pTarget,
        7,
        targetData >> 2,
        stack_buffer,
        0,
        0,
        1);
}