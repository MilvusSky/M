#include "ProfileChanger.h"

namespace cheat {
	static void onUpdate_1(app::GameManager* __this, app::MethodInfo* method);
	app::Button_1* ProfilePage(app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method);

	ProfileChanger::ProfileChanger() : Function() {
		f_Enabled = config::getValue("functions:ProfileChanger", "enabled", false);

		f_EnabledUid = config::getValue("functions:ProfileChanger:UID", "enabled", false);
		f_Uid = config::getValue<std::string>("functions:ProfileChanger:UID", "value", "");
		f_UidSize = config::getValue("functions:ProfileChanger:UID", "size", 14);
		f_UidPosX = config::getValue("functions:ProfileChanger:UID", "posX", static_cast<float>(app::Screen_get_width(nullptr) * 0.96875f));
		f_UidPosY = config::getValue("functions:ProfileChanger:UID", "posY", 0.0f);

		f_EnabledName = config::getValue("functions:ProfileChanger:Name", "enabled", false);
		f_Name = config::getValue<std::string>("functions:ProfileChanger:Name", "value", "");

		f_EnabledLevel = config::getValue("functions:ProfileChanger:Level", "enabled", false);
		f_Level = config::getValue<std::string>("functions:ProfileChanger:Level", "value", "");

		f_EnabledWorldLevel = config::getValue("functions:ProfileChanger:WorldLevel", "enabled", false);
		f_WorldLevel = config::getValue<std::string>("functions:ProfileChanger:WorldLevel", "value", "");

		f_EnabledBirthday = config::getValue("functions:ProfileChanger:Birthday", "enabled", false);
		f_Birthday = config::getValue<std::string>("functions:ProfileChanger:Birthday", "value", "");

		f_EnabledSignature = config::getValue("functions:ProfileChanger:Signature", "enabled", false);
		f_Signature = config::getValue<std::string>("functions:ProfileChanger:Signature", "value", "");

		f_EnabledExp = config::getValue("functions:ProfileChanger:Exp", "enabled", false);
		f_CurrentExp = config::getValue("functions:ProfileChanger:Exp", "current", 1);
		f_MaxExp = config::getValue("functions:ProfileChanger:Exp", "max", 1);

		f_EnabledExpBar = config::getValue("functions:ProfileChanger:ExpBar", "enabled", false);
		f_ExpBar = config::getValue("functions:ProfileChanger:ExpBar", "value", 20.0f);

		f_Hotkey = Hotkey("functions:ProfileChanger");

		HookManager::install(app::GameManager_Update, onUpdate_1);
		HookManager::install(app::ProfilePage, ProfilePage);
	}

	ProfileChanger& ProfileChanger::getInstance() {
		static ProfileChanger instance;
		return instance;
	}

	void ProfileChanger::GUI() {
		ConfigCheckbox(_("PROFILE_CHANGER_TITLE"), f_Enabled, _("PROFILE_CHANGER_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox(_("UID_TITLE"), f_EnabledUid, _("UID_DESCRIPTION"));

			if (f_EnabledUid.getValue()) {
				ConfigInputText(_("UID_VALUE_TITLE"), f_Uid);
				ConfigSliderInt(_("UID_SIZE_TITLE"), f_UidSize, 1, 500, _("UID_SIZE_DESCRIPTION"));
				ConfigSliderFloat(_("UID_POS_X_TITLE"), f_UidPosX, 1.0f, static_cast<float>(app::Screen_get_width(nullptr)), _("UID_POS_X_DESCRIPTION"));
				ConfigSliderFloat(_("UID_POS_Y_TITLE"), f_UidPosY, 1.0f, static_cast<float>(app::Screen_get_height(nullptr)), _("UID_POS_Y_DESCRIPTION"));
			}

			ConfigCheckbox(_("NAME_TITLE"), f_EnabledName, _("NAME_DESCRIPTION"));

			if (f_EnabledName.getValue())
				ConfigInputText(_("NAME_VALUE_TITLE"), f_Name);

			ConfigCheckbox(_("LEVEL_TITLE"), f_EnabledLevel, _("LEVEL_DESCRIPTION"));

			if (f_EnabledLevel.getValue())
				ConfigInputText(_("LEVEL_VALUE_TITLE"), f_Level);

			ConfigCheckbox(_("WORLDLEVEL_TITLE"), f_EnabledWorldLevel, _("WORLDLEVEL_DESCRIPTION"));

			if (f_EnabledWorldLevel.getValue())
				ConfigInputText(_("WORLDLEVEL_VALUE_TITLE"), f_WorldLevel);

			ConfigCheckbox(_("BIRTHDAY_TITLE"), f_EnabledBirthday, _("BIRTHDAY_DESCRIPTION"));

			if (f_EnabledBirthday.getValue())
				ConfigInputText(_("BIRTHDAY_VALUE_TITLE"), f_Birthday);

			ConfigCheckbox(_("SIGNATURE_TITLE"), f_EnabledSignature, _("SIGNATURE_DESCRIPTION"));

			if (f_EnabledSignature.getValue())
				ConfigInputText(_("SIGNATURE_VALUE_TITLE"), f_Signature);

			ConfigCheckbox(_("EXP_TITLE"), f_EnabledExp, _("EXP_DESCRIPTION"));

			if (f_EnabledExp.getValue()) {
				ConfigDragInt(_("EXP_CURRENT_VALUE_TITLE"), f_CurrentExp, 2, 1, INT32_MAX);
				ConfigDragInt(_("EXP_MAX_VALUE_TITLE"), f_MaxExp, 2, 1, INT32_MAX);
			}

			ConfigCheckbox(_("EXPBAR_TITLE"), f_EnabledExpBar, _("EXPBAR_DESCRIPTION"));

			if (f_EnabledExpBar.getValue())
				ConfigSliderFloat(_("EXPBAR_VALUE_TITLE"), f_ExpBar, 1.0f, 100.0f);

			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void ProfileChanger::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void ProfileChanger::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("PROFILE_CHANGER_TITLE"));
	}

	std::string ProfileChanger::getModule() {
		return _("MODULE_VISUALS");
	}

	app::GameObject* uidTextObj;
	app::Component_1* uidTextComp;

	void onUpdate_1(app::GameManager* __this, app::MethodInfo* method) {
		auto& profileChanger = ProfileChanger::getInstance();

		if (profileChanger.f_Enabled.getValue()) {
			if (profileChanger.f_EnabledUid.getValue()) {
				std::string value = profileChanger.f_Uid.getValue();

				if (uidTextObj == nullptr)
					uidTextObj = app::GameObject_Find(string_to_il2cppi("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

				if (uidTextObj != nullptr && uidTextComp == nullptr)
					uidTextComp = app::GameObject_GetComponentByName(uidTextObj, string_to_il2cppi("Text"));

				app::Text_set_text(reinterpret_cast<app::Text*>(uidTextComp), string_to_il2cppi(value.empty() ? "" : value));

				auto transformWatermark = app::GameObject_get_transform(uidTextObj);

				if (transformWatermark) {
					app::Vector3 uidPos = { profileChanger.f_UidPosX.getValue(), profileChanger.f_UidPosY.getValue(), 0 };

					app::Text_set_alignment(reinterpret_cast<app::Text*>(uidTextComp), app::TextAnchor__Enum::LowerRight);
					app::Text_set_horizontalOverflow(reinterpret_cast<app::Text*>(uidTextComp), app::HorizontalWrapMode__Enum::Overflow);
					app::Text_set_verticalOverflow(reinterpret_cast<app::Text*>(uidTextComp), app::VerticalWrapMode__Enum::Overflow);
					app::Text_set_resizeTextForBestFit(reinterpret_cast<app::Text*>(uidTextComp), false);
					app::Text_set_fontSize(reinterpret_cast<app::Text*>(uidTextComp), profileChanger.f_UidSize.getValue());
					app::Transform_set_position(transformWatermark, uidPos);
				}
			}
		}

		CALL_ORIGIN(onUpdate_1, __this, method);
	}


	app::Button_1* ProfilePage(app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method) {
		auto& profileChanger = ProfileChanger::getInstance();

		if (profileChanger.f_Enabled.getValue()) {
			if (profileChanger.f_EnabledUid.getValue())
				app::Text_set_text(__this->fields._playerID, string_to_il2cppi(profileChanger.f_Uid.getValue()));

			if (profileChanger.f_EnabledName.getValue())
				app::Text_set_text(__this->fields._playerName, string_to_il2cppi(profileChanger.f_Name.getValue()));

			if (profileChanger.f_EnabledLevel.getValue())
				app::Text_set_text(__this->fields._playerLv, string_to_il2cppi(profileChanger.f_Level.getValue()));

			if (profileChanger.f_EnabledWorldLevel.getValue())
				app::Text_set_text(__this->fields._playerWorldLv, string_to_il2cppi(profileChanger.f_WorldLevel.getValue()));

			if (profileChanger.f_EnabledBirthday.getValue())
				app::Text_set_text(__this->fields._playerBirthday, string_to_il2cppi(profileChanger.f_Birthday.getValue()));

			if (profileChanger.f_EnabledSignature.getValue())
				app::Text_set_text(__this->fields._playerSignature, string_to_il2cppi(profileChanger.f_Signature.getValue()));

			if (profileChanger.f_EnabledExp.getValue()) {
				std::string CurExpStr = std::to_string(profileChanger.f_CurrentExp.getValue());
				std::string MaxExpStr = std::to_string(profileChanger.f_MaxExp.getValue());

				app::Text_set_text(__this->fields._playerExp, string_to_il2cppi(CurExpStr + "/" + MaxExpStr));

				if (profileChanger.f_EnabledExpBar.getValue()) {
					app::Slider_1_set_minValue(__this->fields._playerExpSlider, 1.0f);
					app::Slider_1_set_maxValue(__this->fields._playerExpSlider, 100.0f);
					app::Slider_1_set_value(__this->fields._playerExpSlider, profileChanger.f_ExpBar.getValue());
				}
			}
		}
		return CALL_ORIGIN(ProfilePage, __this, method);
	}
}
