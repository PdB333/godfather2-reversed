// FUNC_NAME: Player::queryGameStateFlag
// Address: 0x0077c610
// This function serves as a central query dispatching system for various game state flags
// related to a player/NPC entity. It uses a switch on param_1 (flag ID) to return
// boolean results about the entity state, world state, or player capabilities.
// The parameter layout: param_1 = flag ID (case number), param_2 = pointer to entity data
// The entity data is accessed via *param_2 as a pointer to a large NPC/Player structure.

#include <cstdint>

// Forward declarations of helper functions
int FUN_00800ad0();
int FUN_0077be80(int* entity);
char FUN_0078bfd0();
int FUN_00717b00();
int FUN_007175b0();
char FUN_00690150(int id);
int FUN_00711680();
int FUN_007ff880();
int FUN_00716770();
int FUN_0071a610();
int FUN_00471610();
char FUN_00718d40(int param);
char FUN_00719910();
char FUN_0071abe0();
int FUN_00717b50();
int FUN_00716780();
int FUN_006e6410();
int FUN_006e5bb0(int param);
int FUN_00717c70();
int FUN_00717cc0();
int FUN_00711650();
int FUN_00765a60(int* entity);
int FUN_00716d40();
int FUN_006dd590();
char FUN_007193b0();
int FUN_00716440();
char FUN_00719f30(int param);
char FUN_00719550(int param);
int FUN_00710f00();
int FUN_00726890(int* entity);
int FUN_007174e0();
int FUN_00726870(int* entity);
char FUN_006eb940();
char FUN_00719860();
int FUN_00806440();
char FUN_0043c6c0(int* entity, int param);
int FUN_007867b0(int param1, int param2);
int FUN_00786720(int param);
int FUN_0071e270();
int FUN_00744860(int* entity);
int FUN_00746cc0(int* entity);
int FUN_007453d0(int* entity, int param);
int FUN_0077c5f0();
int FUN_006b07e0(int id);
int FUN_006ebfb0();
int FUN_007351e0();
char FUN_006aecf0(int* entity, float param1, int param2);
int FUN_0072ac50();
int FUN_0077dd80();
int FUN_006b0ee0(int id);
int FUN_006b4860();
int FUN_00746ba0(int* entity);
char FUN_0077bdf0();
char FUN_0077bdd0();
char FUN_0071a9b0();

// Function table entries (vtable offsets) used via function pointers
// Offset 0xbc: likely a method returning distance or angle
// Offset 0x28c: unknown method
// Offset 0x310, 0x314: methods on entity vtable

uint32_t FUN_0077c610(int flagID, int** param_2) {
    char cVar1;
    int iVar4, iVar5;
    int* piVar3;
    bool bVar8;
    float extraout_ST0;

    // Dereference to get the actual entity data pointer
    int* entity = *param_2;
    char result = 0;

    switch (flagID) {
    case 1:
        // Check if entity exists, global state valid, and specific flag at offset 0x8E0 (bit 10)
        if (((entity != nullptr) && (iVar5 = FUN_00800ad0(), iVar5 != 0)) &&
            (((uint32_t)entity[0x238] >> 10 & 1) != 0)) {
            return 1;
        }
        break;

    case 6:
        // Check bit 2 of entity[0x927]
        if (entity != nullptr) {
            return (uint32_t)entity[0x927] >> 2 & 1;
        }
        break;

    case 7:
        // Check if entity is not "beaten" and a global state is not active
        iVar5 = FUN_0077be80(entity); // likely isBeaten
        if (iVar5 == 0) {
            return 0;
        }
        cVar1 = FUN_0078bfd0(); // global dialogue or cutscene check
        return (uint32_t)(cVar1 == '\0'); // 1 if no cutscene active
        break;

    case 8:
        // Check some global state about combat
        if (entity != nullptr) {
            return FUN_00717b00();
        }
        break;

    case 9:
        // Check if some condition is true (maybe in combat)
        if ((entity != nullptr) && (iVar5 = FUN_007175b0(), iVar5 != 0)) {
            return 1;
        }
        break;

    case 10:
        // Check global flag ID 0x2e (46)
        if (entity != nullptr) {
            return (uint32_t)FUN_00690150(0x2e);
        }
        break;

    case 0xb:
        // Check if player exists (FUN_00711680) and a global countdown is active
        if (((entity != nullptr) && (iVar5 = FUN_00711680(), iVar5 != 0)) &&
            (iVar5 = FUN_007ff880(), iVar5 != 0)) {
            return 1;
        }
        break;

    case 0xc:
        // Like 0xb but also check offset 0xb74 in the global structure
        if ((((entity != nullptr) && (iVar5 = FUN_00711680(), iVar5 != 0)) &&
            (iVar5 = FUN_007ff880(), iVar5 != 0)) && (*(int*)(iVar5 + 0xb74) != 0)) {
            return 1;
        }
        break;

    case 0xe:
        // Check a specific player state
        if (entity != nullptr) {
            return FUN_00716770();
        }
        break;

    case 0xf:
        // Check another player state (aiming?)
        if (entity != nullptr) {
            return FUN_0071a610();
        }
        break;

    case 0x10:
        // Check if player can execute a takedown/execution
        if ((entity != nullptr) && (iVar5 = FUN_00711680(), iVar5 != 0)) {
            iVar4 = FUN_00471610(); // get current player
            cVar1 = FUN_00718d40(iVar4 + 0x30); // check distance/angle
            if ((cVar1 != '\0') &&
                ((cVar1 = (*(char(**)(void))(*(int*)entity + 0x314))(), // method check
                 cVar1 != '\0' &&
                 (cVar1 = (*(char(**)(int))(*(int*)entity + 0x310))(iVar5), // another check
                  cVar1 != '\0')))) {
                return 1;
            }
        }
        break;

    case 0x11:
        // Check disarming state
        if (entity != nullptr) {
            return FUN_00719910();
        }
        break;

    case 0x12:
        // Check if NPC is in a special state
        if (entity != nullptr) {
            return FUN_0071abe0();
        }
        break;

    case 0x14:
        // Check bit 10 of a global structure at offset 0x8E0
        if ((entity != nullptr) && (iVar5 = FUN_00711680(), iVar5 != 0)) {
            return (uint32_t)(((byte)(*(uint32_t*)(iVar5 + 0x8e0) >> 10) & 1) == 1);
        }
        break;

    case 0x15:
        // Check player reloading state
        if (entity != nullptr) {
            return FUN_00717b50();
        }
        break;

    case 0x16:
        // Check player melee state
        if (entity != nullptr) {
            return FUN_00716780();
        }
        break;

    case 0x17:
        // Check entity health state (maybe HP > 0)
        if (entity == nullptr) break;
        if (entity[0x877] != 0) {
            return *(byte*)(entity + 0x882) & 0xffffff01; // health/intensity byte
        }
        goto LAB_0077d350; // return true

    case 0x1a:
        // Check global flag 1 (likely intro done)
        if (entity != nullptr) {
            return (uint32_t)FUN_00690150(1);
        }
        break;

    case 0x1b:
        // Check if entity is in a vehicle and has health
        if (((entity != nullptr) && (iVar5 = FUN_006e6410(), entity[0x877] != 0)) && (iVar5 != 0)) {
            iVar5 = FUN_00471610();
            return FUN_006e5bb0(iVar5 + 0x30); // vehicle health check
        }
        break;

    case 0x1d:
        // Check player state (maybe crouching)
        if (entity != nullptr) {
            return FUN_00717c70();
        }
        break;

    case 0x1e:
        // Check if player exists (FUN_00711680 returns non-zero)
        if (entity != nullptr) {
            iVar5 = FUN_00711680();
            return (uint32_t)(iVar5 != 0);
        }
        break;

    case 0x1f:
        // Check player in-vehicle state
        if (entity != nullptr) {
            return FUN_00717cc0();
        }
        break;

    case 0x21:
        // Check if entity is not the same as the current player
        if (entity == nullptr) break;
        iVar5 = FUN_00711680();
        if (iVar5 == 0) {
            return 0;
        }
        piVar3 = (int*)FUN_00711650(); // get current player entity
        if (piVar3 == entity) {
            return 0; // entity is the player, return false
        }
        goto LAB_0077d350; // entity is not the player (NPC), return true

    case 0x22:
        // Check if there is a player and a specific global state
        if (entity == nullptr) break;
        iVar5 = FUN_00711680();
        if ((iVar5 == 0) || (cVar1 = FUN_00690150(0x2e), cVar1 == '\0')) {
            return 0;
        }
        goto LAB_0077d350;

    case 0x23:
        // Check specific entity flag (maybe "aware" or "alerted")
        if (entity != nullptr) {
            return FUN_00765a60(entity);
        }
        break;

    case 0x24:
        // Check if entity health value at offset 0x877 differs from another health at 0x87b
        // (likely max health vs current health)
        if (entity != nullptr) {
            return (uint32_t)(entity[0x877] != entity[0x87b]);
        }
        break;

    case 0x28:
        // Check distance/angle using vtable method at offset 0xbc
        if ((entity == nullptr) || (iVar5 = FUN_00711680(), iVar5 == 0)) break;
        (*(void(**)(int))(*(int*)entity + 0xbc))(iVar5); // method that sets extraout_ST0
        if (extraout_ST0 <= (float)0) {
            return 0;
        }
        goto LAB_0077d350;

    case 0x29:
        // Check bit 11 of entity[0x7d6] (maybe a stance/cover flag)
        if (entity != nullptr) {
            return (uint32_t)entity[0x7d6] >> 0xb & 1;
        }
        break;

    case 0x2a:
        // Check player reloading or ammo state
        if (entity != nullptr) {
            return FUN_00716d40();
        }
        break;

    case 0x2b:
        // Check if entity is in a special vehicle mode (like ramming)
        if (entity == nullptr) break;
        if (((((uint32_t)entity[0x238] >> 10 & 1) == 0) || (iVar5 = FUN_006dd590(), iVar5 == 0)) ||
            (iVar5 = FUN_006dd590(), (*(uint32_t*)(iVar5 + 0x1d0) >> 3 & 1) == 0)) {
            return 0;
        }
        goto LAB_0077d350;

    case 0x2c:
        // Check if entity can perform some action (maybe combat action)
        if (entity == nullptr) break;
        cVar1 = FUN_007193b0(); // check player action availability
        if (cVar1 == '\0') {
            return 0;
        }
        // Further checks
        // (This pattern looks like a compound check for action eligibility)
        {
            int uVar2 = FUN_00716440(); // get some parameter
            cVar1 = FUN_00719f30(uVar2); // check it
            if (cVar1 == '\0') {
                return 0;
            }
        }
        goto LAB_0077d350;

    case 0x2e:
        // Check if player is in a specific state (dialogue-related)
        if (((entity == nullptr) || (iVar5 = FUN_00711680(), iVar5 == 0)) ||
            ((iVar5 = FUN_00711650(), iVar5 != 0 && (piVar3 = (int*)FUN_00711650(), entity != piVar3)))
            ) break;
        cVar1 = FUN_00690150(0x38); // talking
        if (((cVar1 == '\0') && (cVar1 = FUN_00690150(0x37), cVar1 == '\0')) && // not in dialogue
            (cVar1 = FUN_00690150(0x39), cVar1 == '\0')) { // not in cutscene
            return 0;
        }
        goto LAB_0077d350;

    case 0x2f:
        // Check player aim state
        if (entity != nullptr) {
            return FUN_00719550(0); // 0 = not aiming?
        }
        break;

    case 0x30:
        // Check some player ability
        if (entity != nullptr) {
            return FUN_00710f00();
        }
        break;

    case 0x31:
        // Check entity weapon type/model info
        if (((entity != nullptr) && (iVar5 = FUN_00726890(entity), iVar5 != 0)) &&
            (*(int*)(iVar5 + 0x14) != 0)) {
            return 1;
        }
        break;

    case 0x34:
        // Check player melee attack availability
        if (entity != nullptr) {
            return FUN_007174e0();
        }
        break;

    case 0x37:
        // Check entity weapon and some global state
        if ((((entity != nullptr) && (piVar3 = (int*)FUN_00726870(entity), piVar3 != nullptr))
            && (cVar1 = FUN_006eb940(), cVar1 != '\0')) &&
            (cVar1 = (*(char(**)(int))(*(int*)piVar3 + 0x1c))(0x100), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x3b:
        // Check special ability state
        if ((entity != nullptr) && (cVar1 = FUN_00719860(), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x3d:
        // Compare game mode (FUN_00806440) to 2
        iVar5 = FUN_00806440();
        bVar8 = iVar5 == 2;
        goto LAB_0077d34e;

    case 0x3e:
        // Check with a global data reference
        cVar1 = FUN_0043c6c0(entity, 0x00e52468); // check translation of some data
        if (cVar1 != '\0') {
            return 1;
        }
        break;

    case 0x3f:
        // Check vehicle health status (player's current vehicle)
        iVar5 = FUN_00471610();
        iVar5 = FUN_007867b0(iVar5 + 0x30, 0); // get vehicle component
        if (iVar5 == 0) {
            return 0;
        }
        return *(byte*)(iVar5 + 0x2c) & 0xffffff01; // vehicle health byte

    case 0x40:
        // Check global game state at fixed address
        return (uint32_t)(*(int*)(0x0112aa1c + 0x1a3c) != 0);

    case 0x41:
        // Check if player is in a vehicle
        iVar5 = FUN_00471610();
        iVar5 = FUN_00786720(iVar5 + 0x30);
        return (uint32_t)(iVar5 != 0);

    case 0x42:
        // Check takedown state
        if (entity != nullptr) {
            iVar5 = FUN_0071e270();
            return (uint32_t)(iVar5 != 0);
        }
        break;

    case 0x43:
        // Dedicated function check for some entity state
        return FUN_00744860(entity);

    case 0x44:
        // Another dedicated check
        return FUN_00746cc0(entity);

    case 0x45:
        // Check with parameter 1
        return FUN_007453d0(entity, 1);

    case 0x46:
        // Check entity weapon and global state
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            (cVar1 = FUN_006eb940(), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x47:
        // Check entity weapon and flag at offset 0x48 (bit 4 and 5)
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((cVar1 = FUN_006eb940(), cVar1 != '\0' && ((*(byte*)(iVar5 + 0x48) & 0x30) != 0)))) {
            return 1;
        }
        break;

    case 0x48:
        // Check weapon and flag at offset 0x48 (bit 6 and 7)
        if ((((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            (cVar1 = FUN_006eb940(), cVar1 != '\0')) && ((*(byte*)(iVar5 + 0x48) & 0xc0) != 0)) {
            return 1;
        }
        break;

    case 0x49:
        // Check some state with a entity index from offset 0x948
        if (entity != nullptr) {
            return FUN_0074c1b0(entity, entity[0x948]);
        }
        break;

    case 0x4b:
        // Check if a specific global function returns non-zero
        if (entity != nullptr) {
            iVar5 = FUN_0077c5f0();
            return (uint32_t)(iVar5 != 0);
        }
        break;

    case 0x4c: // Fall-through
    case 0x51:
        // Check car door interaction (driver/passenger door)
        if (((entity == nullptr) || (iVar5 = FUN_00806440(), iVar5 != 3)) ||
            ((entity[0x84d] == 0 ||
             ((iVar5 = FUN_006b07e0(entity[0x84d]), iVar5 == 0 ||
              (iVar5 = *(int*)(*(int*)(iVar5 + 0x180) + 0xfc), iVar5 == 0)))))) break;
        iVar4 = FUN_006ebfb0(); // get current player ID
        if (*(int*)(iVar5 + 0x14) != iVar4) { // driver seat player ID
            iVar4 = FUN_006ebfb0();
            bVar8 = *(int*)(iVar5 + 0x18) == iVar4; // passenger seat check
            goto LAB_0077d34e;
        }
        goto LAB_0077d350;

    case 0x4d: // Fall-through
    case 0x52:
        // Check car door interaction with distance check
        if ((((entity != nullptr) && (iVar5 = FUN_00806440(), iVar5 == 3)) && (entity[0x84d] != 0)) &&
            ((iVar5 = FUN_006b07e0(entity[0x84d]), iVar5 != 0 &&
             (cVar1 = FUN_006aecf0(entity, 1.0f, 0), cVar1 != '\0')))) { // distance check
            return 1;
        }
        break;

    case 0x4e:
        // Check if some action is available (maybe car-jacking)
        if (entity == nullptr) break;
        cVar1 = FUN_00690150(0x16); // check "carjack" flag
        if (cVar1 == '\0') {
            iVar5 = FUN_0077bea0(entity); // check if car is locked
            if ((iVar5 == 0) || (iVar5 = FUN_0077bed0(), iVar5 == 0)) break; // check some state
            cVar1 = FUN_00690150(0x15); // check other flag
            goto LAB_0077d34c;
        }
        goto LAB_0077d350;

    case 0x4f:
        // Check one specific global flag
        if ((entity != nullptr) && (cVar1 = FUN_00690150(0x15), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x50:
        // Complex check involving car interaction and flags
        if ((((entity == nullptr) ||
             ((iVar5 = entity[0x84d], iVar5 == 0 && (iVar5 = entity[0x7ba], iVar5 == 0)))) ||
            (iVar5 = FUN_006b07e0(iVar5), iVar5 == 0)) ||
           ((*(int*)(*(int*)(iVar5 + 0x180) + 0xd8) == 0 ||
            (*(int*)(*(int*)(iVar5 + 0x180) + 0x40) == entity[0x7b5])))) break;
        cVar1 = FUN_00690150(0x15); // check flag
        if (cVar1 != '\0') {
            cVar1 = FUN_00690150(0x16); // check other flag
            if (cVar1 != '\0') {
                return 1;
            }
            break;
        }
        goto LAB_0077d350;

    case 0x53:
        // Check melee state on a global structure
        if ((((entity != nullptr) && (entity[0x84d] != 0)) && (iVar5 = FUN_007351e0(), iVar5 != 0)) &&
            ((*(uint32_t*)(iVar5 + 0x5c) >> 0x1b & 1) != 0)) { // bit 27 of some flag
            return 1;
        }
        break;

    case 0x54:
        // Check weapon flag at offset 0x44 bit 6
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 0x40) != 0)) {
            return 1;
        }
        break;

    case 0x55:
        // Check weapon flag at offset 0x44 bit 2
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 4) != 0)) {
            return 1;
        }
        break;

    case 0x56:
        // Check weapon flag at offset 0x44 bit 3
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 8) != 0)) {
            return 1;
        }
        break;

    case 0x57:
        // Check weapon flag at offset 0x44 bit 4
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 0x10) != 0)) {
            return 1;
        }
        break;

    case 0x58:
        // Check weapon flag at offset 0x44 bit 5
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 0x20) != 0)) {
            return 1;
        }
        break;

    case 0x59:
        // Check weapon flag at offset 0x44 bit 7
        if (((entity != nullptr) && (iVar5 = FUN_00726870(entity), iVar5 != 0)) &&
            ((*(byte*)(iVar5 + 0x44) & 0x80) != 0)) {
            return 1;
        }
        break;

    case 0x5a:
        // Check entity stance flag at offset 0x7d5 bit 8
        if ((entity != nullptr) && (((uint32_t)entity[0x7d5] >> 8 & 1) != 0)) {
            return 1;
        }
        break;

    case 0x5b:
        // Check entity stance flag at offset 0x7d6 bit 0
        if ((entity != nullptr) && ((*(byte*)(entity + 0x7d6) & 1) != 0)) {
            return 1;
        }
        break;

    case 0x5c:
        // Check if in special state and invert a flag
        cVar1 = FUN_0071abe0();
        if (cVar1 != '\0') {
            return (byte)~(byte)((uint32_t)entity[0x882] >> 2) & 0xffffff01;
        }
        break;

    case 0x5d:
        // Check some interaction state
        if ((entity != nullptr) && (cVar1 = FUN_0072ac50(), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x5e:
        // Compare entity value at offset 0x960 with some max
        if ((entity != nullptr) && (iVar5 = entity[0x960], iVar4 = FUN_0077dd80(), iVar5 < iVar4)) {
            return 1;
        }
        break;

    case 0x5f:
        // Compare entity value at offset 0x960 with some max (inverse)
        if ((entity != nullptr) && (iVar5 = entity[0x960], iVar4 = FUN_0077dd80(), iVar4 < iVar5)) {
            return 1;
        }
        break;

    case 0x60:
    case 0x61:
    case 0x62:
    case 99: // 0x63
        // Compare entity value at offset 0x960 with flagID minus 0x60
        if (entity == nullptr) break;
        bVar8 = entity[0x960] == flagID + -0x60;
        goto LAB_0077d34e;

    case 0x66:
        // Check vehicle type (probably a car variant)
        if (((entity != nullptr) && (entity[0x84d] != 0)) &&
            ((iVar5 = FUN_006b0ee0(entity[0x84d]), iVar5 != 0 &&
             (iVar5 = FUN_006b4860(), iVar5 - 3U < 2)))) {
            return 1;
        }
        break;

    case 0x67:
        // Check two possible entity fields for specific class id (0x20 = 32)
        iVar5 = entity[0x961];
        if (((iVar5 == 0) || (iVar5 == 0x48)) || (*(int*)(iVar5 + 0xc) != 0x20)) {
            iVar5 = entity[0x963];
            if ((iVar5 == 0) || (iVar5 == 0x48)) break;
            bVar8 = *(int*)(iVar5 + 0xc) == 0x20;
            goto LAB_0077d34e;
        }
        goto LAB_0077d350;

    case 0x68:
        // Check entity and some target state (likely cover-related)
        iVar5 = FUN_00746ba0(entity);
        if ((iVar5 != 0) && (cVar1 = FUN_0077bdf0(), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x69:
        // Similar to 0x68 but different target state
        iVar5 = FUN_00746ba0(entity);
        if ((iVar5 != 0) && (cVar1 = FUN_0077bdd0(), cVar1 != '\0')) {
            return 1;
        }
        break;

    case 0x6a:
        // Check entity flag at offset 0x7d7 bit 30, then translation check
        if (((uint32_t)entity[0x7d7] >> 0x1e & 1) == 0) break;
        cVar1 = FUN_0043c6c0(entity, 0x00e52468);
        goto LAB_0077d34c;

    case 0x6b:
        // Call vtable method at offset 0x28c
        cVar1 = (*(char(**)(void))(*(int*)entity + 0x28c))();
        if (cVar1 != '\0') {
            return 1;
        }
        break;

    case 0x6c:
        cVar1 = FUN_0071a9b0();
LAB_0077d34c:
        bVar8 = cVar1 == '\0';
LAB_0077d34e:
        if (!bVar8) break;
LAB_0077d350:
        result = 1;
        break;

    case 0x6d:
    case 0x6e:
        // Check entity flag at offset 0x927 bit 4
        if ((entity != nullptr) && (((uint32_t)entity[0x927] >> 4 & 1) != 0)) {
            return 1;
        }
    }

    return (uint32_t)result;
}