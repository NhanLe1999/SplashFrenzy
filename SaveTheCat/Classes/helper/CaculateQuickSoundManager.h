#pragma once
#include "CaculateQuickBaseSingleton.h"

#define SOUND_MANAGER CaculateQuickSoundManager::GetInstance()
#define IS_MUSIC_KEY_ON "key_is_music_on"
#define IS_SOUND_KEY_ON "key_is_sound_on"

class CaculateQuickSoundManager : public BaseSingleton<CaculateQuickSoundManager>
{
public:

	 void init();


	 void playCoinEffect();

	 void playLevlUpEffect();
	 void PlayOnSucess();

	 void PlaySoundEndDrag();
	 void PlaySoundBeginDrag();


	 void playClickEffect();

	 void playOnGameOver();

	 void playSoundJump();
    
	void playSondWater();
	 
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
};
