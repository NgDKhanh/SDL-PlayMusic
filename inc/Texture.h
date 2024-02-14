#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <iostream>
#include "Window.h"

class LClip
{
public:
	LClip(int x, int y, int width, int height)
	{
		mClip = std::make_shared<SDL_Rect>();
		mClip->x = x;
		mClip->y = y;
		mClip->w = width;
		mClip->h = height;
	}

	LClip()
	{
		mClip = std::make_shared<SDL_Rect>();
		mClip->x = 0;
		mClip->y = 0;
		mClip->w = 0;
		mClip->h = 0;
	}

	LClip(SDL_Rect rect)
	{
		mClip = std::make_shared<SDL_Rect>();
		mClip->x = rect.x;
		mClip->y = rect.y;
		mClip->w = rect.w;
		mClip->h = rect.h;
	}

	void setClip(int x, int y, int width, int height)
	{
		mClip->x = x;
		mClip->y = y;
		mClip->w = width;
		mClip->h = height;
	}

	void setClip(SDL_Rect rect)
	{
		mClip->x = rect.x;
		mClip->y = rect.y;
		mClip->w = rect.w;
		mClip->h = rect.h;
	}

	std::shared_ptr<SDL_Rect> getClip() const
	{
		return mClip;
	}

private:
	std::shared_ptr<SDL_Rect> mClip;
};

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	// BUTTON_SPRITE_MOUSE_OVER_MOTION = 2,
	BUTTON_SPRITE_MOUSE_DOWN = 1,
	BUTTON_SPRITE_MOUSE_UP = 2,
	BUTTON_SPRITE_TOTAL = 2
};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		void setRender(Window* window);
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		void render( int x, int y, LClip *clip = nullptr, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth() const;
		int getHeight() const;

		SDL_Texture* getRawTexture() const
		{
			return mTexture.get();
		}

		SDL_Renderer* GetRenderer() const
		{
			return gRenderer.get();
		}

	private:
		//The actual hardware texture
		std::shared_ptr<SDL_Texture> mTexture;

		// std::map<LButtonSprite, LClip> textureClips;

		//Image dimensions
		int mWidth;
		int mHeight;

		// std::shared_ptr<SDL_Renderer> gRenderer;
		std::shared_ptr<SDL_Renderer> gRenderer;

};