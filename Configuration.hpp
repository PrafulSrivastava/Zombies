#pragma once
namespace Paths {
	constexpr auto PLAYER_PATH = "assets/graphics/player.png";
	constexpr auto BACKGROUND_PATH = "assets/graphics/background_sheet.png";
	constexpr auto BLOATER_PATH = "assets/graphics/bloater.png";
	constexpr auto CHASER_PATH = "assets/graphics/chaser.png";
	constexpr auto CRAWLER_PATH = "assets/graphics/crawler.png";
	constexpr auto BLOOD_PATH = "assets/graphics/blood.png";
	constexpr auto CROSSHAIR_PATH = "assets/graphics/crosshair.png";
	constexpr auto AMMO_PATH = "assets/graphics/ammo_pickup.png";
	constexpr auto HEALTH_PATH = "assets/graphics/health_pickup.png";
	constexpr auto GAME_OVER_BACKGROUND_PATH = "assets/graphics/background1.png";
	constexpr auto AMMO_ICON_PATH = "assets/graphics/ammo_icon.png";
	constexpr auto FONT_PATH = "assets/fonts/zombiecontrol.ttf";
	constexpr auto GAMEDATA_FILE_PATH = "gamedata/scores.txt";
	constexpr auto HIT_SOUND_PATH = "assets/sound/hit.wav";
	constexpr auto PICKUP_SOUND_PATH = "assets/sound/pickup.wav";
	constexpr auto POWERUP_SOUND_PATH = "assets/sound/powerup.wav";
	constexpr auto RELOAD_SOUND_PATH = "assets/sound/reload.wav";
	constexpr auto RELOAD_FAILED_SOUND_PATH = "assets/sound/reload_failed.wav";
	constexpr auto SHOOT_SOUND_PATH = "assets/sound/shoot.wav";
	constexpr auto SPLAT_SOUND_PATH = "assets/sound/splat.wav";
}

namespace Configs {
	constexpr float START_SPEED = 200;
	constexpr float START_HEALTH = 100;
	constexpr auto HEALTH_DROP = 10;
	constexpr auto HIT_LAG = 200;
	constexpr auto HEALTH_BOOST = 0.2;
	constexpr auto SPEED_BOOST = 0.2;
	constexpr auto GAME_NAME = "Zombie Arena!";
	constexpr auto ARENA_WIDTH = 1000;
	constexpr auto ARENA_HEIGHT = 1000;
	constexpr auto ARENA_TOP = 0;
	constexpr auto ARENA_LEFT = 0;
	constexpr auto TILE_SIZE = 50;
	constexpr auto TILE_TYPES = 3;
	constexpr auto VERTS_IN_QUAD = 4;
	constexpr auto BLOATER_SPEED = 70;
	constexpr auto CHASER_SPEED = 100;
	constexpr auto CRAWLER_SPEED = 50;
	constexpr auto BLOATER_HEALTH = 5;
	constexpr auto CHASER_HEALTH = 1;
	constexpr auto CRAWLER_HEALTH = 3;
	constexpr auto MAX_VARIANCE = 30;
	constexpr auto OFFSET = 101 - MAX_VARIANCE;
	constexpr auto MULTIPLIER = 100;
	constexpr auto PIE = 3.141;
	constexpr auto ZOMBIE_SPAWN_ADJUSTMENT = 20;
	constexpr auto NUM_ZOMBIES = 25;
	constexpr auto BULLET_WIDTH = 4;
	constexpr auto BULLET_HEIGHT = 4;
	constexpr auto BULLET_SPEED = 1000;
	constexpr auto BULLET_RANGE = 1000;
	constexpr auto TOTAL_BULLETS = 100;
	constexpr auto CLIP_SIZE = 6;
	constexpr auto SPARE_BULLETS = 50;
	constexpr auto FIRE_RATE = 3.0f;
	constexpr auto HEALTH_START_VAL = 50;
	constexpr auto AMMO_START_VAL = 12;
	constexpr auto START_WAIT_TIME = 10;
	constexpr auto START_SECONDS_TO_LIVE = 10;
	constexpr auto PICKUP_ARENA_OFFSET = 50;
	constexpr auto PAUSED_TEXT_FONT_SIZE = 85;
	constexpr auto GAME_OVER_TEXT_FONT_SIZE = 80;
	constexpr auto SCORE_TEXT_FONT_SIZE = 50;
	constexpr auto HIGH_SCORE_TEXT_FONT_SIZE = 50;
	constexpr auto ZOMBIES_REMAINING_TEXT_FONT_SIZE = 50;
	constexpr auto AMMO_FONT_SIZE = 50;
	constexpr auto WAVE_FONT_SIZE = 50;
	constexpr auto FPS_MEASURMENT_FRAME_INTERVAL = 300;
}

namespace Coordinates {
	constexpr auto PLAYER_ORIGIN_X = 25;
	constexpr auto PLAYER_ORIGIN_Y = 25;
	constexpr auto AMMO_ICON_X = 0;
	constexpr auto AMMO_ICON_Y = 0;
	constexpr auto AMMO_TEXT_X = 50;
	constexpr auto AMMO_TEXT_Y = 0;
	constexpr auto PAUSED_TEXT_X = 350;
	constexpr auto PAUSED_TEXT_Y = 200;
	constexpr auto GAME_OVER_TEXT_X = 280;
	constexpr auto GAME_OVER_TEXT_Y = 540;
	constexpr auto SCORE_TEXT_X = 300;
	constexpr auto SCORE_TEXT_Y = 0;
	constexpr auto HIGH_SCORE_X = 700;
	constexpr auto HIGH_SCORE_Y = 0;
	constexpr auto ZOMBIES_REMAINING_TEXT_X = 1100;
	constexpr auto ZOMBIES_REMAINING_TEXT_Y = 0;
	constexpr auto HEALTHBAR_X = 1500;
	constexpr auto HEALTHBAR_Y = 0;
	constexpr auto WAVE_X = 750;
	constexpr auto WAVE_Y = 0;
}

enum class State {
	PAUSED,
	LEVELING_UP,
	GAME_OVER,
	PLAYING
};

enum class ZombieType {
	BLOATER,
	CHASER,
	CRAWLER,
	NONE
};

enum class PickupType {
	HEALTH,
	AMMO
};