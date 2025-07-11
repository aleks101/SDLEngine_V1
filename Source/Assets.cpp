#include "pch.h"
#include "Assets.h"

std::vector<Texture> Assets::textures;
std::vector<Font> Assets::fonts;

std::vector<AudioMusic> Assets::musics;
std::vector<AudioSound> Assets::sounds;

void Assets::AddTexture(SDL_Renderer* ren, const char* imageFile, int flag) {
	IMG_Init(flag);
	SDL_Surface* surf = IMG_Load(imageFile);
	if (surf == NULL)
		LOG("SURF ERROR\n");
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
	if (tex == NULL)
		LOG("TEX ERROR\n");
	SDL_FreeSurface(surf);

	textures.push_back(Texture(imageFile, tex));
}
SDL_Texture* Assets::GetTexture(const char* imageFile) {
	for (auto texture : textures)
		if (texture.imageFile == imageFile)
			return texture.texture;
}
void Assets::CleanTextures() {
	for (auto& texture : textures)
		SDL_DestroyTexture(texture.texture);
	textures.clear();
	IMG_Quit();
}
void Assets::AddFont(const char* fontFile, int size) {
	if (TTF_Init() < 0) {
		LOG("Error initializing SDL_ttf: ");
		LOG(TTF_GetError());
	}

	TTF_Font* font = TTF_OpenFont(fontFile, size);
	if (!font) {
		LOG("Failed to load font: ");
		LOG(TTF_GetError());
	}
	
	fonts.push_back(Font(fontFile, font));
}
TTF_Font* Assets::GetFont(const char* fontFile) {
	for (auto font : fonts)
		if (font.fontFile == fontFile)
			return font.font;
}
void Assets::CleanFonts() {
	for (auto& font : fonts)
		TTF_CloseFont(font.font);
	fonts.clear();
	TTF_Quit();
}

void Assets::AddSound(const char* soundFile) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: \n");
		LOG(Mix_GetError());
	}
	Mix_Chunk* chunk = Mix_LoadWAV(soundFile);
	if (chunk == NULL) {
		LOG("Failed to load beat chunk! SDL_mixer Error: %s\n");
		LOG(Mix_GetError());
	}
	sounds.push_back(AudioSound(soundFile, chunk));
}
Mix_Chunk* Assets::GetSound(const char* soundFile) {
	for (auto audio : sounds)
		if (audio.audioFile == soundFile)
			return audio.chunk;
}
void Assets::CleanSounds() {
	for (auto& audio : sounds)
		Mix_FreeChunk(audio.chunk);
	sounds.clear();
	Mix_Quit();
}
void Assets::AddMusic(const char* musicFile) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n");
		LOG(Mix_GetError());
	}
	Mix_Music* music=Mix_LoadMUS(musicFile);
	if (music == NULL)
	{
		LOG("Failed to load beat music! SDL_mixer Error: %s\n");
		LOG(Mix_GetError());
	}
	musics.push_back(AudioMusic(musicFile, music));
}
Mix_Music* Assets::GetMusic(const char* musicFile) {
	for (auto audio : musics)
		if (audio.audioFile == musicFile)
			return audio.music;
}
void Assets::CleanMusic() {
	for (auto& audio : musics)
		Mix_FreeMusic(audio.music);
	musics.clear();
	Mix_Quit();
}