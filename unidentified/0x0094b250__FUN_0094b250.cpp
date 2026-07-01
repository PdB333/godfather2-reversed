// FUNC_NAME: SomeClass::spawnSomeObjects
void __fastcall SomeClass::spawnSomeObjects(int this)
{
    undefined4 uVar1;
    uint uVar2;
    
    if (*(char *)(this + 0x70) != '\0') {
        uVar1 = FUN_00977420(); // Get some resource or manager
        uVar2 = 0;
        if (*(int *)(this + 100) != 0) {
            do {
                FUN_0094ae10(1, uVar1); // Spawn or create an object
                uVar2 = uVar2 + 1;
            } while (uVar2 < *(uint *)(this + 100)); // Loop count from member at +0x64
        }
    }
    return;
}