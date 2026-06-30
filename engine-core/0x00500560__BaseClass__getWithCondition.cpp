// FUNC_NAME: BaseClass::getWithCondition
// Function address: 0x00500560
// Role: Conditional getter - returns internal value if flag is non-zero, else 0.
// Parameter: param_2 is a boolean/int condition.
// Internal call at 0x00500120 likely performs actual retrieval.

int BaseClass::getWithCondition(int condition) {
    if (condition != 0) {
        return this->internalGetValue(); // calls FUN_00500120(this)
    }
    return 0;
}