#include "pch.h"
#include "Map.h"

Map::Map(Object* camObj)  : m_camObj(camObj) {
	LOG("MAP CONSTRUCTED\n");
}
Map::~Map() {
	LOG("MAP DECONSTRUCTED\n");
}
void Map::Update() {
	for (auto& tile : m_tiles)
		tile.UpdatePositionRelativeToPlayer();
}
void Map::Render() {
	//SDL_Rect* screen;
	for (auto& tile : m_tiles) {
		//screen = tile.GetScreen();
		tile.Update();
	}
}
void Map::AddLayer(SDL_Renderer* ren, std::string filePath, std::vector<TexID> textures, Vec2 startPos, int size, bool isSolid) {
	std::ifstream data;
	data.open(filePath);
	if (data.is_open()) {
		int width, height, id;
		data >> width >> height;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				data >> id;
				for (int k = 0; k < textures.size(); k++) {
					if (textures[k].id == id) {
						m_tiles.push_back(Tile(ren, textures[k].tex, { static_cast<int>(startPos.x) + size * j, static_cast<int>(startPos.y) + size * i, size, size }, m_camObj->GetDest(), isSolid));
						break;
					}
				}
			}
		}
		LOG("LAYER ADDED\n");
	}
	else {
		LOG("MAP FILE ");
		LOG(" NOT FOUND\n");
	}
	data.close();
}
void Map::AddLayer(SDL_Renderer* ren, std::string mapFile, std::string tilesetFile, SDL_Texture* tex, Vec2 startPos, int size, bool isSolid) {
	std::vector<TileID> tileIDs;

	int xOffset = 0, yOffset = 0;
	int srcTileWidth = 0, srcTileHeight = 0;
	int tilesetWidth = 0, tilesetHeight = 0;
	int tileID;

	std::ifstream tileset;

	tileset.open(tilesetFile);
	if (!tileset.is_open()) {
		LOG("ERROR READIN TILESET FILE: ");
		LOGln(tilesetFile);
		return;
	}

	tileset >> srcTileWidth >> srcTileHeight;
	tileset >> xOffset >> yOffset;
	tileset >> tilesetWidth >> tilesetHeight;

	for (int i = 0; i < tilesetHeight; i++) {
		for (int j = 0; j < tilesetWidth; j++) {
			tileset >> tileID;

			SDL_Rect pos;

			pos.x = srcTileWidth * j + xOffset * j;
			pos.y = srcTileHeight * i + yOffset * i;
			pos.w = srcTileWidth;
			pos.h = srcTileHeight;

			tileIDs.push_back(TileID(pos, tileID));
		}
	}
	tileset.close();

	std::ifstream map;

	map.open(mapFile);
	if (map.is_open()) {
		int width, height, id;
		map >> width >> height;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				map >> id;
				for (int k = 0; k < tileIDs.size(); k++) {
					if (tileIDs[k].id == id) {
						m_tiles.push_back(Tile(ren, tex, { static_cast<int>(startPos.x) + size * j, static_cast<int>(startPos.y) + size * i, size, size }, m_camObj->GetDest(), isSolid));
						m_tiles[m_tiles.size() - 1].SetSrc(tileIDs[k].tilePosition);
						break;
					}
				}
			}
		}
		LOGln("LAYER ADDED");
		map.close();
	}
	else {
		LOG("MAP FILE "); LOG(mapFile); LOGln(" NOT FOUND");
	}
}
void Map::RemoveTile(int index) {
	if(m_tiles.begin()+index <= m_tiles.end())
		m_tiles.erase(m_tiles.begin() + index);
}
void Map::MoveTilesFor(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.ChangeDestPosFor(newPos);
		tile.ChangeScreenPosFor(newPos);
	}
}
void Map::MoveTilesTo(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.SetDestPos(newPos);
		tile.SetScreenPos(newPos);
	}
}
void Map::MoveDisplayTilesFor(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.ChangeScreenPosFor(newPos);
	}
}
void Map::MoveDisplayTilesTo(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.SetScreenPos(newPos);
	}
}
bool Map::CheckCollisionDest(Object* object) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(*tile.GetDest(), *object->GetDest())) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollisionDest(SDL_Rect* dest) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(*tile.GetDest(), *dest)) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollisionDest(Vec2 point) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionPoint(*tile.GetDest(), point)) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollisionScreen(Object* object) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(*tile.GetScreen(), *object->GetScreen())) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollision(Object* object, bool destOrScreen, bool XorY) {
	//destOrScreen : true=dest, false=screen
	//XorY : true=x, false=y
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (destOrScreen) {
				if (coll::CheckCollisionAABB(*tile.GetDest(), *object->GetDest())) {
					if (XorY) {
						if (coll::CheckCollisionX(*tile.GetDest(), *object->GetDest()))
							return true;
					}
					else {
						if (coll::CheckCollisionY(*tile.GetDest(), *object->GetDest()))
							return true;
					}
				}
			}
			else {
				if (coll::CheckCollisionAABB(*tile.GetScreen(), *object->GetScreen())) {
					if (XorY) {
						if (coll::CheckCollisionX(*tile.GetScreen(), *object->GetScreen()))
							return true;
					}
					else {
						if (coll::CheckCollisionY(*tile.GetScreen(), *object->GetScreen()))
							return true;
					}
				}
			}
		}
	}
	return false;
}