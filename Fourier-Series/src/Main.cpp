#include "raylib.h"
#include "raymath.h"
#include "../vendor/raygui.h"

#include "Defines.h"

#define Width  (GetScreenWidth())
#define Height (GetScreenHeight())

#define FourierCircleColor { 102, 255, 102, 125 }
#define FourierLineColor BLUE
#define PointerColor RED
#define LineColor ORANGE

#define LineSec 210
float line[LineSec];
double nextPush = -666.0f;

float g_Speed = 5.0f;
float g_N = 10;

void ClearLine(float y) {
	for (u32 i = 0; i < LineSec - 1; i++) {
		line[i] = y;
	}
}
void PushLine(float y) {
	for(u32 i = LineSec - 1; i > 0; i--) {
		line[i] = line[i - 1];
	}
	line[0] = y;
}
void DrawSeries(Vector2 start, float lineX, u32 n = 100, float speed = 1.0f) {
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
	for (u32 i = 0; i < LineSec - 2; i++) {
		u32 s = 2 * i + lineX;
		DrawLine(s, line[i], s + 2, line[i + 1], LineColor);
	}

	// Draw Pointer
	Vector2 pv{ lineX, start.y };
	DrawLineV(pv, { pv.x, line[0] }, LineColor);
	DrawLineV(start, pv, PointerColor);

	if (t >= nextPush) {
		PushLine(start.y);
		nextPush = t + 0.025 * (1.0f / speed);
	}
}
void DrawGui(float height) {
	DrawRectangle(0, height, Width, Height - height, { 20, 20, 20, 255 });
	GuiSliderBar({ 50, height + 20, 200, 20 }, "Speed", TextFormat("%0.2f", g_Speed), &g_Speed, 0.01f, 50.0f);
	GuiSliderBar({ 50, height + 50, 200, 20 }, "N", TextFormat("%0.0f", g_N), &g_N, 0.0f, 100.0f);
	DrawText(TextFormat("%0.3fsec", nextPush - GetTime()), 285+240, height + 30, 30, GRAY);
	if (GuiButton({ 285+0, height + 20, 50,  50 }, "Reset")) {
		g_N = 10.0f;
		g_Speed = 5.0f;
		nextPush = -666.0f;
		ClearLine(line[0]);
	}
	if (GuiButton({ 285+60, height + 20, 50,  50 }, "Ultra")) {
		g_N = 100.0f;
		g_Speed = 25.0f;
		nextPush = -666.0f;
	}
	if (GuiButton({ 285+120, height + 20, 50,  50 }, "Clear")) {
		nextPush = -666.0f;
		ClearLine(line[0]);
	}
	if (GuiButton({ 285+180, height + 20, 50,  50 }, "Push")) {
		nextPush = -666.0f;
	}
}

int main(i32 argc, char* argv[]) {
	//SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1000, 600, "Fourier Series");

	// Init line to center
	ClearLine(250);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({ 30, 30, 30, 255 });

		DrawSeries({ 300, 250 }, 600, floor(g_N), g_Speed); // speed = 0.4462278f
		DrawGui(515);

		DrawFPS(5, 5);
		EndDrawing();
	}
	CloseWindow();
}
