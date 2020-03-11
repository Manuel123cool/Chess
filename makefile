files = chessboard.cpp chess_game.cpp computer.cpp main.cpp manu.cpp one_player.cpp play_by_rules.cpp states.cpp two_player.cpp user_input.cpp
sfml = -lsfml-graphics -lsfml-window -lsfml-system
chess: $(files)
	g++ -o chess $(files) $(sfml) -I.
