// FUNC_NAME: checkIfStateInSet
// Address: 0x0074c060
// Role: Returns 1 if the integer at object+0x94 is 3, 4, 5, or 6; otherwise 0.
// Likely checks a state enum (e.g., vehicle driving/crash states or NPC activity states).
int __thiscall checkIfStateInSet(void* thisPtr) {
    int state = *(int*)((char*)thisPtr + 0x94); // +0x94: state field
    if (state == 3 || state == 4 || state == 5 || state == 6) {
        return 1;
    }
    return 0;
}