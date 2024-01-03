#include "il2cpp-types.h"

using namespace app;

// unsorted
DO_APP_FUNC(0x0617E860, 0x06155180, void, MoleMole_LCSelectPickup_AddInteeBtnByID, (void* __this, app::BaseEntity* entity, app::MethodInfo* method));
DO_APP_FUNC(0x0617D170, 0x06153AE0, bool, MoleMole_LCSelectPickup_IsInPosition, (void* __this, app::BaseEntity* entity, app::MethodInfo* method));
DO_APP_FUNC(0x0617D420, 0x06153D90, bool, MoleMole_LCSelectPickup_IsOutPosition, (void* __this, app::BaseEntity* entity, app::MethodInfo* method));
DO_APP_FUNC(0x0611B100, 0x060F1E70, void, MoleMole_ItemModule_PickItem, (void* __this, uint32_t entityID, app::MethodInfo* method));

DO_APP_FUNC(0x088C46D0, 0x08879AF0, void, MoleMole_LCAbilityElement_ReduceModifierDurability, (app::LCAbilityElement* __this, int32_t modifierDurabilityIndex, float reduceDurability, app::Nullable_1_Single_ deltaTime, app::MethodInfo* method));
DO_APP_FUNC(0x042B9550, 0x042FEEF0, app::List_1_MoleMole_BaseEntity_*, MoleMole_EntityManager_GetEntities, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x0507AA60, 0x0505F580, app::String*, MoleMole_BaseEntity_ToStringRelease, (app::BaseEntity* __this));
DO_APP_FUNC(0x05680A80, 0x05660730, app::Vector2, Miscs_GenLevelPos_1, (app::Vector3 worldPos));
DO_APP_FUNC(0x0B816730, 0x0B7B9F70, app::Vector3, MoleMole_BaseEntity_GetAbsolutePosition, (app::BaseEntity* __this));
//DO_APP_FUNC(0x007BF620, 0x0, LCBaseCombat*, MoleMole_BaseEntity_GetLogicCombatComponent_1, (app::BaseEntity* __this, app::MethodInfo* method)); // 4.2
//DO_APP_FUNC_METHODINFO(0x931C7A8, MoleMole_BaseEntity_GetLogicCombatComponent_1__MethodInfo); // 4.2
DO_APP_FUNC(0x0CF56FD0, 0x0CEF2FC0, float, Vector2_Distance, (app::Vector2 pos1, app::Vector2 pos2));

// Cooldown cheats
DO_APP_FUNC(0x03FFC5A0, 0x03FF2C40, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x05A06440, 0x059E2A50, bool, MoleMole_LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x05A03280, 0x059DF920, bool, MoleMole_LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float multipler));
DO_APP_FUNC(0x04BFF7C0, 0x04BE9300, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));

// Visuals
DO_APP_FUNC(0x07EDE180, 0x07E99350, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x05519DB0, 0x054FB110, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (app::MoleMole_VCBaseSetDitherValue* __this, float value));

// God mode
DO_APP_FUNC(0x05394400, 0x053769C0, void, VCHumanoidMove_NotifyLandVelocity, (app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x05652AC0, 0x05632B70, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attacker, app::BaseEntity* target, bool checkBackstage));
DO_APP_FUNC(0x081FEFA0, 0x081B8670, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x04ADE790, 0x04AC9870, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (app::ActorAbilityPlugin* __this, float delay, app::Object* arg));

// Utility
DO_APP_FUNC(0x079CDCE0, 0x0798D8E0, app::Vector3, ActorUtils_GetAvatarPos, ());
DO_APP_FUNC(0x079D21C0, 0x07991CD0, void, ActorUtils_SetAvatarPos, (app::Vector3 pos));

DO_APP_FUNC(0x0D0C4C00, 0x0D0607A0, void, Text_set_text, (app::Text* __this, app::String* value));
DO_APP_FUNC(0x0D0C52F0, 0x0D060E90, void, Text_set_alignment, (app::Text* __this, app::TextAnchor__Enum value));
DO_APP_FUNC(0x0D0C5440, 0x0D060FE0, void, Text_set_horizontalOverflow, (app::Text* __this, app::HorizontalWrapMode__Enum value));
DO_APP_FUNC(0x0D0C54B0, 0x0D061050, void, Text_set_verticalOverflow, (app::Text* __this, app::VerticalWrapMode__Enum value));
DO_APP_FUNC(0x0D0C51A0, 0x0D060D40, void, Text_set_resizeTextForBestFit, (app::Text* __this, bool value));
DO_APP_FUNC(0x0D0C53D0, 0x0D060F70, void, Text_set_fontSize, (app::Text* __this, int32_t value));

DO_APP_FUNC(0x0CFDFC30, 0x0CF7B960, void, Slider_1_set_minValue, (app::Slider_1* __this, float value));
DO_APP_FUNC(0x0CFDFCB0, 0x0CF7B9E0, void, Slider_1_set_maxValue, (app::Slider_1* __this, float value));
DO_APP_FUNC(0x0CFDFE20, 0x0CF7BB50, void, Slider_1_set_value, (app::Slider_1* __this, float value));

// should be 'op_Implicit' not 'get_value'
DO_APP_FUNC(0x07E0AC70, 0x07DC6820, float, MoleMole_SafeFloat_get_Value, (app::SafeFloat safeFloat));
// should be 'op_Implicit' not 'set_value'
DO_APP_FUNC(0x07E0AC50, 0x07DC6800, app::SafeFloat, MoleMole_SafeFloat_set_Value, (float value));

DO_APP_FUNC(0x0C771F70, 0x0C711660, app::String*, Marshal_PtrToStringAnsi, (void* ptr));

// Game Object, Transform, Object, Component Utility
DO_APP_FUNC(0x0D0A8100, 0x0D043CF0, app::GameObject*, GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x0D0A84A0, 0x0D044090, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x0D0A84C0, 0x0D0440B0, void, GameObject_SetActive, (app::GameObject* __this, bool value));
DO_APP_FUNC(0x0D0A8730, 0x0D044320, app::GameObject*, GameObject_Find, (app::String* name));
DO_APP_FUNC(0x0D0A8170, 0x0D043D60, app::Component_1*, GameObject_GetComponentByName, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x0D0A8440, 0x0D044030, app::Component_1*, GameObject_AddComponentInternal, (app::GameObject* __this, app::String* className));
DO_APP_FUNC(0x0D0A8470, 0x0D044060, app::Transform*, GameObject_get_transform, (app::GameObject* __this));

DO_APP_FUNC(0x0CF679C0, 0x0CF03960, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x0CF679D0, 0x0CF03970, int32_t, Transform_GetChildCount, (app::Transform* __this));
DO_APP_FUNC(0x0CF622E0, 0x0CEFE270, void, Transform_set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x0CF653F0, 0x0CF01390, void, Transform_set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x0CF65B30, 0x0CF01AD0, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x0CF65B90, 0x0CF01B30, void, Transform_set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x0CF65400, 0x0CF013A0, app::Vector3, Transform_get_right, (app::Transform* __this));
DO_APP_FUNC(0x0CF65650, 0x0CF015F0, app::Vector3, Transform_get_up, (app::Transform* __this));
DO_APP_FUNC(0x0CF658A0, 0x0CF01840, app::Vector3, Transform_get_forward, (app::Transform* __this));
DO_APP_FUNC(0x0CF64F60, 0x0CF00F00, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x0CF64FC0, 0x0CF00F60, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x0CF65180, 0x0CF01120, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x0CF65230, 0x0CF011D0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x0CF63630, 0x0CEFF5C0, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x0CF65C30, 0x0CF01BD0, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x0CF65D90, 0x0CF01D30, void, Transform_Translate, (app::Transform* __this, app::Vector3 translation));

DO_APP_FUNC(0x0CF618F0, 0x0CEFD880, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x0CF618B0, 0x0CEFD840, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));

DO_APP_FUNC(0x0CF4F220, 0x0CEEB210, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));

// UnityEngine
DO_APP_FUNC(0x0D056C20, 0x0CFF28D0, void, RenderSettings_set_fog, (bool value));

DO_APP_FUNC(0x0D0AAA80, 0x0D046670, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x0D0AAB60, 0x0D046750, float, Time_get_timeScale, ());
DO_APP_FUNC(0x0D0AAB70, 0x0D046760, void*, Time_set_timeScale, (float time));

DO_APP_FUNC(0x0D08F430, 0x0D02B060, bool*, Application_get_isFocused, ());
DO_APP_FUNC(0x0D08F590, 0x0D02B1C0, void*, Application_set_targetFrameRate, (int32_t value));

DO_APP_FUNC(0x0D0EED10, 0x0D08A870, void*, QualitySettings_set_vSyncCount, (int32_t value));

DO_APP_FUNC(0x0D0BC3D0, 0x0D057FA0, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));
DO_APP_FUNC(0x0D0BB080, 0x0D056C50, app::Vector3, Vector3_Lerp, (app::Vector3 start, app::Vector3 end, float time));

DO_APP_FUNC(0x0CF73F30, 0x0CF0FE70, bool, Cursor_get_visible, (app::MethodInfo* method));
DO_APP_FUNC(0x0CF73F40, 0x0CF0FE80, void, Cursor_set_visible, (bool value));
DO_APP_FUNC(0x0CF73F60, 0x0CF0FEA0, void, Cursor_set_lockState, (app::CursorLockMode__Enum value));

DO_APP_FUNC(0x0CF54E10, 0x0CEF0E00, int32_t, Screen_get_width, (app::MethodInfo* method));
DO_APP_FUNC(0x0CF54E20, 0x0CEF0E10, int32_t, Screen_get_height, (app::MethodInfo* method));

DO_APP_FUNC(0x0CEC02A0, 0x0CE5C3C0, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x0CEC0430, 0x0CE5C550, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x0CEC0550, 0x0CE5C670, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x0CEC0560, 0x0CE5C680, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x0CEC05C0, 0x0CE5C6E0, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x0CEC0670, 0x0CE5C790, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 position));

DO_APP_FUNC(0x0C7AE520, 0x0C74DAD0, void, Action_Invoke, (/*Action*/ void* __this));

// Lua functions
DO_APP_FUNC(0x03FA0B10, 0x03F974E0, void, MoleMole_LuaShellManager_ReportLuaShellResult, (void* __this, app::String* type, app::String* value));

// World cheats
DO_APP_FUNC(0x04A78BA0, 0x04A64740, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x04E572D0, 0x04E3E440, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));
DO_APP_FUNC(0x04E594D0, 0x04E405F0, void, MoleMole_LevelSceneElementViewPlugin_TriggerElementView, (app::LevelSceneElementViewPlugin* __this, bool trigger));

// Dialog skipping
DO_APP_FUNC(0x070C52F0, 0x0708CE20, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
DO_APP_FUNC(0x05D141D0, 0x05CEDBF0, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x05D13D40, 0x05CED760, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x05D154D0, 0x05CEEED0, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));

// Skip Cutscene
DO_APP_FUNC(0x05CFF000, 0x05CD8B70, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this, app::MethodInfo* method));
DO_APP_FUNC(0x05CFF820, 0x05CD9390, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this, app::MethodInfo* method));

// Chest Indicator
DO_APP_FUNC(0x0766FA30, 0x076321C0, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x0766F480, 0x07631C10, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x0766EF60, 0x076316F0, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));

// Profile Changer
DO_APP_FUNC(0x05249BC0, 0x0522D310, app::Button_1*, ProfilePage, (app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method));

// Visuals
DO_APP_FUNC(0x0831D420, 0x082D5E60, void, MonoParticleDamageTextContainer_ShowDamageText, (void* __this, void* attackResult, void* attackee));
DO_APP_FUNC(0x0831EA80, 0x082D74B0, void, MonoParticleDamageTextContainer_ShowReactionText, (void* __this, void* reaction, void* elemType1, void* elemType2, void* attackee, int hitIndex));

// Modify
DO_APP_FUNC(0x03FF0750, 0x03FE6D90, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));

// Entities
DO_APP_FUNC(0x03E2D5B0, 0x03E254D0, app::MoleMole_EntityManager*, MoleMole_InLevelDrumPageContext_get_ENTITY, (app::MethodInfo* method));

DO_APP_FUNC(0x042B6770, 0x042FC180, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x042B9080, 0x042FEA20, app::CameraEntity*, MoleMole_EntityManager_GetMainCameraEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x042B9710, 0x042FF0B0, app::BaseEntity*, MoleMole_EntityManager_GetValidEntity, (app::MoleMole_EntityManager* __this, uint32_t runtimeID));

DO_APP_FUNC(0x0506F080, 0x05053C40, uint32_t, MoleMole_BaseEntity_get_runtimeID, (app::BaseEntity* __this));
DO_APP_FUNC(0x0506F0C0, 0x05053C80, uint32_t, MoleMole_BaseEntity_get_configID, (app::BaseEntity* __this));
DO_APP_FUNC(0x0505A7E0, 0x0503F4E0, bool, MoleMole_BaseEntity_IsActive, (app::BaseEntity* __this));
DO_APP_FUNC(0x07631D50, 0x075F4810, app::Animator*, MoleMole_BaseEntity_get_animator, (app::BaseEntity* __this));
DO_APP_FUNC(0x07631AB0, 0x075F4570, app::GameObject*, MoleMole_BaseEntity_get_rootGameObject, (app::BaseEntity* __this));
DO_APP_FUNC(0x076359C0, 0x075F8490, app::Rigidbody*, MoleMole_BaseEntity_GetRigidbody, (app::BaseEntity* __this));
DO_APP_FUNC(0x05079BC0, 0x0505E6E0, app::EntityType__Enum_1, MoleMole_BaseEntity_get_entityType, (app::BaseEntity* __this));
DO_APP_FUNC(0x07635B60, 0x075F8630, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
DO_APP_FUNC(0x07636940, 0x075F93E0, void, MoleMole_BaseEntity_SetRelativePosition, (app::BaseEntity* __this, app::Vector3 position, bool forceSyncToRigidbody));
DO_APP_FUNC(0x076371D0, 0x075F9C80, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x07637630, 0x075FA0E0, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x076379D0, 0x075FA480, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));

DO_APP_FUNC(0x04713420, 0x04702DE0, app::BaseEntity*, MoleMole_GadgetEntity_GetOwnerEntity, (app::GadgetEntity* __this));

// Protection bypass
DO_APP_FUNC(0x0529E520, 0x052818B0, app::Byte__Array*, MoleMole_SecurityModule_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Teleport hooks
DO_APP_FUNC(0x0738F470, 0x07354B20, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));

// Open team immediately 4.2
DO_APP_FUNC(0x04475550, 0x0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x00D82A70, 0x0, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (void* __this));
DO_APP_FUNC(0x00D7EFF0, 0x0, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (void* __this));
DO_APP_FUNC(0x013E7B30, 0x0, void, MoleMole_InLevelMainPageContext_EndCountDown, (app::InLevelMainPageContext* __this));

// Unlimited stamina
DO_APP_FUNC(0x03A70CE0, 0x03A6CCA0, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq));
DO_APP_FUNC(0x07431BC0, 0x073F6850, app::MotionState__Enum, MotionInfo_get_State, (app::MotionInfo* __this));
DO_APP_FUNC(0x07431BD0, 0x073F6860, app::MotionState__Enum, MotionInfo_set_State, (app::MotionInfo* __this, app::MotionState__Enum value));
//DO_APP_FUNC(0x03AFF770, 0x03AFAED0, void, MoleMole_DataItem_HandleNormalProp, (app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state));
// Wanderer E Stamina
DO_APP_FUNC(0x0539BA80, 0x0537E040, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));

DO_APP_FUNC(0x0, 0x0, void, QualitySettings_set_shadows, (app::ShadowQuality value));
