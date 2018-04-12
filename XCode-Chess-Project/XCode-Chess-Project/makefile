CC = gcc
OBJS = ChessBoard.o ChessGame.o ChessGameConsoleUtils.o ChessGameGuiUtils.o ChessGameLogic.o ChessGameUtils.o Error.o GamePieces.o GameSettings.o GUIChessWindow.o LineParser.o List.o LoadGameScreen.o main.o MainMenuScreen.o MinimaxAI.o Move.o NewGameMenuScreen.o SDLUtils.o
 
EXEC = chessprog
CCC_COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main 

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

ChessBoard.o : ChessBoard.h GamePieces.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

ChessGame.o : ChessGame.h LoadGameScreen.h ChessGameConsoleUtils.h ChessGameGuiUtils.h
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
 
ChessGameConsoleUtils.o : ChessGameConsoleUtils.h ChessGamesLogic.h ChessGameUtils.h ChessGamesLogic.h Move.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

ChessGameGuiUtils.o : ChessGameGuiUtils.h LoadGameScreen.h ChessGameUtils.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

ChessGameLogic.o : ChessGamesLogic.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

ChessGameUtils.o : ChessGameUtils.h MinimaxAI.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

Error.o : Error.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

GamePieces.o : GamePieces.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

GameSettings.o : GameSettings.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

GUIChessWindow.o : GUIChessWindow.h SDLUtils.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

LineParser.o : LineParser.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

List.o : List.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

LoadGameScreen.o : LoadGameScreen.h SDLUtils.h ChessGame.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

main.o : ChessGame.h MainMenuScreen.h NewGameMenuScreen.h LoadGameScreen.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

MainMenuScreen.o : MainMenuScreen.h SDLUtils.h SDLUtils.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

MinimaxAI.o : MinimaxAI.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

Move.o : Move.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

NewGameMenuScreen.o : NewGameMenuScreen.h SDLUtils.h ChessGame.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SDLUtils.o : SDLUtils.h 
	$(CC) $(CCC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

clean:
	rm -f *.o $(EXEC)
