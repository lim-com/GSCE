//
// Created by lim on 08.07.2026.
//

#include <iostream>
#include <ostream>

#include "raylib.h"
#include "raylib-imgui/rlImGui.h"
#include "imgui.h"
#include "entt.hpp"
#include "cmath"
#include "spdlog/spdlog.h"

#include "implementations/Application.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void ResizeCanvas(int width, int height)
{
    SetWindowSize(width, height);
}

#ifdef __cplusplus
}
#endif
#endif

constexpr float cameraSensitivity = 0.1f;
constexpr float cameraMovementSpeed = 0.1f;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    bool isCameraUsed = false;

    //auto application = std::make_unique<gsce::web::Application>();

    auto logger = spdlog::stdout_color_mt("gsce");
    logger->info("logger initialized");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d picking");

    //application->Initialize();

    rlImGuiSetup(true);

    // Член класса Application
    RenderTexture viewportRT;

    // Initialize()
    viewportRT = LoadRenderTexture(800, 600);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    //loadModel
    Model model = LoadModel("Cross.obj");

    std::cout << "model loaded" << std::endl;

    if (model.meshes == NULL) {
        // ... обработка ошибки, если модель не загрузилась
        CloseWindow();
        return -1;
    }

    SetTargetFPS(120);                   // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        if (IsWindowResized())
        {
            std::cout << "window resized" << std::endl;
        }
        // Update
        //----------------------------------------------------------------------------------

        if (IsKeyPressed(KEY_T))
        {
            if (IsCursorHidden()) ShowCursor();
            else HideCursor();
        }

        // Camera Transform

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            isCameraUsed = true;
            if (!IsCursorHidden())
            {
                DisableCursor();
            }
        }

        if (IsMouseButtonUp(MOUSE_BUTTON_RIGHT))
        {
            isCameraUsed = false;
            if (IsCursorHidden())
            {
                EnableCursor();
            }

        }

        if (isCameraUsed)
        {
            float cameraMovementForward = 0.f;
            float cameraMovementRight = 0.f;
            float cameraMovementUp = 0.f;

            if (IsKeyDown(KEY_W)) cameraMovementForward = 1.f * cameraMovementSpeed;
            if (IsKeyDown(KEY_S)) cameraMovementForward = -1.f * cameraMovementSpeed;
            if (IsKeyDown(KEY_D)) cameraMovementRight = 1.f * cameraMovementSpeed;
            if (IsKeyDown(KEY_A)) cameraMovementRight = -1.f * cameraMovementSpeed;
            if (IsKeyDown(KEY_Q)) cameraMovementUp = 1.f * cameraMovementSpeed;
            if (IsKeyDown(KEY_E)) cameraMovementUp = -1.f * cameraMovementSpeed;

            const Vector3 cameraMovementVector = {cameraMovementForward, cameraMovementRight,cameraMovementUp};

            Vector2 mouseDelta = GetMouseDelta();
            const Vector3 mouseRotationVector = {mouseDelta.x*cameraSensitivity, mouseDelta.y*cameraSensitivity, 0.0f};


            UpdateCameraPro(&camera, cameraMovementVector, mouseRotationVector, 0);
        }
        else
        {
            UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        }

        // CameraTransformEnded

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetScreenToWorldRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                            (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            }
            else collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Рендерим сцену в текстуру
        BeginTextureMode(viewportRT);

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

            // DrawModel(model, {0, 0, 0}, 1.0f, GRAY);
            // DrawModelWires(model, {0, 0, 0}, 1.0f, BLACK);

            if (collision.hit)
            {
                DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
                DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

                DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
            }
            else
            {
                DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
                DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
            }

            DrawRay(ray, MAROON);
            DrawGrid(20, 1.0f);

        EndMode3D();

        DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

        if (collision.hit) DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30))/2, (int)(screenHeight*0.1f), 30, GREEN);

        DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);

        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }
        DrawFPS(10, 10);

        EndTextureMode();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            rlImGuiBegin();

            //---------

            // Окно с вьюпортом
            ImGui::Begin("3D Viewport");
            ImVec2 size = ImGui::GetContentRegionAvail();
            ImGui::Image((void*)(intptr_t)viewportRT.texture.id, size, ImVec2(0,1), ImVec2(1,0));
            ImGui::End();

            // Можешь добавить другие окна
            ImGui::Begin("Controls");
            ImGui::Text("FPS: %.1f", static_cast<float>(GetFPS()));
            ImGui::End();

            //---------

            // BeginMode3D(camera);
            //
            //     DrawModel(model, {0, 0, 0}, 1.0f, GRAY);
            //     DrawModelWires(model, {0, 0, 0}, 1.0f, BLACK);
            //
            //     // if (collision.hit)
            //     // {
            //     //     DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
            //     //     DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);
            //     //
            //     //     DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
            //     // }
            //     // else
            //     // {
            //     //     DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
            //     //     DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
            //     // }
            //
            //     DrawRay(ray, MAROON);
            //     DrawGrid(20, 1.0f);
            //
            // EndMode3D();
            //
            // DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);
            //
            // if (collision.hit) DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30))/2, (int)(screenHeight*0.1f), 30, GREEN);
            //
            // DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);
            //
            // if (IsKeyPressed(KEY_F))
            // {
            //     ToggleFullscreen();
            // }
            // DrawFPS(10, 10);

            rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);
    rlImGuiShutdown();
    //application->Shutdown();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
