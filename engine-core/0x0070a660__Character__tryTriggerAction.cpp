// FUNC_NAME: Character::tryTriggerAction
void __fastcall Character::tryTriggerAction(Character* this)
{
    // Check if bit 0 at offset 0x39f is cleared and a pointer at +0x2d0 exists
    if (((*(byte *)(this + 0x39f) & 1) == 0) && (*(int *)(this + 0x2d0) != 0)) {
        // Set flag bit 0x100 at offset 0x39e
        *(ushort *)(this + 0x39e) |= 0x100;
        // Trigger animation controller action
        FUN_009f1f90(*(undefined4 *)(this + 0x2d0));
        // Notify animation system
        FUN_009f0190();
    }
}