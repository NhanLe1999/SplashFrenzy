#include "BPSoundManager.h"
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;

void BPSoundManager::init()
{
	preloadSoundEffectAndMusic();
}

void BPSoundManager::playWinEffect()
{
    if (isSoundEffectEnable())
    {
        AudioEngine::play2d("res/BlackPink/sound/win.wav");
    }
}
void BPSoundManager::playLoseEffect()
{
    if (isSoundEffectEnable())
    {
        AudioEngine::play2d("res/sound/game_over.mp3");
    }
}

void BPSoundManager::playClickEffect()
{
	if (isSoundEffectEnable()) 
	{
		AudioEngine::play2d("res/sound/sound_click_1.mp3",false,0.5);
	}
}

void BPSoundManager::chooseCorect()
{
    if (isSoundEffectEnable())
    {
        AudioEngine::play2d("res/sound/coin.mp3",false,0.5);
    }
}

void BPSoundManager::playJump()
{
    if (isSoundEffectEnable())
    {
        AudioEngine::play2d("res/sound/jump.mp3",false,0.5);
    }
}
void BPSoundManager::chooseWrong()
{
    if (isSoundEffectEnable())
    {
        AudioEngine::play2d("res/sound/wrong.wav",false,0.5);
    }
}


static int gameID = -1;

static int menuID = -1;

static bool s_isGameMusic = false;

void BPSoundManager::playMainMenuMusic(bool isGameMusic)
{
	if (!isMusicEffectEnable())
	{
		return;
	}

	s_isGameMusic = isGameMusic;

	AudioEngine::stop(gameID);

	AudioEngine::stop(menuID);

	if (isGameMusic) 
	{
		gameID = AudioEngine::play2d("res/sound/game.mp3", true,0.1);
	}
	else 
	{
		menuID = AudioEngine::play2d("res/sound/bg.mp3", true,0.2);
	}
}

void BPSoundManager::pauseAllBackgroundMusics()
{
	AudioEngine::pause(gameID);

	AudioEngine::pause(menuID);
}

void BPSoundManager::pauseAllSoundEffects()
{
	AudioEngine::pauseAll();
}

void BPSoundManager::resumeAllBackgroundMusics()
{
	playMainMenuMusic(s_isGameMusic);
}

void BPSoundManager::resumeAllSoundEffects()
{
	AudioEngine::resumeAll();
}

void BPSoundManager::stopAllBackgroundMusics()
{
	AudioEngine::stopAll();
}

void BPSoundManager::stopAllSoundEffects()
{
	AudioEngine::stopAll();
}

void BPSoundManager::preloadSoundEffectAndMusic()
{
	AudioEngine::preload("");
}

bool BPSoundManager::isSoundEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
}

bool BPSoundManager::isMusicEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
}
