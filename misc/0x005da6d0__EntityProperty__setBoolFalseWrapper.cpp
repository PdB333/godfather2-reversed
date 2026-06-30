// FUNC_NAME: EntityProperty::setBoolFalseWrapper
void __fastcall setBoolFalseWrapper(void* unusedThis, void* objectPtr, int unusedParam, int propertyId)
{
    // Calls internal set-property function with (objectPtr, propertyId, FALSE)
    // param_1 (ecx) ignored; param_3 (stack) unused.
    // The inner function (0x005dab00) likely sets a boolean flag on an entity or component.
    FUN_005dab00(objectPtr, propertyId, 0);
}