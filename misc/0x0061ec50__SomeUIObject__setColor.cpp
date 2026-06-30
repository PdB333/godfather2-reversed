// FUNC_NAME: SomeUIObject::setColor
void __fastcall SomeUIObject::setColor(int param_1)
{
    int iVar1;
    int in_EAX; // this pointer

    // Check if sub-object exists (this+0x98 is pointer to something)
    if (*(int *)(in_EAX + 0x98) != 0) {
        iVar1 = *(int *)(in_EAX + 0x9c); // sub-object at this+0x9c

        if (param_1 == 0) {
            // Build default color resource string "placeholder.color"
            int uVar2 = FUN_00ab8560(0, "placeholder", 0xb);
            uVar2 = FUN_00ab8560(uVar2, "color", 5);
            // Convert resource to color handle
            uVar2 = FUN_00611000(uVar2);
            // Store color handle at sub-object+0xbc
            *(int *)(iVar1 + 0xbc) = uVar2;
            return;
        }
        // Otherwise directly use the provided color handle
        *(int *)(iVar1 + 0xbc) = param_1;
    }
}