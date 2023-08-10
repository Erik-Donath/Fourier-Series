#include <stdio.h>
#include "raylib.h"

int main(int argc, char* argv[]) {
	InitWindow(800, 600, "Fourier Series");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({ 45, 45, 45, 255 });
		EndDrawing();
	}
	CloseWindow();
}
