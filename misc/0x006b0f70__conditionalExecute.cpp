// FUNC_NAME: conditionalExecute
bool checkCondition(int param); // FUN_006b0ee0
void performAction(int param);  // FUN_006b25c0

void conditionalExecute(int param1, int param2)
{
    if (checkCondition(param1) != 0) {
        performAction(param2);
    }
    return;
}