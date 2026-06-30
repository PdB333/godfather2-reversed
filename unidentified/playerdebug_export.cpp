// Player debug export reconstructed from xbox_debug symbols and the PC reverse
// engineering work already present in auto-re-agent.
//
// This is a feature-level export, not a byte-accurate decompilation.
// The goal is to preserve the menu surface, option names, and integration
// points so the PC build can be extended from the Xbox alpha debug subsystem.

#include <cstdint>

namespace Modules
{
namespace EARS
{

static void EmitDebugLine(const char* channel, const char* text)
{
    (void)channel;
    (void)text;
}

struct AttackCastDispData
{
    float startX;
    float startY;
    float startZ;
    float endX;
    float endY;
    float endZ;
    bool active;

    AttackCastDispData()
        : startX(0.0f)
        , startY(0.0f)
        , startZ(0.0f)
        , endX(0.0f)
        , endY(0.0f)
        , endZ(0.0f)
        , active(false)
    {
    }
};

class PlayerDebugOptions
{
public:
    enum FlagBits1 : std::uint32_t
    {
        kFlagGodMode                        = 1u << 0,
        kFlagUnlimitedAmmo                  = 1u << 1,
        kFlagDebugFly                       = 1u << 2,
        kFlagFastRegen                      = 1u << 3,
        kFlagDisplayF2FDebugInfo            = 1u << 4,
        kFlagShowWeaponBinding              = 1u << 5,
        kFlagShowActiveGunSpread            = 1u << 6,
        kFlagNeckSnapForce                  = 1u << 7,
        kFlagH2HPushback                    = 1u << 8,
        kFlagH2HAlternateFinisher           = 1u << 9,
        kFlagH2HVacuumDisabled              = 1u << 10,
        kFlagDisplayEnvCollisionTests       = 1u << 11,
        kFlagDisplaySprintFatigueDebug      = 1u << 12,
        kFlagCrewCommandsEnabled            = 1u << 13,
        kFlagIdleTurnSupport                = 1u << 14,
        kFlagDisableBanking                 = 1u << 15,
        kFlagGhostInterpretControlsDisabled = 1u << 16,
        kFlagGhostDesiredYawDisabled        = 1u << 17,
        kFlagMovingGhostDesiredYawDisabled  = 1u << 18,
        kFlagAimAssistance                  = 1u << 19
    };

    enum FlagBits2 : std::uint32_t
    {
        kFlagAudioOcclusion = 1u << 0,
        kFlagWrinkleShader   = 1u << 1,
        kFlagDisplayAxes     = 1u << 2,
        kFlagDisplayGraph    = 1u << 3,
        kFlagDisplayNearestNode = 1u << 4,
        kFlagDisplayInfo     = 1u << 5,
        kFlagDrawAttackCasts = 1u << 6
    };

    PlayerDebugOptions()
        : m_flags1(0)
        , m_flags2(0)
        , m_dirty(false)
        , m_requestResetHealth(false)
        , m_requestFillAmmo(false)
        , m_requestAddMoney(false)
        , m_requestAddLotsOfMoney(false)
        , m_requestAllItems(false)
        , m_requestForceKill(false)
        , m_requestUpdateChaseCamera(false)
        , m_ghostStickMagOverride(0.0f)
        , m_movingGhostStickMagOverride(0.0f)
        , m_attackCastCount(0)
        , m_locomotionTurnAngle(0.0f)
    {
    }

    ~PlayerDebugOptions()
    {
    }

    static PlayerDebugOptions& GetSingleton()
    {
        static PlayerDebugOptions s_instance;
        return s_instance;
    }

    void HandleEvents(void* msg)
    {
        (void)msg;
        UpdateDebugChaseCamera();
        UpdateFlagChanges();
    }

    void UpdateDebugChaseCamera()
    {
        if (!m_requestUpdateChaseCamera)
        {
            return;
        }

        // PC integration point:
        // this is where the debug chase camera should sync against the existing
        // camera / overlay path already exposed by setDebugOverlayState.
        m_requestUpdateChaseCamera = false;
        EmitDebugLine("PlayerDebug", "UpdateDebugChaseCamera");
    }

    void UpdateEnvCollisionCacheDebugOption()
    {
        EmitDebugLine("PlayerDebug", "UpdateEnvCollisionCacheDebugOption");
    }

    void DisplayNearestNode()
    {
        m_flags2 |= kFlagDisplayNearestNode;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "DisplayNearestNode");
    }

    void DisplayAxis()
    {
        m_flags2 |= kFlagDisplayAxes;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "DisplayAxis");
    }

    void DrawAxisGraph()
    {
        m_flags2 |= kFlagDisplayGraph;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "DrawAxisGraph");
    }

    void DisplayGrabBoneAndLocators()
    {
        EmitDebugLine("PlayerDebug", "DisplayGrabBoneAndLocators");
    }

    void DrawGrabBoneAndLocators(void* sentient, float x, float y, float z, float w, float h)
    {
        (void)sentient;
        (void)x;
        (void)y;
        (void)z;
        (void)w;
        (void)h;
        EmitDebugLine("PlayerDebug", "DrawGrabBoneAndLocators");
    }

    void DisplayInfo()
    {
        m_flags2 |= kFlagDisplayInfo;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "DisplayInfo");
    }

    void PrintPlayer(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayer");
    }

    void PrintPlayerAnims(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerAnims");
    }

    void PrintPlayerCCTVars(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerCCTVars");
    }

    void PrintPlayerCCTAimVars(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerCCTAimVars");
    }

    void PrintPlayerAnimFrameInfo(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerAnimFrameInfo");
    }

    void PrintPlayerHealth(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerHealth");
    }

    void PrintPlayerLocation(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintPlayerLocation");
    }

    void PrintGameMovement(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintGameMovement");
    }

    void PrintSupportCastInfo(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintSupportCastInfo");
    }

    void PrintCrouchDebugging(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintCrouchDebugging");
    }

    void PrintCurrentTarget(char* outText, std::uint32_t outSize, void* player)
    {
        (void)outText;
        (void)outSize;
        (void)player;
        EmitDebugLine("PlayerDebug", "PrintCurrentTarget");
    }

    void DisplayProxyInfo(void* player)
    {
        (void)player;
        EmitDebugLine("PlayerDebug", "DisplayProxyInfo");
    }

    void DisplayBlockingInfo(void* player)
    {
        (void)player;
        EmitDebugLine("PlayerDebug", "DisplayBlockingInfo");
    }

    void DisplayAttackerInfo(void* player)
    {
        (void)player;
        EmitDebugLine("PlayerDebug", "DisplayAttackerInfo");
    }

    void DisplayLocomotionDebug()
    {
        EmitDebugLine("PlayerDebug", "DisplayLocomotionDebug");
    }

    void UpdateControllerRumbleTest()
    {
        EmitDebugLine("PlayerDebug", "UpdateControllerRumbleTest");
    }

    void SetLocomotionTurnAngle(float angle)
    {
        m_locomotionTurnAngle = angle;
        m_dirty = true;
    }

    static void SetAudioOcclusionCallBackFn(bool enabled)
    {
        PlayerDebugOptions& options = GetSingleton();
        if (enabled)
        {
            options.m_flags2 |= kFlagAudioOcclusion;
        }
        else
        {
            options.m_flags2 &= ~kFlagAudioOcclusion;
        }
        options.m_dirty = true;
    }

    static void SetWrinkleShaderOnOffCallBackFn(bool enabled)
    {
        PlayerDebugOptions& options = GetSingleton();
        if (enabled)
        {
            options.m_flags2 |= kFlagWrinkleShader;
        }
        else
        {
            options.m_flags2 &= ~kFlagWrinkleShader;
        }
        options.m_dirty = true;
    }

    static void SetGodModeCallBackFn(bool enabled)
    {
        GetSingleton().SetInGodMode(enabled);
    }

    void SetInGodMode(bool enabled)
    {
        if (enabled)
        {
            m_flags1 |= kFlagGodMode;
        }
        else
        {
            m_flags1 &= ~kFlagGodMode;
        }
        m_dirty = true;
    }

    bool IsInGodMode() const
    {
        return (m_flags1 & kFlagGodMode) != 0;
    }

    void SetInDebugFly(bool enabled)
    {
        if (enabled)
        {
            m_flags1 |= kFlagDebugFly;
        }
        else
        {
            m_flags1 &= ~kFlagDebugFly;
        }
        m_requestUpdateChaseCamera = enabled;
        m_dirty = true;
    }

    bool IsInDebugFly() const
    {
        return (m_flags1 & kFlagDebugFly) != 0;
    }

    void SetUnlimitedAmmo(bool enabled)
    {
        if (enabled)
        {
            m_flags1 |= kFlagUnlimitedAmmo;
        }
        else
        {
            m_flags1 &= ~kFlagUnlimitedAmmo;
        }
        m_dirty = true;
    }

    bool IsInUnlimitedAmmo() const
    {
        return (m_flags1 & kFlagUnlimitedAmmo) != 0;
    }

    bool DidPlayerSwitchControllerConfigs() const
    {
        return false;
    }

    bool IsInFastRegenMode() const
    {
        return (m_flags1 & kFlagFastRegen) != 0;
    }

    bool ShouldDisplayF2FDebugInfo() const
    {
        return (m_flags1 & kFlagDisplayF2FDebugInfo) != 0;
    }

    bool IsShowingWeaponBinding() const
    {
        return (m_flags1 & kFlagShowWeaponBinding) != 0;
    }

    bool FallIfUnsupported() const
    {
        return true;
    }

    bool ShouldShowActiveGunSpread() const
    {
        return (m_flags1 & kFlagShowActiveGunSpread) != 0;
    }

    bool IsNeckSnapForceEnabled() const
    {
        return (m_flags1 & kFlagNeckSnapForce) != 0;
    }

    bool IsH2HPushbackEnabled() const
    {
        return (m_flags1 & kFlagH2HPushback) != 0;
    }

    bool IsH2HAlternateFinisherEnabled() const
    {
        return (m_flags1 & kFlagH2HAlternateFinisher) != 0;
    }

    bool IsH2HVacuumDisabled() const
    {
        return (m_flags1 & kFlagH2HVacuumDisabled) != 0;
    }

    bool ShouldDisplayEnvCollisionTests() const
    {
        return (m_flags1 & kFlagDisplayEnvCollisionTests) != 0;
    }

    bool ShouldDisplaySprintFatigueDebug() const
    {
        return (m_flags1 & kFlagDisplaySprintFatigueDebug) != 0;
    }

    bool AreCrewCommandsEnabled() const
    {
        return (m_flags1 & kFlagCrewCommandsEnabled) != 0;
    }

    bool ShouldRunIdleTurnSupportCode() const
    {
        return (m_flags1 & kFlagIdleTurnSupport) != 0;
    }

    bool ShouldDisableBanking() const
    {
        return (m_flags1 & kFlagDisableBanking) != 0;
    }

    bool IsGhostInterpretControlsDisabled() const
    {
        return (m_flags1 & kFlagGhostInterpretControlsDisabled) != 0;
    }

    float GetGhostStickMagOverride() const
    {
        return m_ghostStickMagOverride;
    }

    float GetMovingGhostStickMagOverride() const
    {
        return m_movingGhostStickMagOverride;
    }

    bool ShouldDisableGhostDesiredYaw() const
    {
        return (m_flags1 & kFlagGhostDesiredYawDisabled) != 0;
    }

    bool ShouldDisableMovingGhostDesiredYaw() const
    {
        return (m_flags1 & kFlagMovingGhostDesiredYawDisabled) != 0;
    }

    bool DebugAimAssistance() const
    {
        return (m_flags1 & kFlagAimAssistance) != 0;
    }

    void ResetPlayerHealth()
    {
        m_requestResetHealth = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "ResetPlayerHealth");
    }

    void FillPlayerAmmo()
    {
        m_requestFillAmmo = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "FillPlayerAmmo");
    }

    void AddSomeMoney()
    {
        m_requestAddMoney = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "AddSomeMoney");
    }

    void AddLotsOfMoney()
    {
        m_requestAddLotsOfMoney = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "AddLotsOfMoney");
    }

    void AllItems()
    {
        m_requestAllItems = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "AllItems");
    }

    void ForceKillPlayer()
    {
        m_requestForceKill = true;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "ForceKillPlayer");
    }

    void AddAttackCastToDraw(const float start[3], const float end[3], bool enabled)
    {
        if (m_attackCastCount >= 16)
        {
            return;
        }

        AttackCastDispData& slot = m_attackCasts[m_attackCastCount++];
        slot.startX = start[0];
        slot.startY = start[1];
        slot.startZ = start[2];
        slot.endX = end[0];
        slot.endY = end[1];
        slot.endZ = end[2];
        slot.active = enabled;
        m_flags2 |= kFlagDrawAttackCasts;
        m_dirty = true;
    }

    void ClearAttackCasts()
    {
        m_attackCastCount = 0;
        m_flags2 &= ~kFlagDrawAttackCasts;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "ClearAttackCasts");
    }

    void DrawAttackCasts()
    {
        m_flags2 |= kFlagDrawAttackCasts;
        m_dirty = true;
        EmitDebugLine("PlayerDebug", "DrawAttackCasts");
    }

    void UpdateFlagChanges()
    {
        if (!m_dirty)
        {
            return;
        }

        // PC integration point:
        // this is where the option bits should be forwarded to the existing
        // player systems already present in the PC rebuild:
        // - Player::setPlayerFlag / setPlayerConditionFlags
        // - Player::enableAimAssist
        // - the debug overlay / debug console hooks
        // - player cheat / inventory helpers
        //
        // We keep the export logic here so the feature matrix is preserved even
        // if the exact per-build addresses differ.

        if (m_requestResetHealth)
        {
            EmitDebugLine("PlayerDebug", "Apply ResetPlayerHealth");
            m_requestResetHealth = false;
        }
        if (m_requestFillAmmo)
        {
            EmitDebugLine("PlayerDebug", "Apply FillPlayerAmmo");
            m_requestFillAmmo = false;
        }
        if (m_requestAddMoney)
        {
            EmitDebugLine("PlayerDebug", "Apply AddSomeMoney");
            m_requestAddMoney = false;
        }
        if (m_requestAddLotsOfMoney)
        {
            EmitDebugLine("PlayerDebug", "Apply AddLotsOfMoney");
            m_requestAddLotsOfMoney = false;
        }
        if (m_requestAllItems)
        {
            EmitDebugLine("PlayerDebug", "Apply AllItems");
            m_requestAllItems = false;
        }
        if (m_requestForceKill)
        {
            EmitDebugLine("PlayerDebug", "Apply ForceKillPlayer");
            m_requestForceKill = false;
        }

        m_dirty = false;
    }

    std::uint32_t GetFlags1() const
    {
        return m_flags1;
    }

    std::uint32_t GetFlags2() const
    {
        return m_flags2;
    }

    void SetFlags(std::uint32_t flags1, std::uint32_t flags2)
    {
        m_flags1 = flags1;
        m_flags2 = flags2;
        m_dirty = true;
    }

    bool IsDirty() const
    {
        return m_dirty;
    }

    void ClearDirty()
    {
        m_dirty = false;
    }

private:
    std::uint32_t m_flags1;
    std::uint32_t m_flags2;
    bool m_dirty;

    bool m_requestResetHealth;
    bool m_requestFillAmmo;
    bool m_requestAddMoney;
    bool m_requestAddLotsOfMoney;
    bool m_requestAllItems;
    bool m_requestForceKill;
    bool m_requestUpdateChaseCamera;

    float m_ghostStickMagOverride;
    float m_movingGhostStickMagOverride;
    AttackCastDispData m_attackCasts[16];
    int m_attackCastCount;
    float m_locomotionTurnAngle;
};

class PlayerDebugFlySM
{
public:
    PlayerDebugFlySM(unsigned int stateId, void* params)
        : m_stateId(stateId)
        , m_params(params)
        , m_cameraActive(false)
        , m_grabbee(0)
        , m_vehicle(0)
    {
    }

    ~PlayerDebugFlySM()
    {
    }

    void BuildStateMachine()
    {
        EmitDebugLine("PlayerDebugFlySM", "BuildStateMachine");
    }

    bool HandleStateMessage(unsigned int stateId, unsigned int messageId, unsigned int arg1, unsigned int arg2, const void* data)
    {
        (void)stateId;
        (void)messageId;
        (void)arg1;
        (void)arg2;
        (void)data;
        return true;
    }

    bool CheckTransition(unsigned int stateId, unsigned int messageId, unsigned int arg1, const void* transitionData)
    {
        (void)stateId;
        (void)messageId;
        (void)arg1;
        (void)transitionData;
        return true;
    }

    void ProcessMovement(float deltaSeconds)
    {
        (void)deltaSeconds;
        EmitDebugLine("PlayerDebugFlySM", "ProcessMovement");
    }

    void CreateCamera()
    {
        m_cameraActive = true;
        EmitDebugLine("PlayerDebugFlySM", "CreateCamera");
    }

    void DestroyCamera()
    {
        m_cameraActive = false;
        EmitDebugLine("PlayerDebugFlySM", "DestroyCamera");
    }

    void SetGrabbee(void* sentient)
    {
        m_grabbee = sentient;
    }

    void DropVehicle()
    {
        m_vehicle = 0;
        EmitDebugLine("PlayerDebugFlySM", "DropVehicle");
    }

    const char* GetTransIDString(unsigned int id) const
    {
        switch (id)
        {
        case 0: return "Idle";
        case 1: return "CreateCamera";
        case 2: return "DestroyCamera";
        case 3: return "Grabbee";
        case 4: return "DropVehicle";
        default: return "Unknown";
        }
    }

private:
    unsigned int m_stateId;
    void* m_params;
    bool m_cameraActive;
    void* m_grabbee;
    void* m_vehicle;
};

class PlayerDebugMenu
{
public:
    struct MenuEntry
    {
        const char* label;
        void (PlayerDebugMenu::*action)();
    };

    static const char* MENU_TITLE;

    PlayerDebugMenu()
        : m_options(&PlayerDebugOptions::GetSingleton())
        , m_itemCount(0)
    {
        Build();
    }

    ~PlayerDebugMenu()
    {
    }

    void BindOptions(PlayerDebugOptions* options)
    {
        m_options = options;
        Build();
    }

    const MenuEntry* Items() const
    {
        return m_items;
    }

    int ItemCount() const
    {
        return m_itemCount;
    }

    void ForceKillPlayer()
    {
        if (m_options != 0)
        {
            m_options->ForceKillPlayer();
        }
    }

private:
    void Build()
    {
        m_itemCount = 0;
        Add("Reset Health", &PlayerDebugMenu::OnResetHealth);
        Add("Fill Ammo", &PlayerDebugMenu::OnFillAmmo);
        Add("Add Some Money", &PlayerDebugMenu::OnAddSomeMoney);
        Add("Add Lots Of Money", &PlayerDebugMenu::OnAddLotsOfMoney);
        Add("All Items", &PlayerDebugMenu::OnAllItems);
        Add("God Mode", &PlayerDebugMenu::OnToggleGodMode);
        Add("Unlimited Ammo", &PlayerDebugMenu::OnToggleUnlimitedAmmo);
        Add("Debug Fly", &PlayerDebugMenu::OnToggleDebugFly);
        Add("Audio Occlusion", &PlayerDebugMenu::OnToggleAudioOcclusion);
        Add("Wrinkle Shader", &PlayerDebugMenu::OnToggleWrinkleShader);
        Add("Kill Player", &PlayerDebugMenu::OnForceKillPlayer);
        Add("Draw Attack Casts", &PlayerDebugMenu::OnDrawAttackCasts);
        Add("Clear Attack Casts", &PlayerDebugMenu::OnClearAttackCasts);
        Add("Nearest Node", &PlayerDebugMenu::OnDisplayNearestNode);
        Add("Axis", &PlayerDebugMenu::OnDisplayAxis);
        Add("Axis Graph", &PlayerDebugMenu::OnDrawAxisGraph);
        Add("Grab Bones", &PlayerDebugMenu::OnDisplayGrabBones);
        Add("Player Info", &PlayerDebugMenu::OnDisplayInfo);
        Add("Player Health Log", &PlayerDebugMenu::OnPrintPlayerHealth);
        Add("Player Location Log", &PlayerDebugMenu::OnPrintPlayerLocation);
        Add("Game Movement Log", &PlayerDebugMenu::OnPrintGameMovement);
        Add("Target Log", &PlayerDebugMenu::OnPrintCurrentTarget);
    }

    void Add(const char* label, void (PlayerDebugMenu::*action)())
    {
        if (m_itemCount >= kMaxItems)
        {
            return;
        }

        m_items[m_itemCount].label = label;
        m_items[m_itemCount].action = action;
        ++m_itemCount;
    }

    void Run(void (PlayerDebugOptions::*action)())
    {
        if (m_options != 0)
        {
            (m_options->*action)();
        }
    }

    void OnResetHealth() { Run(&PlayerDebugOptions::ResetPlayerHealth); }
    void OnFillAmmo() { Run(&PlayerDebugOptions::FillPlayerAmmo); }
    void OnAddSomeMoney() { Run(&PlayerDebugOptions::AddSomeMoney); }
    void OnAddLotsOfMoney() { Run(&PlayerDebugOptions::AddLotsOfMoney); }
    void OnAllItems() { Run(&PlayerDebugOptions::AllItems); }
    void OnToggleGodMode()
    {
        if (m_options != 0)
        {
            m_options->SetInGodMode(!m_options->IsInGodMode());
        }
    }

    void OnToggleUnlimitedAmmo()
    {
        if (m_options != 0)
        {
            m_options->SetUnlimitedAmmo(!m_options->IsInUnlimitedAmmo());
        }
    }

    void OnToggleDebugFly()
    {
        if (m_options != 0)
        {
            m_options->SetInDebugFly(!m_options->IsInDebugFly());
        }
    }

    void OnToggleAudioOcclusion()
    {
        if (m_options != 0)
        {
            m_options->SetAudioOcclusionCallBackFn((m_options->GetFlags2() & PlayerDebugOptions::kFlagAudioOcclusion) == 0);
        }
    }

    void OnToggleWrinkleShader()
    {
        if (m_options != 0)
        {
            m_options->SetWrinkleShaderOnOffCallBackFn((m_options->GetFlags2() & PlayerDebugOptions::kFlagWrinkleShader) == 0);
        }
    }
    void OnForceKillPlayer() { Run(&PlayerDebugOptions::ForceKillPlayer); }
    void OnDrawAttackCasts() { Run(&PlayerDebugOptions::DrawAttackCasts); }
    void OnClearAttackCasts() { Run(&PlayerDebugOptions::ClearAttackCasts); }
    void OnDisplayNearestNode() { Run(&PlayerDebugOptions::DisplayNearestNode); }
    void OnDisplayAxis() { Run(&PlayerDebugOptions::DisplayAxis); }
    void OnDrawAxisGraph() { Run(&PlayerDebugOptions::DrawAxisGraph); }
    void OnDisplayGrabBones() { Run(&PlayerDebugOptions::DisplayGrabBoneAndLocators); }
    void OnDisplayInfo() { Run(&PlayerDebugOptions::DisplayInfo); }
    void OnPrintPlayerHealth()
    {
        if (m_options != 0)
        {
            m_options->PrintPlayerHealth(0, 0, 0);
        }
    }

    void OnPrintPlayerLocation()
    {
        if (m_options != 0)
        {
            m_options->PrintPlayerLocation(0, 0, 0);
        }
    }

    void OnPrintGameMovement()
    {
        if (m_options != 0)
        {
            m_options->PrintGameMovement(0, 0, 0);
        }
    }

    void OnPrintCurrentTarget()
    {
        if (m_options != 0)
        {
            m_options->PrintCurrentTarget(0, 0, 0);
        }
    }

private:
    static const int kMaxItems = 32;
    PlayerDebugOptions* m_options;
    MenuEntry m_items[kMaxItems];
    int m_itemCount;
};

const char* PlayerDebugMenu::MENU_TITLE = "Player Debug";

class LuaPlayerDebugLibrary
{
public:
    LuaPlayerDebugLibrary()
    {
    }

    ~LuaPlayerDebugLibrary()
    {
    }

    void Open(void* luaState)
    {
        (void)luaState;
    }

    void Close(void* luaState)
    {
        (void)luaState;
    }

    static int DispOn(void* luaState)
    {
        (void)luaState;
        PlayerDebugOptions::GetSingleton().DisplayInfo();
        return 0;
    }

    static int DispOff(void* luaState)
    {
        (void)luaState;
        PlayerDebugOptions::GetSingleton().ClearDirty();
        return 0;
    }

    static int GodMode(void* luaState)
    {
        (void)luaState;
        PlayerDebugOptions::GetSingleton().SetInGodMode(true);
        return 0;
    }

    static int DebugFly(void* luaState)
    {
        (void)luaState;
        PlayerDebugOptions::GetSingleton().SetInDebugFly(true);
        return 0;
    }

    static int Teleport(void* luaState)
    {
        (void)luaState;
        EmitDebugLine("LuaPlayerDebug", "Teleport");
        return 0;
    }
};

} // namespace EARS
} // namespace Modules
