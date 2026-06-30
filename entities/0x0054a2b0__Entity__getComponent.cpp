// FUNC_NAME: Entity::getComponent
enum eComponentType {
    kComponentType_Wrapper = 0xB,
    kComponentType_Actual = 0xA
};

struct Component { // Base component layout
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int type; // +0x0C: component type identifier
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
    int field_0x24;
    int field_0x28;
    int field_0x2C;
    int field_0x30;
    Component* wrapperTarget; // +0x34: only valid when type == kComponentType_Wrapper
};

struct ObjectWithComponent {
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0C;
    Component* component; // +0x10
};

// __thiscall: first parameter (this) in ecx
int __thiscall Entity::getComponent(ObjectWithComponent* thisObj) {
    Component* comp = thisObj->component; // deref +0x10
    if (comp == nullptr) {
        return 0;
    }

    int type = comp->type; // +0x0C
    if (type == kComponentType_Wrapper) {
        comp = comp->wrapperTarget; // +0x34
        if (comp == nullptr) {
            return 0;
        }
        type = comp->type; // update type to target's type
    }

    // Return component if it is the desired type (0xA)
    if (type == kComponentType_Actual) {
        return (int)comp;
    }

    return 0;
}