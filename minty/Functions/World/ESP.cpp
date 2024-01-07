#include "ESPRender.h"

namespace cheat 
{
	void DrawExternal();

	ImColor CalcContrastColor(const ImColor& foreground, float maxContrastRatio = 2.0f, const ImColor& background = ImColor(1.0f, 1.0f, 1.0f), const ImColor& inverted = ImColor(0.0f, 0.0f, 0.0f));

    ESP::ESP(){
		f_Enabled = config::getValue("functions:ESP", "enabled", false);

		f_TracerSize = config::getValue("functions:ESP", "tracerSize", 1.f);
		f_OutlineThickness = config::getValue("functions:ESP", "outlineThickness", 1.f);

		f_Range = config::getValue("functions:ESP", "range", 200.f);

		f_DrawBox = config::getValue("functions:ESP", "drawBox", true);
		f_DrawTracer = config::getValue("functions:ESP", "drawTracer", true);

		f_DrawName = config::getValue("functions:ESP", "drawName", false);
		f_DrawDistance = config::getValue("functions:ESP", "drawDistance", false);

		f_FontSize = config::getValue("function::ESP", "textSize", 15);

		f_FillTransparency = config::getValue("functions:ESP", "fillTransparency", 50.f);

		// Filters
		f_Ores = config::getValue("functions:ESP:filters", "ores", false);
		f_Oculies = config::getValue("functions:ESP:filters", "oculies", false);
		f_Plants = config::getValue("functions:ESP:filters", "plants", false);
		f_PickableLoot = config::getValue("functions:ESP:filters", "itemDrops", false);
		f_Chests = config::getValue("functions:ESP:filters", "chests", false); 
		f_Monsters = config::getValue("functions:ESP:filters", "enemies", false);

		f_GlobalBoxColor = config::getValue<std::vector<float>>("functions:ESP:colors", "box", { 0.5f, 0.5f, 0.5f, 1.0f });
		f_GlobalLineColor = config::getValue<std::vector<float>>("functions:ESP:colors", "tracer", { 0.5f, 0.5f, 0.5f, 1.0f });
		f_GlobalESPColor = config::getValue<std::vector<float>>("functions:ESP:colors", "text", { 1.f, 1.f, 1.f, 1.0f });

		GlobalESPColor.Value = { f_GlobalESPColor.getValue()[0], f_GlobalESPColor.getValue()[1], f_GlobalESPColor.getValue()[2], f_GlobalESPColor.getValue()[3] };
		GlobalLineColor.Value = { f_GlobalLineColor.getValue()[0], f_GlobalLineColor.getValue()[1], f_GlobalLineColor.getValue()[2], f_GlobalLineColor.getValue()[3] };
		GlobalBoxColor.Value = { f_GlobalBoxColor.getValue()[0], f_GlobalBoxColor.getValue()[1], f_GlobalBoxColor.getValue()[2], f_GlobalBoxColor.getValue()[3] };

		entityManager = &game::EntityManager::getInstance();
    }

	std::string ESP::getModule() {
		return _("MODULE_WORLD");
    }

	void ESP::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
		DrawExternal();
	}

    void ESP::GUI()
    {
		ConfigCheckbox("ESP", f_Enabled, "Show filtered object through obstacles.");
		if (f_Enabled) {
			ImGui::Indent();
			if (BeginGroupPanel("Config", true))
			{
				ImGuiColorEditFlags_ flag = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar;

				ImGui::SeparatorText("Overlay settings");
				ConfigCheckbox("Draw box", f_DrawBox);
				ConfigCheckbox("Draw tracer", f_DrawTracer); ImGui::SameLine(); HelpMarker("Draw tracer from center of the screen");
				ConfigCheckbox("Draw name", f_DrawName, "Draw name of object.");
				ConfigCheckbox("Draw distance", f_DrawDistance, "Draw distance to object.");
				ConfigSliderInt("Font size", f_FontSize, 1, 100, "Font size of name or distance.");
				ConfigSliderFloat("Range (m)", f_Range, 1.0f, 200.0f); ImGui::SameLine(); HelpMarker("Max. distance to detect target objects");
				ConfigSliderFloat("Outline width", f_OutlineThickness, 1.0f, 20.0f); ImGui::SameLine(); HelpMarker("Thickness of box outline");
				ConfigSliderFloat("Tracer width", f_TracerSize, 1.0f, 20.0f); ImGui::SameLine(); HelpMarker("Thickness of tracer");

				ImGui::SeparatorText("Colors");
				if (ImGui::ColorEdit4("Color of box", &f_GlobalBoxColor.getValue()[0], flag)) {
					config::setValue(f_GlobalBoxColor, f_GlobalBoxColor.getValue());
					f_GlobalBoxColor.setValue(f_GlobalBoxColor.getValue());
				}
				if (ImGui::ColorEdit4("Color of tracer", &f_GlobalLineColor.getValue()[0], flag)) {
					config::setValue(f_GlobalLineColor, f_GlobalLineColor.getValue());
					f_GlobalLineColor.setValue(f_GlobalLineColor.getValue());
				}
				if (ImGui::ColorEdit4("Color of text", &f_GlobalESPColor.getValue()[0], flag)) {
					config::setValue(f_GlobalESPColor, f_GlobalESPColor.getValue());
					f_GlobalESPColor.setValue(f_GlobalESPColor.getValue());
				}
				ConfigSliderFloat("Transparency", f_FillTransparency, 0.01f, 1.0f, "Transparency of box filling.");
			}
			EndGroupPanel();

			if (BeginGroupPanel("Filters", true)) {
				ConfigCheckbox("Ores", f_Ores);
				ConfigCheckbox("Oculies", f_Oculies);
				ConfigCheckbox("Plants", f_Plants);
				ConfigCheckbox("Pickable loot", f_PickableLoot);
				ConfigCheckbox("Chests", f_Chests);
				ConfigCheckbox("Monsters", f_Monsters);
			}
			EndGroupPanel();

			f_Hotkey.Draw();

			ImGui::Unindent();
		}
    }

    void ESP::Status()
    {
	    ImGui::Text("ESP [%.01fm]", f_Range.getValue());
    }

	ESP& ESP::getInstance()
	{
	    static ESP instance;
	    return instance;
    }

    void DrawExternal()
    {
        auto& esp = ESP::getInstance();
	    if (!esp.f_Enabled.getValue())
		    return;

	    PrepareFrame();

	    for (auto& entity : esp.entityManager->entities())
	    {
		    if (esp.entityManager->avatar()->distance(entity) > esp.f_Range.getValue())
			    continue;

			if (!(
				(esp.f_Ores.getValue() and game::filters::combined::Ores.IsValid(entity)) or
				(esp.f_Oculies.getValue() and game::filters::combined::Oculies.IsValid(entity)) or
				(esp.f_Plants.getValue() and game::filters::combined::Plants.IsValid(entity)) or
				(esp.f_PickableLoot.getValue() and 
					(game::filters::combined::AllPickableLoot.IsValid(entity) and
					game::filters::combined::Equipments.IsValid(entity) and 
					game::filters::combined::OresDrop.IsValid(entity))
					) or (esp.f_Chests.getValue() and entity->isChest()) or
				(esp.f_Monsters.getValue() and game::filters::combined::AllMonsters.IsValid(entity))
				))
				continue;

			DrawEntity(entity->name(), entity, esp.GlobalESPColor, CalcContrastColor(esp.GlobalESPColor));
	    }
    }
}
