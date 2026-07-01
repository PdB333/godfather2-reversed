// FUNC_NAME: Entity::getOrCreateComponent
void __fastcall Entity::getOrCreateComponent(int thisPtr)
{
    if (*(int *)(thisPtr + 0x60) == 0) {
        // Lazy initialize the component pointer at +0x60 using the key at +0x50
        int componentKey = thisPtr + 0x50;
        *(int *)(thisPtr + 0x60) = FUN_00446100(componentKey, 0);
    }
    return;
}