#include "About.h"

namespace cheat {
	void About::GUI() {
        ImGui::SeparatorText(_("About"));

        ImGui::Text(_("Minty version : %s"), "1.41");
        ImGui::Text(_("ImGui version: %s"), ImGui::GetVersion());
        ImGui::Text(_("Design made with love by KittyKate :3"));

        ImGui::SeparatorText(_("Contributors"));

        ImGui::TextColored(ImVec4(235.0F / 255.0F, 64.0F / 255.0F, 52.0F / 255.0F, 1.0), _("Owner: MintyGingy"));
        ImGui::TextColored(ImVec4(219.0F / 255.0F, 57.0F / 255.0F, 219.0F / 255.0F, 1.0), _("Co-founder: Moistcrafter"));
        ImGui::TextColored(ImVec4(57.0F / 255.0F, 68.0F / 255.0F, 219.0F / 255.0F, 1.0), _("Contributors: EtoShinya, KittyKate, lilmayofuksu, USSY, akioukun, sad_akulka, Micah, wat3r1ng"));
        ImGui::TextColored(ImVec4(255, 0, 212, 255), _("Donaters: Thomas_Heath, Blair, unmeinoshonen, USSY"));
        ImGui::TextColored(ImVec4(0, 255, 179, 255), _("Special thanks to family: Futchev, yarik0chka, keitaro_gg"));
        ImGui::TextColored(ImVec4(212, 0, 179, 255), _("Translator: Micah, Amireux, d3adp3r50n, Niko"));


	ImGui::Text("Minty Github: ");
	TextURL(_("Link"), "https://github.com/kindawindytoday/Minty-Releases", true, false);

	ImGui::Text("KWT Discord: ");
	TextURL(_("Link"), "https://discord.gg/kindawindytoday", true, false);
	}

    std::string About::getModule() {
        return _("About");
    }

    About& About::getInstance() {
        static About instance;
        return instance;
    }
}
