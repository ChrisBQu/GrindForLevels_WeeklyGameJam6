#pragma once
#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

// Class for playing music and sound effects

class SoundPlayer {
public:
	SoundPlayer();
	void playEffect(std::string filename);
	void playMusic(std::string filename);
	bool musicIsPlaying();
	void stopMusic();
private:
	ALLEGRO_SAMPLE_ID songID;
	ALLEGRO_SAMPLE *loadedSong;
	ALLEGRO_SAMPLE *loadedFX;
};

SoundPlayer *getSoundPlayer();

#endif