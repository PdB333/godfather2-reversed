// FUNC_NAME: GameEntity::tryPerformAction

#include <cstdint>

// Forward declarations for internal structures
struct GameEntity;
struct EntityManager;
struct GameEnvironment;

// Internal function signatures (renamed for clarity)
GameEntity* resolveEntity(uint32_t entityId); // FUN_006f5dd0
bool isActionTypeBlocked(uint32_t actionFlags); // FUN_006f3db0
bool isGameModeActive(); // FUN_007f47a0 (checks global gameplay state)
bool isInCombat(); // FUN_007f7c60 (checks if currently in combat)
bool hasLineOfSight(); // FUN_006f0940
bool isTargetValid(); // FUN_006f3c30
bool canEntityBeTargeted(GameEntity* target, GameEntity* performer, uint32_t flags); // FUN_006f5940
void updateActionCooldown(GameEntity* entity); // FUN_006f5870
bool executeAction(uint32_t entityId, int32_t duration, bool flag, uint32_t unknown1, uint32_t flags, uint32_t param3_modified, uint32_t param3_shifted, uint32_t unknown2); // FUN_006f3e10
void markActionPerformed(GameEntity* entity); // FUN_006f58d0

// External global pointer (probably to GameManager)
extern void* g_globalGameData; // DAT_012233a0

// Structure offsets for GameEntity (based on decompiled usage)
// +0x1c : bitmask of entity state flags
// +0x... (param_1[3] offset 0x0C) points to some manager, possibly containing +0x1ed4 as a hash or ID

// This function validates and potentially executes an action (e.g., attack, interact) on an entity.
// Returns 1 on success, 0 on failure.
char __thiscall GameEntity::tryPerformAction(GameEntity* this, uint32_t entityId, uint32_t actionFlags, uint32_t param4, uint32_t param5)
{
    char result = '\0';

    // Resolve entity ID to a pointer
    GameEntity* target = resolveEntity(entityId);
    if (target == nullptr) {
        return '\0';
    }

    // Check if this action type is globally blocked
    if (isActionTypeBlocked(actionFlags)) {
        return '\0';
    }

    // Get manager pointer from this object (offset 0x0C)
    int* managerPtr = this->field_0x0C; // this[3] -> offset 12 bytes
    // Access global game data pointer +4 to get some game singleton
    void** globalBase = *(void***)(g_globalGameData);
    int* gameInstance;
    if (globalBase[0] == nullptr) {
        gameInstance = nullptr;
    } else {
        // Subtract 0x1f30 to get a meaningful pointer (likely offset in structure)
        gameInstance = (int*)((uintptr_t)globalBase[0] - 0x1f30);
    }

    uint32_t isForceAction = actionFlags & 0x100;
    bool allowForce = false;

    // Check if force action is allowed
    if ((isForceAction == 0) &&
        ((((target->flags & 0x20) == 0) && (isGameModeActive())) ||
         ((gameInstance != nullptr) &&
          ((isGameModeActive() && ((target->flags & 0x40) == 0)))))) {
        allowForce = true;
    }

    bool canExecute = true;
    // Global check: if entity has 0x800 flag and game not in combat -> can't execute
    if (((target->flags & 0x800) != 0) && (isInCombat())) {
        canExecute = false;
    }

    // Another condition: if target has high-tier invulnerability flag and manager+0x1ed4 matches specific hash
    // and not in combat -> can't execute
    if ((((target->flags & 0x100000) != 0) && (managerPtr[0x1ed4 / 4] == 0x637b907)) &&
        (isInCombat()) && (!isInCombat())) { // note the contradiction in decompiled (second call returns 0)
        canExecute = false;
    }

    // Final validation checks before execution
    if ((!allowForce) && (canExecute)) {
        if ((!hasLineOfSight()) &&
            ((!isTargetValid()) || ((actionFlags & 2) != 0))) {
            // one of checks passed? Actually logic is:
            // if (hasLineOfSight()==0) && (isTargetValid()==0 OR actionFlags & 2)
            // and then proceed only if (isForceAction !=0 OR canEntityBeTargeted(...)!=0 OR actionFlags & 2)
        }
        else {
            // Invalid state, do not execute
            return result;
        }
    }

    // Additional: if actionFlags & 2, the condition above ensures entry? Actually from decompiled:
    // The condition for entering the block is:
    // (!allowForce && canExecute) &&
    // ( (hasLineOfSight()==0 && (isTargetValid()==0 || (actionFlags & 2))) ) &&
    // ( (isForceAction != 0) || (canEntityBeTargeted(...)!=0) || (actionFlags & 2) )
    // This is confusing; re-interpreting the decompiled control flow:
    // It says: if ((!allowForce) && (canExecute) && (hasLineOfSight()==0) && (isTargetValid()==0 || (actionFlags & 2)))
    // and then if (isForceAction !=0 || (canEntityBeTargeted(...) !=0 || (actionFlags & 2)))
    // actually the decompiled code has:
    // if ((((!bVar10) && (bVar3)) &&
    //     ((cVar4 = FUN_006f0940(), cVar4 == '\\0' &&
    //      ((cVar4 = FUN_006f3c30(), cVar4 == '\\0' || ((param_3 & 2) != 0)))))) &&
    //    ((uVar6 != 0 ||
    //     ((cVar4 = FUN_006f5940(iVar5,iVar1,param_3), cVar4 != '\\0' || ((param_3 & 2) != 0)))))) {
    // So it's:
    // if ( (!allowForce && canExecute) &&
    //      ( hasLineOfSight() == 0 && (isTargetValid() == 0 || (actionFlags & 2)) ) &&
    //      ( isForceAction || (canEntityBeTargeted(target, this, actionFlags) != 0 || (actionFlags & 2)) ) )
    // Then execute.
    // This is a permission check: a non-force action requires either a valid target or the "ignore" flag (&2).

    if ((!allowForce) && (canExecute)) {
        if (hasLineOfSight() == '\0') {
            if (isTargetValid() == '\0' || (actionFlags & 2) == 0) {
                // Cannot execute because no line of sight and target not valid / no force ignore
                return result;
            }
        }
        // If have line of sight, continue to second condition
        if (!(isForceAction != 0 || (canEntityBeTargeted(target, this, actionFlags) != 0 || (actionFlags & 2) != 0))) {
            return result;
        }
    }

    // All checks passed, now attempt to execute the action
    if ((param_3 & 1) != 0) {
        // Call a vtable function at offset 0x1c (maybe callback for action start)
        (*(void (**)(void))(*this + 0x1c))();
    }

    if (isForceAction == 0) {
        updateActionCooldown(target);
    }

    if (entityId != 0) {
        uint32_t newFlags = 0x80000;
        int32_t duration = 600;

        if ((isForceAction == 0) && ((target->flags & 1) != 0)) {
            newFlags = 0x400000;
            duration = 0x578; // 1400
        }

        uint32_t targetFlags = target->flags;
        if ((targetFlags & 0x10) != 0) {
            newFlags |= 0x10;
        }
        if ((targetFlags & 0x200) != 0) {
            newFlags |= 0x100;
        }

        if ((actionFlags & 2) != 0) {
            newFlags = 0x4000c;
            duration = 0x960; // 2400
        }

        if ((actionFlags & 4) != 0) {
            newFlags = (newFlags & 0xfff7ffff) | 0x40000;
            duration = 0x898; // 2200
        }

        if ((actionFlags & 0x40) != 0) {
            newFlags |= 0x20;
        }

        if ((actionFlags & 0x400) == 0) {
            newFlags |= 8;
        }

        bool noForceFlag = (targetFlags & 0x400) != 0;
        if (noForceFlag) {
            newFlags &= ~8;
        }

        result = executeAction(entityId, duration, !noForceFlag, param4, newFlags, actionFlags & 0xffffff01, 
                                (actionFlags >> 1) & 0xffffff01, param5);
        if ((result != '\0') && (isForceAction == 0)) {
            markActionPerformed(target);
            return result;
        }
    }

    return result;
}