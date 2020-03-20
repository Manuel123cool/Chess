#   Chess: a simple chess AI
#   Copyright (C) 2020  Manuel Maria Kümpel

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.


files = chessboard.cpp chess_game.cpp computer.cpp main.cpp manu.cpp one_player.cpp play_by_rules.cpp states.cpp two_player.cpp user_input.cpp
sfml = -lsfml-graphics -lsfml-window -lsfml-system
chess: $(files)
	g++ -o chess $(files) $(sfml) -I.
