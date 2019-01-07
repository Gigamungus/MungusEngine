#include "stdafx.h"
#include "World.h"
#include "Actor.h"

#include "../Resources/MungusLibs/MungusMath.h"
#include "../Resources/MungusLibs/MungusUtil.h"


std::shared_ptr<Mungus::Entity> createEntityFromSourceString(const std::string & title, const std::string & source) {

	std::string sourceText = MungusUtil::removeAllWhiteSpace(source);
	auto itr = sourceText.begin();
	std::string entityType = Mungus::ParseAssetFunctions::getVarName(itr);

	switch (Mungus::ParseAssetFunctions::paramCodes.at(entityType)) {
	case MACTOR:
		return std::make_shared<Mungus::Actor>(title, MACTOR, itr);

	default:
		MLOG("trying to load unsupported asset type: " << entityType);
		return nullptr;
	}
}

void Mungus::World::loadAsset(const std::string& title) {
	std::string assetSource = MungusUtil::getTextFromFile(std::filesystem::current_path().string() + "/../resources/assets/" + title + ".txt");
	entities[title] = (createEntityFromSourceString(title, assetSource));
}
