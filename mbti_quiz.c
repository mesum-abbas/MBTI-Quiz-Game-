#include "raylib.h"
#include <stdio.h>
#include <string.h>

#define NUM_QUESTIONS 16

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "MBTI Quiz");

    Color LIGHTGREEN = {144, 238, 144, 255};
    Color LIGHTPINK = {255, 182, 193, 255};
    Color VIBRANT_COLOR = {255, 215, 0, 255};

    Color bgColors[] = {RAYWHITE, LIGHTGRAY, SKYBLUE, LIGHTGREEN, BEIGE, LIGHTPINK, YELLOW, VIOLET};
    int bgColorIndex = 0;

    Color buttonColor = SKYBLUE;
    Color buttonHoverColor = GRAY;

    const char *questions[NUM_QUESTIONS] = {
        "I prefer solitary activities over social ones.",
        "For a new project, I prefer working solo over team brainstorming.",
        "I often think before I speak.",
        "I find it draining to socialize with large groups.",
        "In planning, I prefer tried-and-true strategies.",
        "I trust practical experience over theory.",
        "I prefer focusing on the present and concrete info.",
        "I do not like thinking about the future and what could be.",
        "I make decisions based on logic.",
        "I strategize rather than rushing with feelings.",
        "In feedback, I focus on honesty over sparing feelings.",
        "I avoid relying on emotions for decisions.",
        "I prefer a planned and organized approach to life.",
        "I thrive on having everything organized ahead of time.",
        "I find satisfaction in checking off completed tasks.",
        "I feel anxious when plans change unexpectedly."
    };

    int answers[NUM_QUESTIONS] = {0};

    int currentQuestion = 0;
    int introvertCount = 0, sensingCount = 0, thinkingCount = 0, judgingCount = 0;

    bool quizComplete = false;
    bool introScreen = true;
    char mbti[5] = "";

    float startTime = GetTime();
    const float timeLimit = 180.0f;

    while (!WindowShouldClose()) {
        float elapsedTime = GetTime() - startTime;
        float remainingTime = timeLimit - elapsedTime;

        if (remainingTime <= 0) {
            remainingTime = 0;
            quizComplete = true;
        }

        BeginDrawing();

        if (quizComplete) {
            ClearBackground(VIBRANT_COLOR);
        } else {
            ClearBackground(bgColors[bgColorIndex]);
        }

        if (introScreen) {
            DrawText("Welcome to MBTI Game", 200, 100, 50, DARKBLUE);
            DrawText("Created by Arquam, Emaan, Ibrahim, Mesum", 260, 200, 20, DARKGRAY);

            Rectangle startButton = {400, 400, 200, 60};
            if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
                DrawRectangleRec(startButton, buttonHoverColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    introScreen = false;
                }
            } else {
                DrawRectangleRec(startButton, buttonColor);
            }
            DrawText("Start Quiz", 450, 415, 30, BLACK);
        } else if (!quizComplete) {
            DrawText("MBTI Quiz", 400, 20, 30, DARKGRAY);
            DrawText(questions[currentQuestion], 100, 100, 25, DARKGRAY);

            const char *options[] = {"Strongly Agree", "Agree", "Neutral", "Disagree", "Strongly Disagree"};
            for (int i = 0; i < 5; i++) {
                Rectangle button = {150, 200 + i * 70, 700, 50};
                if (CheckCollisionPointRec(GetMousePosition(), button)) {
                    DrawRectangleRec(button, buttonHoverColor);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        answers[currentQuestion] = i + 1;

                        if (currentQuestion < 4 && i < 2) introvertCount++;
                        else if (currentQuestion >= 4 && currentQuestion < 8 && i < 2) sensingCount++;
                        else if (currentQuestion >= 8 && currentQuestion < 12 && i < 2) thinkingCount++;
                        else if (currentQuestion >= 12 && currentQuestion < 16 && i < 2) judgingCount++;

                        currentQuestion++;
                        bgColorIndex = (bgColorIndex + 1) % 8;

                        if (currentQuestion >= NUM_QUESTIONS) quizComplete = true;
                    }
                } else {
                    DrawRectangleRec(button, buttonColor);
                }
                DrawText(options[i], 170, 215 + i * 70, 25, BLACK);
            }

            int minutes = (int)(remainingTime / 60);
            int seconds = (int)(remainingTime) % 60;
            char timeText[10];
            snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);
            DrawText(timeText, 850, 20, 25, RED);

            int percentage = (int)((float)currentQuestion / NUM_QUESTIONS * 100);
            char progressText[15];
            snprintf(progressText, sizeof(progressText), "%d%% Completed", percentage);
            DrawText(progressText, 400, 700, 30, DARKBLUE);
        } else {
            DrawText("Quiz Complete!", 350, 100, 40, DARKGREEN);

            mbti[0] = (introvertCount >= 3) ? 'I' : 'E';
            mbti[1] = (sensingCount >= 3) ? 'S' : 'N';
            mbti[2] = (thinkingCount >= 3) ? 'T' : 'F';
            mbti[3] = (judgingCount >= 3) ? 'J' : 'P';
            mbti[4] = '\0';

            DrawText(TextFormat("Your MBTI Type is: %s", mbti), 100, 200, 30, DARKGRAY);

            if (strcmp(mbti, "ISTJ") == 0) {
                DrawText("ISTJ: The Sentinel\n\nGrounded, responsible, and focused, ISTJs are the keepers of order.\nThey are dependable, loyal, and committed to stability.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ISFJ") == 0) {
                DrawText("ISFJ: The Protector\n\nGentle yet strong, ISFJs are unsung heroes who dedicate themselves to others.\nThey create harmony and make an unforgettable impact through kindness.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "INFJ") == 0) {
                DrawText("INFJ: The Advocate\n\nWise and mysterious, INFJs seek meaning in everything and offer deep insights.\nThey are empathetic and visionary individuals.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "INTJ") == 0) {
                DrawText("INTJ: The Mastermind\n\nStrategic and logical, INTJs turn visions into reality.\nThey are focused, determined, and thrive on intellectual challenges.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ISTP") == 0) {
                DrawText("ISTP: The Virtuoso\n\nBold and practical, ISTPs love to tinker and explore.\nThey are resourceful and adventurous problem-solvers.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ISFP") == 0) {
                DrawText("ISFP: The Artist\n\nCreative and passionate, ISFPs live in the present and express themselves authentically.\nThey bring unique charm and beauty to the world.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "INFP") == 0) {
                DrawText("INFP: The Mediator\n\nIdealistic and poetic, INFPs fight for what’s right and express their creativity.\nThey are gentle yet passionate dreamers.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "INTP") == 0) {
                DrawText("INTP: The Thinker\n\nLogical and curious, INTPs dive into theoretical universes and solve mysteries.\nThey love exploring ideas and concepts deeply.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ESTP") == 0) {
                DrawText("ESTP: The Dynamo\n\nBold and outgoing, ESTPs are thrill-seekers who thrive on excitement.\nThey are confident and practical risk-takers.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ESFP") == 0) {
                DrawText("ESFP: The Performer\n\nThe life of the party, ESFPs embrace life with open arms.\nThey bring joy, fun, and laughter wherever they go.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ENFP") == 0) {
                DrawText("ENFP: The Campaigner\n\nEnergetic and enthusiastic, ENFPs explore ideas and inspire others.\nThey see the potential in everyone and love adventure.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ENTP") == 0) {
                DrawText("ENTP: The Debater\n\nQuick-witted and creative, ENTPs love intellectual challenges and debates.\nThey bring innovative solutions to tough problems.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ESTJ") == 0) {
                DrawText("ESTJ: The Executive\n\nPractical and organized, ESTJs bring order to chaos.\nThey are strong leaders who turn ideas into solid results.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ESFJ") == 0) {
                DrawText("ESFJ: The Caregiver\n\nSocial and generous, ESFJs thrive on bringing people together.\nThey create harmony and make communities feel like home.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ENFJ") == 0) {
                DrawText("ENFJ: The Protagonist\n\nCharismatic and inspiring, ENFJs guide others with wisdom and enthusiasm.\nThey create connection and lift others to their full potential.", 100, 300, 20, DARKGREEN);
            } else if (strcmp(mbti, "ENTJ") == 0) {
                DrawText("ENTJ: The Performer\n\nThe life of the party, ESFPs embrace life with open arms.\nThey bring joy, fun, and laughter wherever they go.", 100, 300, 20, DARKGREEN);
}
            int finalPercentage = 100;
            char finalProgressText[15];
            snprintf(finalProgressText, sizeof(finalProgressText), "%d%% Completed", finalPercentage);
            DrawText(finalProgressText, 350, 550, 30, DARKBLUE);

            if (IsKeyPressed(KEY_R)) {
                currentQuestion = 0;
                introvertCount = sensingCount = thinkingCount = judgingCount = 0;
                quizComplete = false;
                introScreen = true;
                bgColorIndex = 0;  // This is to Reset our color cycle
                for (int i = 0; i < NUM_QUESTIONS; i++) {
                    answers[i] = 0;  // this then Resets the answers
                }
                startTime = GetTime();
            }
        }

        EndDrawing();
    }

    CloseWindow();
   
    return 0;
}
