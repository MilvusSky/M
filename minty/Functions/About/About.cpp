#include "About.h"

namespace cheat {
	About::About() {
		mVersion = "4.3.0.3-stable";
	}
	void About::GUI() {
		ImGui::SeparatorText(_("MODULE_ABOUT"));

		ImGui::Text("%s: %s", _("ABOUT_MINTY_VERSION"), mVersion);
		ImGui::Text("%s: %s", _("ABOUT_IMGUI_VERSION"), ImGui::GetVersion());
		ImGui::Text("%s %s", _("ABOUT_DESIGN"), "KittyKate :3");

		ImGui::SeparatorText(_("ABOUT_CONTRIBUTORS"));

		ImGui::TextColored(ImVec4(235.0F / 255.0F, 64.0F / 255.0F, 52.0F / 255.0F, 1.0),
			"%s: MintyGingy", _("ABOUT_OWNER"));
		ImGui::TextColored(ImVec4(219.0F / 255.0F, 57.0F / 255.0F, 219.0F / 255.0F, 1.0),
			"%s: Moistcrafter", _("ABOUT_CO-FOUNDER"));
		ImGui::TextColored(ImVec4(57.0F / 255.0F, 68.0F / 255.0F, 219.0F / 255.0F, 1.0),
			"%s: EtoShinya, KittyKate, lilmayofuksu, USSY, akioukun, sad_akulka, Micah, wat3r1ng", _("ABOUT_CONTRIBUTORS"));
		ImGui::TextColored(ImVec4(255, 0, 212, 255),
			"%s: Thomas_Heath, Blair, unmeinoshonen, USSY", _("ABOUT_DONATERS"));
		ImGui::TextColored(ImVec4(0, 255, 179, 255),
			"%s: Futchev, yarik0chka, keitaro_gg", _("ABOUT_FAMILY"));
		ImGui::TextColored(ImVec4(212, 0, 179, 255),
			"%s: Micah, Amireux, d3adp3r50n, Niko", _("ABOUT_TRANSLATORS"));


		ImGui::Text("%s: ", _("ABOUT_GITHUB"));
		TextURL(_("ABOUT_LINK"), "https://github.com/kindawindytoday/Minty-Releases", true, false);

		ImGui::Text("%s: ", _("ABOUT_DISCORD"));
		TextURL(_("ABOUT_LINK"), "https://discord.gg/kindawindytoday", true, false);
	}

	std::string About::getModule() {
		return _("MODULE_ABOUT");
	}

	About& About::getInstance() {
		static About instance;
		return instance;
	}
}
