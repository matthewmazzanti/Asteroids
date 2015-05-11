#include "Texture.h"


Texture::Texture(SDL_Renderer* inRenderer)
{
	//Initialize
	_Texture = NULL;
	_Width = 0;
	_Height = 0;
	_Pixels = NULL;
	_Pitch = 0;

	_Renderer = inRenderer;
}

Texture::~Texture()
{
	//Deallocate
	free();
	_Renderer = NULL;
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &_Pixels, &_Pitch);

				//Copy loaded/formatted surface pixels
				memcpy(_Pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				_Width = formattedSurface->w;
				_Height = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)_Pixels;
				int pixelCount = (_Pitch / 4) * _Height;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				_Pixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_Texture = newTexture;
	return _Texture != NULL;
}

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		_Texture = SDL_CreateTextureFromSurface(_Renderer, textSurface);
		if (_Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = textSurface->w;
			_Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return _Texture != NULL;
}
#endif

bool Texture::createBlank(int width, int height, SDL_TextureAccess access)
{
	//Create uninitialized texture
	_Texture = SDL_CreateTexture(_Renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
	if (_Texture == NULL)
	{
		printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		_Width = width;
		_Height = height;
	}

	return _Texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (_Texture != NULL)
	{
		SDL_DestroyTexture(_Texture);
		_Texture = NULL;
		_Width = 0;
		_Height = 0;
		_Pixels = NULL;
		_Pitch = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(_Texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(_Texture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(_Texture, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, _Width, _Height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(_Renderer, _Texture, clip, &renderQuad, angle, center, flip);
}

void Texture::setAsRenderTarget()
{
	//Make self render target
	SDL_SetRenderTarget(_Renderer, _Texture);
}

int Texture::getWidth()
{
	return _Width;
}

int Texture::getHeight()
{
	return _Height;
}

bool Texture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (_Pixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(_Texture, NULL, &_Pixels, &_Pitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool Texture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (_Pixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(_Texture);
		_Pixels = NULL;
		_Pitch = 0;
	}

	return success;
}

void* Texture::getPixels()
{
	return _Pixels;
}

void Texture::copyPixels(void* pixels)
{
	//Texture is locked
	if (_Pixels != NULL)
	{
		//Copy to locked pixels
		memcpy(_Pixels, pixels, _Pitch * _Height);
	}
}

int Texture::getPitch()
{
	return _Pitch;
}

Uint32 Texture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)_Pixels;

	//Get the pixel requested
	return pixels[(y * (_Pitch / 4)) + x];
}

