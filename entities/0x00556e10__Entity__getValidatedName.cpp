// FUNC_NAME: Entity::getValidatedName
undefined4 __thiscall Entity::getValidatedName(Entity *this) {
  int resourceId;
  int *manager;
  char *name;

  resourceId = this->nameId;  // +0x40, likely an ID into a string table
  if (resourceId != 0) {
    manager = (int *)(*(code **)(*gStringTableManager + 0x14))();  // getManager() static call
    name = (char *)(*(code **)(*manager + 0x10))(resourceId);     // getStringById
    name = (char *)FUN_00ab06f0(&stack0xfffffffb, name);          // copy or verify string
    if (*name == '\0') {
      return 0  // return null if empty
    }
  }
  return this->nameId;  // return original pointer/ID
}