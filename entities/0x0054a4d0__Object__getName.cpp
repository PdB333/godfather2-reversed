// FUNC_NAME: Object::getName
char* __fastcall Object::getName(Object* this) {
    return *(char**)((char*)this + 8);
}