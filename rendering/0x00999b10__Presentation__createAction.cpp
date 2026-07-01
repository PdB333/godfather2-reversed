// FUNC_NAME: Presentation::createAction
// Address: 0x00999b10
// Reconstructed C++ from Ghidra decompilation

class ActionObject; // forward declaration

ActionObject* Presentation::createAction(int32 param1, int32 param2) {
    // Get current game manager (likely GodfatherGameManager singleton)
    GodfatherGameManager* gameMgr = reinterpret_cast<GodfatherGameManager*>(FUN_004a37d0());
    if (!gameMgr) return nullptr;

    // Check game manager's internal data and type ID (0x33a16735 = magic?)
    if (gameMgr->field_0x1c == nullptr) return nullptr;
    if (gameMgr->typeId != 0x33a16735) return nullptr;

    // Access a sub-object at +0x14 from the internal data at +0x1c
    void* internalObj = *reinterpret_cast<void**>(reinterpret_cast<uint8*>(gameMgr->field_0x1c) + 0x14);
    if (!internalObj) return nullptr;

    // Get local player (using FUN_0054a4d0)
    Player* localPlayer = reinterpret_cast<Player*>(FUN_0054a4d0());
    if (!localPlayer) return nullptr;

    // Allocate 0x10 bytes for the action object
    ActionObject* newAction = reinterpret_cast<ActionObject*>(FUN_00999990(0x10));
    if (!newAction) return nullptr;

    // Initialize vtable (pointing to global vtable at 0x00d92308)
    newAction->vtable = reinterpret_cast<void**>(&PTR_LAB_00d92308);
    newAction->field_0x04 = param1;
    newAction->field_0x08 = param2;
    newAction->field_0x0C = localPlayer;

    return newAction;
}