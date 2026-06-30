// FUNC_NAME: GameObject::checkAndCallUpdate
// Function address: 0x006a2b90
// Role: Calls a method via function pointer at this+0x98 if FUN_006a2950 returns true.
// Likely part of a game object update loop where a condition must be met before executing an action.

void __thiscall GameObject::checkAndCallUpdate(GameObject* this)
{
    char conditionResult;

    // Check some condition (likely whether the object is active or should update)
    conditionResult = FUN_006a2950();
    if (conditionResult != '\0') {
        // Call the function pointer stored at offset 0x98 in the object.
        // This is likely a virtual method or callback (e.g., onUpdate, execute, etc.)
        (*(void (__thiscall **)(GameObject*))(*(int*)this + 0x98))(this);
    }
}