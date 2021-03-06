#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Window.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

j1Textures::j1Textures() : j1Module()
{
	name = "textures";
}

j1Textures::~j1Textures()
{}

// Called before render is available
bool j1Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool j1Textures::Start()
{
	LOG("Start module textures");
	bool ret = true;

	SDL_SetWindowIcon(App->win->window, LoadSurface("gui/appicon.png"));

	return ret;
}

// Called before quitting
bool j1Textures::CleanUp()
{
	LOG("Freeing textures and Image library");
	bool ret = true;

	Texture*  item;

	for (std::list<Texture*>::iterator it = textures.begin(); it != textures.end(); it++) 
	{
		SDL_DestroyTexture((*it)->tex);
		RELEASE(*it);
	}

	textures.clear();
	IMG_Quit();

	return ret;
}

// Load new texture from file path
SDL_Texture* const j1Textures::LoadTexture(const char* path)
{
	SDL_Texture* texture = nullptr;

	// Check if the texture is already loaded
	for (std::list<Texture*>::iterator it = textures.begin(); it != textures.end(); it++) 
	{
		if ((*it)->path == path) 
		{
			texture = (*it)->tex;
			break;
		}
	}

	// If the texture doesn't exist, load it on memory
	if (texture == nullptr) 
	{
		Texture* new_tex = new Texture(path);
		texture = new_tex->tex;
		textures.push_back(new_tex);
	}

	return texture;
}

SDL_Surface * const j1Textures::LoadSurface(const char * path)
{
	SDL_Surface* surface = NULL;
	surface = IMG_Load_RW(App->fs->Load(path), 1);

	if (surface == NULL)
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	
	return surface;
}

// Unload texture
bool j1Textures::UnLoadTexture(SDL_Texture* texture)
{
	if (texture == nullptr)
		return false;

	for (std::list<Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		if (texture == (*it)->tex)
		{
			SDL_DestroyTexture((*it)->tex);
			RELEASE(*it);
			textures.erase(it);
			return true;
		}
	}

	if(texture != nullptr) 
		SDL_DestroyTexture(texture); // if texture not found but exist delete it

	return false;
}

// Translate a surface into a texture
SDL_Texture* const j1Textures::SurfaceToTexture(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

	if (texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}

	return texture;
}

// Retrieve size of a texture
void j1Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*) &width, (int*) &height);
}

Texture::Texture()
{
}

Texture::Texture(const char * path)
{
	SDL_Surface* surface = IMG_Load_RW(App->fs->Load(path), 1);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		tex = App->tex->SurfaceToTexture(surface);
		SDL_FreeSurface(surface);

		this->path = path;
	}
}
