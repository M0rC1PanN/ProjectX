#include "pch.h"

#include "Texture.h"
#include "Define.h"
#include "Main.h"
#include<limits>

SDL_Texture* LoadImage(std::string file, SDL_Renderer* renderer) {
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else {
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	return texture;
}

void DrawTexture(float x, float y, SDL_Texture* tex, SDL_Renderer* rend)
{
	SDL_Rect pos;

	pos.x = x, pos.y = y;

	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	/*if (part == NIGHT) {
		SDL_SetTextureColorMod(tex, 20, 20, 20);
	}
	if (part == MORNING) {
		SDL_SetTextureColorMod(tex, 200, 200, 200);
	}*/
	int current_diff = abs(App::Game_time.GetTime() - PartDuration / 2);
	float parameter = 200.0 * (PartDuration / 2 - current_diff) / (PartDuration / 2);
	for (int i = 1; i <= 2; ++i)
		parameter *= parameter / 200;
	SDL_SetTextureColorMod(tex, parameter, parameter, parameter);
	SDL_RenderCopy(rend, tex, NULL, &pos);
}

bool DrawTexture(SDL_Texture* tex, SDL_Renderer* rend, float X, float Y, float X2, float Y2, float W, float H)
{
	if (tex == NULL || rend == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.h = H;
	DestR.w = W;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	// ChooseColor(tex, X, Y);
	SDL_RenderCopy(rend, tex, &SrcR, &DestR);
	return true;
}

float MagicFunction(float X, float Y, float xH, float yH) {
	int current_diff = abs(App::Game_time.GetTime() - PartDuration / 2);
	float current_radius = (App::Hero.GetVisionRadius() - 8 * current_diff / (PartDuration / 20));
	float deep = current_radius / (200.0*current_diff / (PartDuration / 2));
	float parameter = 200.0 - std::min(sqrt(0.316f*fabs(X - xH)*fabs(X - xH) + fabs(Y - yH)*fabs(Y - yH)), current_radius) / deep;
	for (int i = 1; i <= 4; ++i)
		parameter *= parameter / 200;
	return parameter;
}

void ChooseColor(SDL_Texture* tex, float X, float Y) {
	float xH = App::Hero.X - Camera::CameraControl.GetX(), yH = App::Hero.Y - Camera::CameraControl.GetY();
	X /= TILE_SIZE;
	Y /= TILE_SIZE;
	float parameter = MagicFunction(X, Y, xH, yH);
	SDL_SetTextureColorMod(tex, parameter, parameter, parameter);
}

void DrawText(SDL_Renderer* rend, SDL_Color color, TTF_Font* font, std::string text, float X, float Y, float width, float height) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = X;
	Message_rect.y = Y;
	Message_rect.w = width;
	Message_rect.h = height;
	SDL_RenderCopy(rend, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void DrawBullet(SDL_Renderer* renderer, float X, float Y) {
	SDL_Texture* tex = LoadImage("Pictures/Bullet_proof.bmp", renderer);
	DrawTexture(X, Y, tex, renderer);
}