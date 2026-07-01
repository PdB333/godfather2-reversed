// FUNC_NAME: GameObject::conditionalProcess
// Function address: 0x008c78f0
void GameObject::conditionalProcess(GameObject* otherObject) {
    // Check if this object meets a condition (FUN_008c74d0)
    if (this->checkCondition()) {
        // If condition met, perform some action on otherObject (FUN_008c3240)
        otherObject->handleEvent();
    }
}