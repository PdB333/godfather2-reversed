// FUNC_NAME: Object::callMethodFromTable
// Address: 0x007ef560
// Calls a function through a pointer at offset 0x2c and then offset 4.
// This pattern is typical of an indirect virtual method call or a dispatch via a function table.
void Object::callMethodFromTable() {
    // Read pointer from this + 0x2c (points to a function table structure)
    // Then read pointer at offset 4 from that table (second function) and call it
    (*(void (**)())(*(int*)((int)this + 0x2c) + 4))();
}