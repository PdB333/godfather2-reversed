// FUNC_NAME: GameObject::destroy
void __fastcall GameObject::destroy(GameObject* this)
{
    // Release child object at offset +0x3C (param_1[0xf])
    if (this->field_0x3C != 0) {
        releaseObject(this->field_0x3C); // FUN_009c8f10
    }

    // Global cleanup (e.g., garbage collection or memory manager flush)
    globalCleanup(); // FUN_00498180

    // Release object at offset +0x14 (param_1[5])
    releaseObject(this->field_0x14); // FUN_009c8f10

    // Dereference first field (offset +0x00) to get a secondary pointer
    GameObject* secondary = this->field_0x00;
    if (secondary != 0) {
        // Release object at offset +0x30 from secondary
        releaseObject(secondary->field_0x30); // FUN_009c8f10
        // Destroy the secondary object itself
        destroyObject(secondary); // FUN_009c8eb0
    }
}