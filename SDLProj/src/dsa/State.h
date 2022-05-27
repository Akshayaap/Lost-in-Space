#pragma once
class State
{
private:
	unsigned int gameState;
	unsigned int mouseState;
	unsigned int messageState;
	unsigned int keyBordState;

public:
	State();

	inline unsigned int GetGameState() {
		return gameState;
	}
	inline unsigned int GetMouseState() {
		return mouseState;
	}
	inline unsigned int GetMessageState() {
		return messageState;
	}

	inline void SetGameState(unsigned int state) {
		gameState = state;
	}
	inline void SetMouseState(unsigned int state) {
		mouseState=state;
	}
	inline void SetMessageState(unsigned int state) {
		messageState=state;
	}


public:
	static const unsigned int INVALID = 0;

	static const unsigned int NORMAL = 1;

	static const unsigned int GAME_OVER = 110;
	static const unsigned int GAME_WON = 111;
	
	static const unsigned int NO_MESSAGE = 1110;
	static const unsigned int MESSAGE_HIT_WALL = 1112;
	static const unsigned int MESSAGE_HIT_GATE = 1113;

	static const unsigned int MOUSE_LEFT_DOWN = 1201;
	static const unsigned int MOUSE_LEFT_UP = 1202;
	static const unsigned int MOUSE_LEFT_PRESSED = 1203;

};

