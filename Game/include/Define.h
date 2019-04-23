// Константы, которые нам пригодятся на протяжении всего проекта

#pragma once
#pragma warning(disable : 4996)

#define MAP_WBLOCK				500
#define MAP_HBLOCK				500

#define TILE_SIZE				32

#define WWIDTH					1920.f
#define WHEIGHT					1088.f

#define FPS						60

#define EntityWidht				32
#define EntityHeight			64

#define PartDuration			600 // X/1000 seconds, длительность части дня
#define OneMinute				100

const float STEP = 0.2;
const float EPS = 0.001;
const float EPS_SPEED = 0.00001;
const int second = 1000;

const int NUM_AGR_NPC = 10;

//const int cave_level = 30;
const int surface_level = 50;

enum partOfDay {
	MORNING,
	DINNER,
	NIGHT,
	COUNT_PART,
	NONE_PART
};