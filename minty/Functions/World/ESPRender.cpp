#include "ESPRender.h"

namespace ESPBase {
	app::Bounds GetEntityBounds(cheat::game::Entity* this_) {
		auto go = this_->gameObject();
		auto comp = reinterpret_cast<app::Collider*>(app::GameObject_GetComponentByName(go, string_to_il2cppi("Collider")));
		app::Bounds bounds = app::Collider_get_bounds(comp);
		return bounds;
	}

	Bounds WorldBoundsToScreen(app::Camera* camera, app::Bounds worldBounds) {
		Bounds returnBounds;
		LOG_INFO("24");
		returnBounds.v_center = app::Camera_WorldToScreen(camera, worldBounds.m_Center);
		returnBounds.v_max = app::Camera_WorldToScreen(camera, worldBounds.m_Extents);
		returnBounds.v_min = app::Camera_WorldToScreen(camera, -worldBounds.m_Extents);
		return returnBounds;
	}

	void DrawBoundsOnScreen(Bounds screenBounds, ESPDrawInfo drawInfo) {
		switch (drawInfo.drawMode) { // 1 - Line, 2 - Rectangle, 3 - Filled rectangle, 4 - Circle, 0 - err
		case 1: {
			ImVec2 bottomMid = { ImGui::GetIO().DisplaySize.x / 2, 0 };
			ImVec2 targetPos = { screenBounds.v_center.x, screenBounds.v_center.y };
			ImGui::GetBackgroundDrawList()->AddLine(bottomMid, targetPos, ImGui::ColorConvertFloat4ToU32(drawInfo.color), drawInfo.tracerWidth);
			break;
		}
		case 2: {
			if (drawInfo.tracerEnabled) {
				ImVec2 bottomMid = { ImGui::GetIO().DisplaySize.x / 2, 0 };
				ImVec2 targetPos = { screenBounds.v_center.x, screenBounds.v_center.y };
				ImGui::GetBackgroundDrawList()->AddLine(bottomMid, targetPos, ImGui::ColorConvertFloat4ToU32(drawInfo.color), drawInfo.tracerWidth);
			}
			ImVec2 min = { screenBounds.v_min.x, screenBounds.v_min.y };
			ImVec2 max = { screenBounds.v_max.x, screenBounds.v_max.y };
			ImGui::GetBackgroundDrawList()->AddRect(min, max, ImGui::ColorConvertFloat4ToU32(drawInfo.color), 5, 0, drawInfo.outlineWidth);
			break;
		}
		case 3: {
			if (drawInfo.tracerEnabled) {
				ImVec2 bottomMid = { ImGui::GetIO().DisplaySize.x / 2, 0 };
				ImVec2 targetPos = { screenBounds.v_center.x, screenBounds.v_center.y };
				ImGui::GetBackgroundDrawList()->AddLine(bottomMid, targetPos, ImGui::ColorConvertFloat4ToU32(drawInfo.color), drawInfo.tracerWidth);
			}
			ImVec2 min = { screenBounds.v_min.x, screenBounds.v_min.y };
			ImVec2 max = { screenBounds.v_max.x, screenBounds.v_max.y };
			ImGui::GetBackgroundDrawList()->AddRectFilled(min, max, ImGui::ColorConvertFloat4ToU32(drawInfo.color), 5, 0);
			break;
		}
		case 4: {
			if (drawInfo.tracerEnabled) {
				ImVec2 bottomMid = { ImGui::GetIO().DisplaySize.x / 2, 0 };
				ImVec2 targetPos = { screenBounds.v_center.x, screenBounds.v_center.y };
				ImGui::GetBackgroundDrawList()->AddLine(bottomMid, targetPos, ImGui::ColorConvertFloat4ToU32(drawInfo.color), drawInfo.tracerWidth);
			}
			ImVec2 center = { screenBounds.v_center.x, screenBounds.v_center.y };
			float radius = screenBounds.v_max.x;
			break;
		}
		default: {
			break;
		}
		}
	}

	bool CompareEntityWithFilter(Filter filter, cheat::game::Entity* entity) {
		//switch (filter.filter) {
		//case zalupa // вотт тут кароч ээ тужа сюда кароч с енамчиком сравнивать по et или както так хз кароч
		//}
		switch (filter.filter) {
		case Enemy: {
			LOG_INFO("ENEMIED");
			if (app::MoleMole_BaseEntity_get_entityType(entity->raw()) == app::EntityType__Enum_1::Monster) {
				return true;
			} break;
		}
		
		}

		return false;
	}

	std::vector<cheat::game::Entity*> FilterEntities(std::vector<Filter> filters, std::vector<cheat::game::Entity*> entities) {
		LOG_INFO("17");
		std::vector<cheat::game::Entity*> returnVec;
		LOG_INFO("18");
		for (auto& ent : entities) {
			LOG_INFO("19");
			for (auto& filter : filters) {
				LOG_INFO("20");
				if (filter.enabled && CompareEntityWithFilter(filter, ent)) {
					LOG_INFO("21");
					returnVec.push_back(ent);
				}
			}
		}
	}

	void DrawESP(app::Camera* camera, cheat::game::EntityManager& manager, std::vector<Filter> filters, ESPDrawInfo drawInfo) {
		LOG_INFO("10");
		auto entities = manager.entities();
		LOG_INFO("11");
		auto filteredEntities = FilterEntities(filters, entities);
		LOG_INFO("12");
		for (auto ent : filteredEntities) {
			LOG_INFO("13");
			LOG_INFO("LOL ONE ENT");
			app::Bounds worldBounds = GetEntityBounds(ent);
			LOG_INFO("14");
			Bounds bounds = WorldBoundsToScreen(camera, worldBounds);
			LOG_INFO("15");
			DrawBoundsOnScreen(bounds, drawInfo);
			LOG_INFO("16");
		}
	}
}

