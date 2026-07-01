// FUNC_NAME: AptCharacter::update
void AptCharacter::update(int flag) {
    // Debug assertion checking for null pRect
    if (flag == 0) {
        const char* assertExpr = "pRect";
        const char* file = "..\\source\\Apt\\AptCharacter.cpp";
        int line = 0x464; // 1124
        int assertType = 2; // severity
        // Simplified assertion logic; actual implementation would call EA assertion handler
        if (pRect == nullptr) {
            __debugbreak(); // break into debugger
        }
    }

    // Static transform data used for character updates
    static double transformData[3]; // equivalent to local_18, local_10, local_8
    // Initialize from global data
    transformData[0] = DAT_0119cbf4; // double
    transformData[1] = DAT_0119cbfc;
    transformData[2] = DAT_0119cc04;

    // Iterate over linked list of child nodes or related objects
    Node* node = *(Node**)(this + 0x54); // linked list head at +0x54
    while (node != nullptr) {
        FUN_005b4540(&transformData); // apply transform to each node
        node = node->next; // next pointer also at +0x54
    }

    // Update rect data
    FUN_005b4270();

    // Global transform + apply + call vfunc
    Transform3D* globalTransform = (Transform3D*)(DAT_0119cbf0 + 0x220);
    FUN_005b4540(globalTransform);
    ((void(*)(Transform3D*))DAT_0119cb68)(globalTransform); // function pointer call

    // Character finalization
    FUN_005b5a40(this);
    FUN_005b4350();
}