#include "Sound.h"
#include <iostream>

using namespace std;

SoundPlayer *theSoundPlayer;

// Sound volume configuration variables
float MUSIC_VOLUME = 1.0;
float SOUND_EFFECT_VOLUME = 1.0;

// Constructor will reserve the sound channels
SoundPlayer::SoundPlayer() {
	al_reserve_samples(4);
	loadedSong = NULL;
	loadedFX = NULL;
}

// Begin looping a music file
void SoundPlayer::playMusic(string filename) {

	// Stop currently playing music if it exists
	stopMusic();

	// Try to load the music, with error checking
	loadedSong = al_load_sample(filename.c_str());
	if (!loadedSong) { cout << "Error: Unable to load sound file: " << filename << endl; }
	al_play_sample(loadedSong, MUSIC_VOLUME, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &songID);
}

// Stop playing music
void SoundPlayer::stopMusic() {

	// If the song isn't loaded, then it can't be stopped. Otherwise stop it
	if (loadedSong != NULL) { 
		loadedSong = NULL;
		al_stop_sample(&songID);
		al_destroy_sample(loadedSong); 
	}

}

// Play a sound effect once
void SoundPlayer::playEffect(string filename) {
	// Try to load the music, with error checking
	loadedFX = al_load_sample(filename.c_str());
	if (!loadedFX) { cout << "Error: Unable to load sound file: " << filename << endl; }
		al_play_sample(loadedFX, SOUND_EFFECT_VOLUME, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

// Get a pointer to the sound player
SoundPlayer *getSoundPlayer() {
	if (theSoundPlayer == NULL) { theSoundPlayer = new SoundPlayer(); }
	return theSoundPlayer;
}

// Get whether or not music is playing
bool SoundPlayer::musicIsPlaying() { return (loadedSong != NULL); }