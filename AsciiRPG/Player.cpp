#include "Player.h"

#include "GameManager.h"


Player::Player(char c) 
{
	characterOnMap = c;
	x = 2;
	y = 3;
}


Player::~Player()
{
}

void Player::HandleInput()
{
	INPUT_RECORD* inputBuffer;
	DWORD numEventRead = GameManager::instance.input.getInput(&inputBuffer);

	for (int i = 0; i < numEventRead; i++)
	{
		switch (inputBuffer[i].EventType)
		{
		case KEY_EVENT:
			switch (inputBuffer[i].Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_LEFT:
				if (x - 1 >= 0)
					x--;
			break;
			}
		}
	}

}
