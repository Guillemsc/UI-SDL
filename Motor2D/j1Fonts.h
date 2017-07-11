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

	// Destructor
	virtual ~j1Fonts();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Load Font
	Font* LoadFont(const char* path, const char* name, int size = 12);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = {255, 255, 255, 255}, Font* font = nullptr);

	bool CalcSize(const char* text, int& width, int& height, Font* font) const;

	Font* GetFont(const char* name);

protected:
	std::list<Font*>	    fonts;

public:
	_TTF_Font*			    default = nullptr;

};

struct Font
{
	_TTF_Font* font = nullptr;
	string name = "";
};


#endif // __j1FONTS_H__