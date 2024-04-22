#pragma once
#include "BaseSingleton.h"

#define SOUND_MANAGER BPSoundManager::GetInstance()

#define IS_MUSIC_KEY_ON "key_is_music_on"

#define IS_SOUND_KEY_ON "key_is_sound_on"

class BPSoundManager : public BaseSingleton<BPSoundManager>
{
public:

	 void init();


     void playCoinEffect();
     void playHealingEffect();
     void playDieEffect();
     void playBulletColiEffect();
     void playExplose();
     void chooseCorect();
     void chooseWrong();
     void playFlipCard();
	 void playChangeCard();
	 void playJump();

     void playLoseEffect();
	 
	 void playWinEffect();

	 void playClickEffect();

	 void playCollisionEffect();
    
    void playTeleEffect();
    
	 void playMainMenuMusic(bool isGameMusic = false);

	 void pauseAllBackgroundMusics();

	 void pauseAllSoundEffects();

	 void resumeAllBackgroundMusics();

	 void resumeAllSoundEffects();

	 void stopAllBackgroundMusics();

	 void stopAllSoundEffects();

	 void preloadSoundEffectAndMusic();

	 bool isSoundEffectEnable();

	 bool isMusicEffectEnable();

private:

};
