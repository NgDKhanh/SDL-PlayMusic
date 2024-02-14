#include "Texture.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = nullptr;
	gRenderer = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	// free();

	//The final texture
	std::shared_ptr<SDL_Texture> newTexture = NULL;

	//Load image at specified path
	std::shared_ptr<SDL_Surface> loadedSurface = std::shared_ptr<SDL_Surface>(IMG_Load( path.c_str() ), SDL_FreeSurface);
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface.get(), SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface( gRenderer.get(), loadedSurface.get() ), SDL_DestroyTexture);
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		// SDL_DestroyTexture( mTexture );
		// mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture.get(), red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture.get(), blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture.get(), alpha );
}

void LTexture::setRender(Window *mWindow)
{
	gRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(mWindow->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (gRenderer == nullptr) {
      // Handle renderer creation failure
      std::cerr << "Failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
    }
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip );
}

void LTexture::render( int x, int y, LClip *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != nullptr )
	{
		renderQuad.w = clip->getClip()->w;
		renderQuad.h = clip->getClip()->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer.get(), mTexture.get(), clip->getClip().get(), &renderQuad, angle, center, flip );
}

int LTexture::getWidth() const
{
	return mWidth;
}

int LTexture::getHeight() const
{
	return mHeight;
}