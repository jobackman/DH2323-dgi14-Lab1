// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Interpolate(float a, float b, vector<float>& result);

// --------------------------------------------------------
// FUNCTION DEFINITIONS

void Interpolate(vec3 a, vec3 b, vector<vec3>& result)
{	
	float xdiff = (b.x - a.x) / (result.size() - 1);
	float ydiff = (b.y - a.y) / (result.size() - 1);
	float zdiff = (b.z - a.z) / (result.size() - 1);

	cout << "\n xdiff: " << xdiff;
	cout << "\n ydiff: " << ydiff;
	cout << "\n zdiff: " << zdiff;
	cout << "\n Result.size: " << result.size() << "\n"; //

	for (int i = 0; i<result.size(); ++i)
	{
		result[i].x = a.x + xdiff*i;
		result[i].y = a.y + ydiff*i;
		result[i].z = a.z + zdiff*i;
	}
}

int main(int argc, char* argv[])
{	cout << "START\n";	vector<vec3> result(4);	vec3 a(1, 4, 9.2);	vec3 b(4,1,9.8);	Interpolate(a, b, result); // Fill it with interpolated values

	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (NoQuitMessageSDL())
	{
		Draw();
	}
	SDL_SaveBMP(screen, "screenshot.bmp");
	return 0;
}

void Draw()
{
	vector<vec3> leftSide(SCREEN_HEIGHT);
	vector<vec3> rightSide(SCREEN_HEIGHT);
	vector<vec3> topSide(SCREEN_WIDTH);
	vector<vec3> bottomSide(SCREEN_WIDTH);

	vec3 topLeft(1, 0, 0);		//red
	vec3 topRight(0, 0, 1);		//blue
	vec3 bottomRight(0, 1, 0);	//green
	vec3 bottomLeft(1, 1, 0);	//yellow

	Interpolate(topLeft, bottomLeft, leftSide);
	Interpolate(topRight, bottomRight, rightSide);

	for (int x = 0; x<SCREEN_WIDTH; ++x)
	{ 

		for (int y = 0; y<SCREEN_HEIGHT; ++y)
		{
			vec3 color(leftSide[y].x, leftSide[y].y, leftSide[y].z);
			PutPixelSDL(screen, x, y, color);
		}
	}

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);

}