#include "CaculateQuickSoundManager.h"
#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include "AudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d::experimental;

USING_NS_CC;

static int gameID = -1;
static int menuID = -1;
static bool s_isGameMusic = false;

void CaculateQuickSoundManager::init()
{
	preloadSoundEffectAndMusic();
}


void CaculateQuickSoundManager::playCoinEffect()
{
	if (isSoundEffectEnable())
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/CaculateQuickcorrect.mp3");
	}
}

void CaculateQuickSoundManager::playClickEffect()
{
	if (isSoundEffectEnable())
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button_click.mp3");
	}
}

void CaculateQuickSoundManager::PlaySoundEndDrag()
{
	if (isSoundEffectEnable()) 
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/end_drag.mp3");
	}
}

void CaculateQuickSoundManager::PlaySoundBeginDrag()
{
	if (isSoundEffectEnable()) 
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/sound_click_drag.mp3");
	}
}

void CaculateQuickSoundManager::playOnGameOver() {
	if (isSoundEffectEnable())
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3");
	}
}

void CaculateQuickSoundManager::playLevlUpEffect() {
    if (isSoundEffectEnable())
    {
        SimpleAudioEngine::getInstance()->playEffect("sound/win.mp3");
    }
}

void CaculateQuickSoundManager::PlayOnSucess() {
    if (isSoundEffectEnable())
    {
        SimpleAudioEngine::getInstance()->playEffect("sound/sucess.mp3");
    }
}



void CaculateQuickSoundManager::playMainMenuMusic(bool isGameMusic)
{
	if (!isMusicEffectEnable())
	{
		return;
	}

	s_isGameMusic = isGameMusic;

	cocos2d::experimental::AudioEngine::stop(gameID);

	cocos2d::experimental::AudioEngine::stop(menuID);

	if (!isGameMusic)
	{
		gameID = cocos2d::experimental::AudioEngine::play2d("sound/sound_bg.mp3", true, 0.8f);
	}
	else
	{
		menuID = cocos2d::experimental::AudioEngine::play2d("sound/sound_game.mp3", true, 0.8f);
	}
}

void CaculateQuickSoundManager::pauseAllBackgroundMusics()
{
	AudioEngine::pause(gameID);

	AudioEngine::pause(menuID);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void CaculateQuickSoundManager::pauseAllSoundEffects()
{
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void CaculateQuickSoundManager::resumeAllBackgroundMusics()
{
	playMainMenuMusic(s_isGameMusic);
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void CaculateQuickSoundManager::resumeAllSoundEffects()
{
	SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void CaculateQuickSoundManager::stopAllBackgroundMusics()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void CaculateQuickSoundManager::stopAllSoundEffects()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void CaculateQuickSoundManager::preloadSoundEffectAndMusic()
{
	//background music
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/CaculateQuicksound_bg.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/CaculateQuicksound_game.mp3");

	//sound effects
	SimpleAudioEngine::getInstance()->preloadEffect("sound/dragon_roar.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/CaculateQuickclick.mp3");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/clicked_wooden.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/breaking_woodend.wav");

	//
	SimpleAudioEngine::getInstance()->preloadEffect("sound/ate_eff.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/clicked_metal.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/showing_eff.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/star.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/coin.wav"); 
	SimpleAudioEngine::getInstance()->preloadEffect("sound/uncap.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/firework_01.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/firework_02.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/confirm.wav");
	
}

bool CaculateQuickSoundManager::isSoundEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
}

bool CaculateQuickSoundManager::isMusicEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
}
