#include "raylib.h"
#include "raymath.h"

#include "Defines.h"

#define Width  (GetScreenWidth())
#define Height (GetScreenHeight())

#define FourierCircleColor { 102, 255, 102, 125 }
#define FourierLineColor BLUE
#define PointerColor RED
#define LineColor ORANGE

#define LineSec 315
float line[LineSec];
double nextPush = -666.0f;

void PushLine(float y) {
	for(u32 i = LineSec - 1; i > 0; i--) {
		line[i] = line[i - 1];
	}
	line[0] = y;
}
void DrawSeries(Vector2 start, u32 n = 100, float speed = 1.0f) {
	double t = GetTime();
	for (u32 i = 0; i < n; i++) {
		i32 n = 2 * i + 1; // N function

		float r = 100 * (4 / (n * PI)); // Radius function
		DrawCircleLines(start.x, start.y, r, FourierCircleColor);

		Vector2 pos{
			start.x + r *  cosf(n * (t * speed)),
			start.y + r * -sinf(n * (t * speed))
		};
		DrawLineV(start, pos, FourierLineColor);
		start = pos;
	}

	// Draw the line
	float px = Width / 2 + Width / 10;
	for (u32 i = 0; i < LineSec - 2; i++) {
		u32 s = 2 * i + px;
		DrawLine(s, line[i], s + 2, line[i + 1], LineColor);
	}

	// Draw Pointer
	Vector2 pv{ px, start.y };
	DrawLineV(start, pv, PointerColor);
	DrawLineV(pv, { pv.x, line[0] }, LineColor);

	if (t >= nextPush) {
		PushLine(start.y);
		nextPush = t + 0.025 * (1.0f / speed);
	}
}

int main(i32 argc, char* argv[]) {
	//SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1500, 800, "Fourier Series");

	// Init line to center
	for (u32 i = 0; i < LineSec - 1; i++) {
		line[i] = Height / 3;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({ 35, 35, 35, 255 });

		DrawSeries({ Width / 3.0f, Height / 3.0f }, 128, 0.5f); // speed = 0.4462278f
		
		i32 height = Height / 2 + Height / 10;
		DrawRectangle(0, height, Width, Height - height, { 30, 30, 30, 255 });

		DrawFPS(5, 5);
		EndDrawing();
	}
	CloseWindow();
}
