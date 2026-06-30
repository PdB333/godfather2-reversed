// FUNC_NAME: ActionOptions::constructor

void __thiscall ActionOptions::constructor(ActionOptions* this, int param) {
    *(int*)((char*)this + 0x40) = 0;   // +0x40: some integer field
    *(int*)((char*)this + 0x2c) = param; // +0x2c: store passed parameter
    *(int*)((char*)this + 0x28) = 0;   // +0x28: another integer
    *(char*)((char*)this + 0x25) = 1;  // +0x25: boolean flag
    *(char*)((char*)this + 0x24) = 1;  // +0x24: boolean flag
    *(char*)((char*)this + 0x38) = 0;  // +0x38: boolean flag
    FUN_0040b7a0(); // calls a base initialization helper
}