// FUNC_NAME: doubleUpdate
void* __thiscall doubleUpdate(void* this) {
    int i = 2;
    do {
        FUN_008d5df0(); // calls some update function twice
        i = i - 1;
    } while (i != 0);
    return this;
}