// FUNC_NAME: ObjectFactory::createFromHash
int* ObjectFactory::createFromHash(uint32_t hash, void* owner, int param3)
{
    int* obj = nullptr;

    if (hash == 0x4ecfbe13) {
        obj = (int*)FUN_00851630(owner, 0); // e.g., createPlayer
    }
    else if (hash == 0x332d5a20) {
        obj = (int*)FUN_008517c0(owner, 0); // e.g., createVehicle
    }
    else if (hash == 0xF26FB213) { // -0xd9047ed as unsigned
        obj = (int*)FUN_008518b0(owner, 0); // e.g., createBuilding
    }
    else {
        return nullptr;
    }

    if (obj != nullptr) {
        // Call virtual function at vtable+4 (likely init or setup)
        (*(void (**)(void*))(*(int*)obj + 4))(owner);

        if (param3 == 0) {
            // Copy string from global to object at offset 0x3C (0xF * 4)
            FUN_00408b80(&DAT_0120e93c, obj + 0xF, 0);
            // Set function pointer at offset 0x158 (0x56 * 4)
            obj[0x56] = (int)&LAB_00707ff0;
            return obj;
        }

        int* somePtr = (int*)FUN_004025a0(param3); // likely cast to some type
        if (somePtr != nullptr && somePtr[0x24 / 4] == 3) { // check field at +0x24
            FUN_00408b80(&DAT_0120e93c, obj + 0xF, 0);
        }
    }
    return obj;
}