# ----------------------------
# Makefile Options
# ----------------------------

NAME = TTT
ICON = icon.png
DESCRIPTION = "TICTACTOE"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -O3
CXXFLAGS = -Wall -Wextra -O3

# ----------------------------

include $(shell cedev-config --makefile)
