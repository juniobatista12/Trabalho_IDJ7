#pragma once
#include "Component.h"
#include <SDL_ttf.h>
class Text : public Component {
public:
	enum TextStyle {SOLID, SHADED, BLENDED};
	Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
	~Text();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void SetText(string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(string fontFile);
	void SetFontSize(int fontSize);
private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	string text;
	TextStyle style;
	string fontFile;
	int fontSize;
	SDL_Color color;
};

