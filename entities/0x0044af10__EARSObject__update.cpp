// FUNC_NAME: EARSObject::update
class EARSObject {
public:
    char m_bDirty; // +0x14 - non-zero indicates pending update
    bool checkCanUpdate(int* pContext); // FUN_0044b390
    void doActualUpdate(); // FUN_0044a7c0

    void update();
};

void EARSObject::update() {
    if (m_bDirty != 0) {
        int context = 0; // local placeholder
        if (checkCanUpdate(&context)) {
            return;
        }
    }
    doActualUpdate();
}