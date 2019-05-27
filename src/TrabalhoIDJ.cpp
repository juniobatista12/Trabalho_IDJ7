#define _CRTDBG_MAP_ALLOC
#include "Game.h"
#include <stdlib.h>
#if defined(_WIN64) && defined(_DEBUG)
#include <crtdbg.h>
#endif
#include "TitleState.h"
#include <time.h>


int main(int argc, char** argv) {
	#if defined(_WIN64) && defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);//Isso aqui serve para checar memory leaks dentro do VSCommunity
	#endif
	srand(time(NULL));
	Game::GetInstance().Push(new TitleState());
	Game::GetInstance().Run();
	return 0;
}