// FUN_NAME: GameObject::receiveUpdate (0x0045f9e0)
// 
// Function: Receives an update/message and applies it to the object's data field at offset 0x34.
// The virtual function at vtable+0xa0 retrieves the class name (8‑byte string) to identify the update type.
// Then delegates to a common apply function (FUN_0045c230) for dispatch.
// 
// Note: uStack_4 (first arg of applyMessage) is likely the original param_2, but Ghidra's decompilation
// shows an uninitialized local; we preserve the intended logic.

void __thiscall GameObject::receiveUpdate(GameObject* thisPtr, int msgArg, int msgData) {
    char className[8];   // 8‑byte class name buffer (e.g., "Vehicle", "Weapon")
    int tempArg = msgData; // copy of the message data

    // Call the virtual method to get the class name (vtable offset 0xa0)
    (*(void (__thiscall*)(GameObject*, char*))((int*)(*(int*)thisPtr) + 0xa0))(thisPtr, className);

    // Dispatch the message using the class name, the message data pointer, and the object's data block at +0x34
    applyMessageForClass(msgArg, &tempArg, &thisPtr->dataBlock_0x34);
}