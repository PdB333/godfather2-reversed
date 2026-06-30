// FUNC_NAME: GameObject::release
void __thiscall GameObject::release(GameObject* this) {
    // Offset +0x34: bit0 = released flag
    if ((this->flags_34 & 1) == 0) {
        this->flags_34 |= 1; // Mark as released

        // Release the sub-object at +0x16c (e.g., animation component)
        if (this->childObject_16c != 0) {
            releaseChildObject(this->childObject_16c, 0); // FUN_006b4e30
        }

        // The following condition is dead code because the flag was just set.
        if (((this->flags_34 & 1) == 0) && (this->somePtr_40 != 0)) {
            int conditionResult = checkSomeCondition(this->somePtr_40); // FUN_008c74d0
            if ((conditionResult != 0) && ((~(conditionResult->field_84 >> 5) & 1) != 0)) {
                return; // Early return (unreachable after flag set)
            }
        }

        // Free the resource pointer at +0x19c
        if (this->resourcePtr_19c != 0) {
            freeResource(this->resourcePtr_19c); // FUN_0094b0e0
            this->resourcePtr_19c = 0;
        }
    }
}