// FUNC_NAME: SimNpc::updateAnimationFromMovement
void __thiscall SimNpc::updateAnimationFromMovement(int* this) {
    int* animationController = reinterpret_cast<int*>(this[0x17]); // +0x5C: pointer to animation controller
    int transformData[2] = {0, 0}; // local_8, local_4: output from virtual call

    // +0x88: pointer to some component (e.g., skeleton or collider)
    int* component = nullptr;
    if (this[0x22] != 0) {
        component = reinterpret_cast<int*>(this[0x22] - 0x48);
    }

    // Call virtual function on component at vtable offset 0x1f8 to fill transform data
    if (component != nullptr) {
        (*(void (**)(int*, int*))(*(int*)component + 0x1f8))(animationController, transformData);
    }

    // Determine movement state via checks on transformData
    bool isMoving1 = FUN_008754b0(&transformData[0]);
    bool isMoving2 = FUN_008754e0(&transformData[0]);

    int animID;
    if (!isMoving1) {
        // Branch when first movement check fails (e.g., standing)
        animID = isMoving2 ? 0xFC1FBC38 : 0xA1C0912A;
    } else {
        // Branch when first movement check passes (e.g., moving)
        animID = isMoving2 ? 0xFC1FBC38 : 0x6E26083E;
    }

    // Update animation controller with desired state if component exists and isn't a sentinel
    if (this[0x22] != 0 && this[0x22] != 0x48) {
        FUN_00875af0(animationController, animID);
    }

    // If animation state is valid, play it
    if (FUN_0045f1b0(animID)) {
        (*(void (**)(int*, int, int, int, float, float))(*(int*)this + 0x2c))(
            animID, 1, 1, 0, 1.0f, 1.0f
        );
    }
}