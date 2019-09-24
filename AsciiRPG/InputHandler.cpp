#include "InputHandler.h"

#include "GameManager.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

/* Read console input buffer and return malloc'd INPUT_RECORD array */
DWORD InputHandler::getInput(INPUT_RECORD **eventBuffer)
{
	/* Variable for holding the number of current events, and a point to it */
	DWORD numEvents = 0;


	/* Variable for holding how many events were read */
	DWORD numEventsRead = 0;


	/* Put the number of console input events into numEvents */
	GetNumberOfConsoleInputEvents(GameManager::instance.handleInput, &numEvents);


	if (numEvents) /* if there's an event */
	{
		/* Allocate the correct amount of memory to store the events */
		*eventBuffer = new INPUT_RECORD[numEvents];

		/* Place the stored events into the eventBuffer pointer */
		ReadConsoleInput(GameManager::instance.handleInput, *eventBuffer, numEvents, &numEventsRead);
	}


	/* Return the amount of events successfully read */
	return numEventsRead;
}
