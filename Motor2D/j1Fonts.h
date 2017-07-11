#ifndef __j1FONTS_H__
#define __j1FONTS_H__

#include "j1Module.h"
#include "SDL\include\SDL_pixels.h"
#include <list>

#define DEFAULT_FONT "fonts/open_sans/OpenSans-Regular.ttf"
#define DEFAULT_FONT_SIZE 12

struct SDL_Texture;
struct _TTF_Font;
struct Font;

class j1Fonts : public j1Module
{
public:
	j1Fonts();

	virtual ~j1Fonts();

	bool Awake(pugi::xml_node&);

	bool CleanUp();

	Font* LoadFont(const char* path, const char* name, int size = 12);
	SDL_Texture* Print(const char* text, SDL_Color color = {255, 255, 255, 255}, Font* font = nullptr);
    bool CalcSize(const char* text, int& width, int& height, Font* font);
	Font* GetFont(const char* name);

protected:
	std::list<Font*> fonts;
};

struct Font
{
	_TTF_Font* font = nullptr;
	string     name = "";
};


#endif // __j1FONTS_H__