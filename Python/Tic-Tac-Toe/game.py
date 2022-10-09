import sys
from typing import Optional

import pygame
from pygame.locals import MOUSEBUTTONDOWN, QUIT

BOARD_SIZE = 4
WINDOW_WIDTH = 600
WINDOW_HEIGHT = 600
MESSAGE_RECT_DIMENSIONS = (0, WINDOW_HEIGHT, WINDOW_HEIGHT + 100, 100)
MESSAGE_RECT_CENTER = WINDOW_HEIGHT + 50

HEIGHT_PER_SQUARE = WINDOW_HEIGHT // BOARD_SIZE
WIDTH_PER_SQUARE = WINDOW_WIDTH // BOARD_SIZE

WINDOW_HEIGHT_OFFSET = 100
XO_OFFSET = 30

ROWS = range(BOARD_SIZE)
COLS = range(BOARD_SIZE)

WHITE_COLOR = (255, 255, 255)
BLACK_COLOR = (0, 0, 0)

BACKGROUND_COLOR = WHITE_COLOR
LINE_COLOR = BLACK_COLOR
FONT_COLOR = WHITE_COLOR
MESSAGE_RECT_COLOR = BLACK_COLOR

X_CHAR = 'x'
O_CHAR = 'o'
DRAW_CHAR = '_'
XO_CHARS = [X_CHAR, O_CHAR]

X_IMAGE_PATH = "res/x.png"
O_IMAGE_PATH = "res/o.png"
XO_IMAGE_SIZE = 80
LINE_WIDTH = 8

board = [([None] * BOARD_SIZE) for _ in range(BOARD_SIZE)]
GAME_TITLE = "cool tic-tac-toe game"

FPS = 30
FONT_SIZE = 30

# global vars
turn = X_CHAR
winner = None
x_image = None
o_image = None
screen = None


def reset_board() -> None:
    global board
    board = [([None] * BOARD_SIZE) for _ in range(BOARD_SIZE)]


def draw_empty_game() -> None:
    pygame.display.update()
    screen.fill(BACKGROUND_COLOR)

    # vertical lines
    for col in range(1, BOARD_SIZE):
        pygame.draw.line(screen, LINE_COLOR, (WIDTH_PER_SQUARE * col, 0), (WIDTH_PER_SQUARE * col, WINDOW_HEIGHT),
                         LINE_WIDTH)

    # horizontal lines
    for row in range(1, BOARD_SIZE):
        pygame.draw.line(screen, LINE_COLOR, (0, HEIGHT_PER_SQUARE * row), (WINDOW_WIDTH, HEIGHT_PER_SQUARE * row),
                         LINE_WIDTH)

    draw_status()


def draw_status() -> None:
    global winner

    if winner is None:
        message = turn.upper() + "'s turn"
    elif winner in XO_CHARS:
        message = winner.upper() + " is da winner"
    elif winner in DRAW_CHAR:
        message = "it's a draw :X"
    else:
        assert False, f"illegal winner character: {winner}"

    font = pygame.font.Font(None, FONT_SIZE)
    text = font.render(message, True, FONT_COLOR)
    screen.fill(MESSAGE_RECT_COLOR, MESSAGE_RECT_DIMENSIONS)
    text_rect = text.get_rect(center=(WINDOW_WIDTH // 2, MESSAGE_RECT_CENTER))
    screen.blit(text, text_rect)
    pygame.display.update()


def check_win() -> Optional[str]:
    for col in COLS:
        if all((board[row][col] == X_CHAR for row in ROWS)):
            return X_CHAR

        if all((board[row][col] == O_CHAR for row in ROWS)):
            return O_CHAR

    for row in ROWS:
        if all((board[row][col] == X_CHAR for col in COLS)):
            return X_CHAR

        if all((board[row][col] == O_CHAR for col in COLS)):
            return O_CHAR

    if all((board[diag][diag] == X_CHAR for diag in ROWS)):
        return X_CHAR

    if all((board[diag][diag] == O_CHAR for diag in COLS)):
        return O_CHAR

    if all((board[diag][BOARD_SIZE - diag - 1] == X_CHAR for diag in ROWS)):
        return X_CHAR

    if all((board[diag][BOARD_SIZE - diag - 1] == O_CHAR for diag in COLS)):
        return O_CHAR

    if all(board[row][col] in XO_CHARS for row in ROWS for col in COLS):
        return DRAW_CHAR

    # game not over
    return None


def draw_turn_image(row: int, col: int) -> None:
    global board, turn

    posx = WIDTH_PER_SQUARE * row + XO_OFFSET
    posy = HEIGHT_PER_SQUARE * col + XO_OFFSET
    board[row][col] = turn

    if turn == X_CHAR:
        screen.blit(x_image, (posy, posx))
        turn = O_CHAR
    else:
        screen.blit(o_image, (posy, posx))
        turn = X_CHAR

    pygame.display.update()


def user_click() -> None:
    global board, winner

    x, y = pygame.mouse.get_pos()
    print(f"{x},{y}")

    row = y // HEIGHT_PER_SQUARE
    col = x // WIDTH_PER_SQUARE
    print(f"rowcol={row},{col}")

    if (row >= BOARD_SIZE) or (col >= BOARD_SIZE):
        return

    if board[row][col] is None:
        global turn

        draw_turn_image(row, col)
        winner = check_win()


def reset_game() -> None:
    global board, winner, turn
    turn = X_CHAR
    draw_empty_game()
    winner = None
    reset_board()


def main() -> None:
    global x_image, o_image, screen

    pygame.init()
    clock = pygame.time.Clock()
    pygame.display.set_caption(GAME_TITLE)
    x_image = pygame.transform.scale(pygame.image.load(X_IMAGE_PATH), (XO_IMAGE_SIZE, XO_IMAGE_SIZE))
    o_image = pygame.transform.scale(pygame.image.load(O_IMAGE_PATH), (XO_IMAGE_SIZE, XO_IMAGE_SIZE))
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT + WINDOW_HEIGHT_OFFSET), 0, 32)

    draw_empty_game()
    while True:
        for event in pygame.event.get():

            if event.type == QUIT:
                pygame.quit()
                sys.exit()

            elif event.type == MOUSEBUTTONDOWN:
                print("oi")
                user_click()

                if winner:
                    reset_game()

        pygame.display.update()
        clock.tick(FPS)


if __name__ == "__main__":
    main()
