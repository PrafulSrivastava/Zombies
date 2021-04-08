#include <iostream>
#include "Player.hpp"
#include "Configuration.hpp"
#include "ZombieArena.hpp"
#include "TextureHolder.hpp"
#include "Bullet.hpp"
#include "Pickup.hpp"
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>

using namespace sf;

void setFontAttributes(sf::Text& text, sf::Font& font, const std::string& str, const sf::Color& color, const int& x, const int& y, const int& size) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
}


void setSoundAttributes(sf::SoundBuffer& buffer, sf::Sound& sound, const std::string& path) {
    buffer.loadFromFile(path);
    sound.setBuffer(buffer);
}

void gamelogic() {

    TextureHolder holder;
    State state = State::GAME_OVER;
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), Configs::GAME_NAME, Style::Default);
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));
    Clock clock;
    Time gameTotalTime;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Player player;
    IntRect arena;
    Pickup healthPickup(PickupType::HEALTH);
    Pickup ammoPickup(PickupType::AMMO);
    vector<Bullet> bullets(Configs::TOTAL_BULLETS);
    int currentBullet = 0;
    int bulletsSpare = Configs::SPARE_BULLETS;
    int bulletsInClip = Configs::CLIP_SIZE;
    float fireRate = Configs::FIRE_RATE;
    Time lastPressed;
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(Coordinates::HEALTHBAR_X, Coordinates::HEALTHBAR_Y);

    Sprite spriteGameOver = Sprite(TextureHolder::GetTexture(Paths::GAME_OVER_BACKGROUND_PATH));
    spriteGameOver.setPosition(0, 0);
    Sprite spriteAmmoIcon = Sprite(TextureHolder::GetTexture(Paths::AMMO_ICON_PATH));
    spriteAmmoIcon.setPosition(Coordinates::AMMO_ICON_X, Coordinates::AMMO_ICON_Y);

    VertexArray background;
    Texture textureBackground = TextureHolder::GetTexture(Paths::BACKGROUND_PATH);

    window.setMouseCursorVisible(false);
    Sprite spriteCrossHair = Sprite(TextureHolder::GetTexture(Paths::CROSSHAIR_PATH));
    spriteCrossHair.setOrigin(Coordinates::PLAYER_ORIGIN_X, Coordinates::PLAYER_ORIGIN_Y);
    int score = 0;
    int highScore = 0;
    int wave = 0;
    int sinceLastHUDFrameUpdate = 0;
    int fpsMeasurmentFrameInterval = Configs::FPS_MEASURMENT_FRAME_INTERVAL;
    Font font;
    font.loadFromFile(Paths::FONT_PATH);

    Text textPaused, textGameOver, textScore, textHighScore, textZombiesRemaining, textAmmo, textWave;
    setFontAttributes(textPaused, font, "Press Enter\nto continue..", Color::White, Coordinates::PAUSED_TEXT_X, Coordinates::PAUSED_TEXT_Y, Configs::PAUSED_TEXT_FONT_SIZE);
    setFontAttributes(textGameOver, font, "Press Enter To Play!", Color::White, Coordinates::GAME_OVER_TEXT_X, Coordinates::GAME_OVER_TEXT_Y, Configs::GAME_OVER_TEXT_FONT_SIZE);
    setFontAttributes(textScore, font, "Score = 0", Color::White, Coordinates::SCORE_TEXT_X, Coordinates::SCORE_TEXT_Y, Configs::SCORE_TEXT_FONT_SIZE);
    stringstream ss;
    ss << "High Score : " << highScore;
    setFontAttributes(textHighScore, font, ss.str(), Color::White, Coordinates::HIGH_SCORE_X, Coordinates::HIGH_SCORE_Y, Configs::HIGH_SCORE_TEXT_FONT_SIZE);
    setFontAttributes(textZombiesRemaining, font, "Zombies: 0", Color::White, Coordinates::ZOMBIES_REMAINING_TEXT_X, Coordinates::ZOMBIES_REMAINING_TEXT_Y, Configs::ZOMBIES_REMAINING_TEXT_FONT_SIZE);
    setFontAttributes(textAmmo, font, bulletsInClip+"\\"+bulletsSpare, Color::White, Coordinates::AMMO_TEXT_X, Coordinates::AMMO_TEXT_Y, Configs::AMMO_FONT_SIZE);
    setFontAttributes(textWave, font, "Wave: 0", Color::White, Coordinates::WAVE_X, Coordinates::WAVE_Y, Configs::WAVE_FONT_SIZE);

    ifstream inputFile1(Paths::GAMEDATA_FILE_PATH);
    if (inputFile1.is_open()) {
        inputFile1 >> highScore;
        inputFile1.close();
    }
    
    int numZombies;
    int numZombieAlive;
    ifstream inputFile2(Paths::ZOMBIES_FILE_PATH);
    if (inputFile2.is_open()) {
        inputFile2 >> numZombies;
        inputFile2.close();
    }
    vector<Zombie*> zombies;

    SoundBuffer hitBuffer, pickupBuffer, powerupBuffer, reloadBuffer, reloadFailedBuffer, shootBuffer, splatBuffer;
    Sound hitSound, pickupSound, reloadSound, reloadFailedSound, powerupSound, shootSound, splatSound;
    setSoundAttributes(hitBuffer, hitSound, Paths::HIT_SOUND_PATH);
    setSoundAttributes(pickupBuffer, pickupSound, Paths::PICKUP_SOUND_PATH);
    setSoundAttributes(powerupBuffer, powerupSound, Paths::POWERUP_SOUND_PATH);
    setSoundAttributes(reloadBuffer, reloadSound, Paths::RELOAD_SOUND_PATH);
    setSoundAttributes(reloadFailedBuffer, reloadFailedSound, Paths::RELOAD_FAILED_SOUND_PATH);
    setSoundAttributes(shootBuffer, shootSound, Paths::SHOOT_SOUND_PATH);
    setSoundAttributes(splatBuffer, splatSound, Paths::SPLAT_SOUND_PATH);
 
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Enter && state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Enter && state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING) {
                    if (event.key.code == Keyboard::R) {
                        reloadSound.play();
                        if (bulletsInClip < Configs::CLIP_SIZE) {
                            if (bulletsSpare >= Configs::CLIP_SIZE) {
                                int diff = Configs::CLIP_SIZE - bulletsInClip;
                                bulletsSpare -= diff;
                                bulletsInClip = Configs::CLIP_SIZE;
                            }
                            else if (bulletsSpare > 0) {
                                if (bulletsSpare + bulletsInClip >= Configs::CLIP_SIZE) {
                                    bulletsSpare = bulletsSpare + bulletsInClip - Configs::CLIP_SIZE;
                                    bulletsInClip = Configs::CLIP_SIZE;
                                }
                                else {
                                    bulletsInClip += bulletsSpare;
                                    bulletsSpare = 0;
                                }
                            }
                            else {
                                reloadFailedSound.play();
                            }
                        }
                    }                   
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (state == State::PLAYING) {
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.moveUp();
            }
            else {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.moveDown();
            }
            else {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                player.moveLeft();
            }
            else {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                player.moveRight();
            }
            else {
                player.stopRight();
            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (gameTotalTime.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0) {
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet++;
                    if (currentBullet > Configs::TOTAL_BULLETS - 1) {
                        currentBullet = 0;
                    }
                    lastPressed = gameTotalTime;
                    bulletsInClip--;
                    shootSound.play();
                }
            }
        }
        if (state == State::LEVELING_UP) {
            /*if (event.key.code == Keyboard::Num1) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6) {
                state = State::PLAYING;
            }*/
            state = State::PLAYING;
            if (state == State::PLAYING) {
                arena.width = Configs::ARENA_WIDTH;
                arena.height = Configs::ARENA_HEIGHT;
                arena.top = Configs::ARENA_TOP;
                arena.left = Configs::ARENA_LEFT;
                int tilesize = createBackground(background, arena);
                player.spawn(resolution, arena, Configs::TILE_SIZE);
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);
                if(numZombies == 0)
                    numZombies = Configs::NUM_ZOMBIES;
                zombies.clear();
                zombies = createHorde(numZombies, arena);
                numZombieAlive = numZombies;
                clock.restart();

            }
        }

        if (state == State::PLAYING) {
            //UPDATE
            Time dt = clock.restart();
            gameTotalTime += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
            spriteCrossHair.setPosition(mouseWorldPosition);
            player.update(dtAsSeconds, Mouse::getPosition());
            Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i]->isAlive()) {
                    zombies[i]->update(dt.asSeconds(), playerPosition);
                }
            }
            for (int i = 0; i < Configs::TOTAL_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    bullets[i].update(dtAsSeconds);
                }
            }
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);
            for (int i = 0; i < Configs::TOTAL_BULLETS; i++) {
                for (int j = 0; j < numZombies; j++) {
                    if (bullets[i].isInFlight() && zombies[j]->isAlive()) {
                        if (bullets[i].getPosition().intersects(zombies[j]->getPosition())) {
                            bullets[i].stop();
                            hitSound.play();
                            if (zombies[j]->hit()) {
                                splatSound.play();
                                score += 10;
                                if (highScore < score) {
                                    highScore = score;
                                }
                                numZombieAlive--;
                                if (numZombieAlive == 0) {
                                    state = State::LEVELING_UP;
                                }
                            }
                        }
                    }
                }
            }
            for (int j = 0; j < numZombies; j++) {
                if (zombies[j]->isAlive()) {
                    if (player.getPosition().intersects(zombies[j]->getPosition())) {
                        if (player.hit(gameTotalTime)) {

                        }
                        if (player.getHealth() <= 0) {
                            splatSound.play();
                            state = State::GAME_OVER;
                            ofstream outputFile(Paths::GAMEDATA_FILE_PATH);
                            outputFile << highScore;
                            outputFile.close();
                        }
                    }
                }
            }
            if (ammoPickup.isSpawned()) {
                if (player.getPosition().intersects(ammoPickup.getPosition())) {
                    bulletsSpare+= ammoPickup.gotIt();
                    pickupSound.play();
                }
            }
            if (healthPickup.isSpawned()) {
                if (player.getPosition().intersects(healthPickup.getPosition())) {
                    player.increaseHealthLevel(healthPickup.gotIt());
                    powerupSound.play();
                }
            }
            healthBar.setSize(Vector2f(player.getHealth() * 3, 70));
            sinceLastHUDFrameUpdate++;
            if (sinceLastHUDFrameUpdate > fpsMeasurmentFrameInterval) {
                stringstream ssAmmo, ssScore, ssHighScore, ssWave, ssZombies;
                ssAmmo << bulletsInClip << "/" << bulletsSpare;
                textAmmo.setString(ssAmmo.str());
                ssScore << "Score: "<<score;
                textScore.setString(ssScore.str());
                ssHighScore << "High Score: "<<highScore;
                textHighScore.setString(ssHighScore.str());
                ssWave << "Wave: "<<wave;
                textWave.setString(ssWave.str());
                ssZombies << "Zombies: "<<numZombieAlive;
                textZombiesRemaining.setString(ssZombies.str());
                sinceLastHUDFrameUpdate = 0;
            }
            //DRAW
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            for (int i = 0; i < numZombies; i++) {
                window.draw(zombies[i]->getSprite());
            }
            for (int i = 0; i < Configs::TOTAL_BULLETS; i++) {
                if (bullets[i].isInFlight()) {
                    window.draw(bullets[i].getShape());
                }
            }
            if (healthPickup.isSpawned()) {
                window.draw(healthPickup.getSprite());
            }
            if (ammoPickup.isSpawned()) {
                window.draw(ammoPickup.getSprite());
            }
            window.draw(player.getSprite());
            window.draw(spriteCrossHair);
            window.setView(hudView);
            window.draw(spriteAmmoIcon);
            window.draw(textAmmo);
            window.draw(textScore);
            window.draw(textHighScore);
            window.draw(healthBar);
            window.draw(textZombiesRemaining);
            if (state == State::LEVELING_UP) {
                window.draw(spriteGameOver);
            }
            if (state == State:: PAUSED) {
                window.draw(textPaused);
            }
            if (state == State::GAME_OVER) {
                window.draw(textScore);
                window.draw(textHighScore);
                window.draw(textGameOver);
                window.draw(spriteGameOver);
            }
            window.display();

        }
    }
}

int main()
{
    gamelogic();
    return 0;
}