import pygame
import numpy as N
l = []
mainGrid = N.zeros((9, 9), dtype="int")
quesGrid = N.zeros((9, 9), dtype="int")
starti = 4
startj = 4
c = 0
colors = [(245,245,245), (169,169,169)]
n = 0
correctMoves = 0
wrongMoves = 0
lasti = 0
lastj = 0
pygame.init()
font = pygame.font.Font('freesansbold.ttf', 32)
def setQuesGrid():
    global mainGrid
    global quesGrid
    global l
    for i in range(9):
        for j in range(9):
            if (i * 9 + j) not in l:
                quesGrid[i,j] = mainGrid[i,j]

def display():
    global l
    global quesGrid
    global starti
    global startj
    global colors
    global n
    global font
    global lasti
    global lastj
    global c
    global wrongMoves
    global correctMoves
    if n:
        lasti = starti
        lastj = startj
        if mainGrid[lasti, lastj] == n:
            quesGrid[lasti, lastj] = n
            correctMoves += 1
        else:
            wrongMoves += 1
    for row in range(9):           # Draw each row of the board.
        c_indx = row % 2           # Alternate starting color
        for col in range(9):
            if row in [0,1,2,6,7,8] and col in [0,1,2,6,7,8]:#--------
                colors[0] = (245,245,245)
            elif row in [3,4,5] and col in [3,4,5]:
                colors[0] = (245,245,245)
            else:
                colors[0] = (216,216,216)
            the_square = (col*60 + 1, row*60 + 1, 59, 59)
            if row == starti and col == startj:
                main_surface.fill((255,0,0), the_square)
                if quesGrid[row, col] != 0:
                    main_surface.fill((255,148,148), the_square)
            else:
                main_surface.fill(colors[c_indx], the_square)
            if quesGrid[row,col] != 0:
                if row == lasti and col == lastj:
                    text = font.render(f'{quesGrid[row,col]}', True, (0,255,0))
                else:
                    text = font.render(f'{quesGrid[row,col]}', True, (0,0,0))
                textRect = text.get_rect()
                textRect.center = (60*col + 31,60*row + 31)
                main_surface.blit(text, textRect)
            '''elif row == lasti and col == lastj:
                text = font.render(f'{n}', True, (0,0,0))
                textRect = text.get_rect()
                textRect.center = (60*col + 30,60*row + 30)
                main_surface.blit(text, textRect)
            elif n:
                text = font.render(f'{n}', True, (255,0,0))
                textRect = text.get_rect()
                textRect.center = (60*col + 30,60*row + 30)
                main_surface.blit(text, textRect)'''
            c_indx = (c_indx + 1) % 2
    if 0 not in quesGrid:
        output_string = "You win"
        text = font.render(output_string, True, (255,0,0))
        main_surface.blit(text, [120, 555])
    pygame.display.flip()

def rowColCheck(k, row, col):
    global mainGrid
    if k in mainGrid[:, col]:
        return False
    if k in mainGrid[row, :]:
        return False
    return True


def blockCheck(k, row, col):
    global mainGrid
    if k in mainGrid[row:row + 3, col:col + 3]:
        return False
    return True


def setBlock(row, col):
    global mainGrid
    for i in range(3):
        for j in range(3):
            while True:
                k = N.random.randint(9) + 1
                if blockCheck(k, row, col):
                    mainGrid[row + i, col + j] = k
                    break


def setDiagonals():
    for i in [0, 3, 6]:
        setBlock(i, i)


def setRest(i, j):
    global mainGrid
    if i == 9 and j == 9:
        return True
    elif j == 9:
        i += 1
        j = 0
    if i < 3:
        if j < 3:
            j = 3
    elif i < 6:
        if j >= 3 and j < 6:
            j = 6
    else:
        if j == 6:
            j = 0
            i += 1
            if i == 9:
                return True
    number = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    N.random.shuffle(number)
    for k in number:
        if rowColCheck(k, i, j) and blockCheck(k, i - i % 3, j - j % 3):
            mainGrid[i][j] = k
            if setRest(i, j + 1):
                return True
            mainGrid[i][j] = 0
    return False



print("At what level do you want to play: ")
print("1 -> Easy")
print("2 -> Medium")
print("3 -> Hard")
n = int(input("Enter the level:  "))
level = 0
if n == 1:
  level = 35
elif n == 2:
  level = 30
else:
  level = 25
for i in range(level):
  k = N.random.randint(81) + 1
  while k in l:
    k = N.random.randint(81) + 1
  l.append(k)

setDiagonals()
setRest(0, 0)
setQuesGrid()
print(mainGrid)
for i in range(9):
  for j in range(9):
    x = i * 9 + j
    if x not in l:
      print(mainGrid[i,j], end = " ")
    else:
      print(". ", end = "")
    if j % 3 == 2:
      print("| ", end = "")
  if i % 3 == 2 and i != 8:
    print()
    print("-----------------------", end = "")
  print()
for i in range(9):
  for j in range(9):
    x = i * 9 + j
    if quesGrid[i,j] != 0:
        print(quesGrid[i,j], end = " ")
    else:
      print(". ", end = "")
    if j % 3 == 2:
      print("| ", end = "")
  if i % 3 == 2 and i != 8:
    print()
    print("-----------------------", end = "")
  print()
#-----------------------------------------------------------

pygame.display.set_caption('Sudoku Game')
main_surface = pygame.display.set_mode((541, 600))
pygame.display.flip()
display()
clock = pygame.time.Clock()
font = pygame.font.Font(None, 25)
frame_count = 0
frame_rate = 60
start_time = 90
temp = 0
while True:
    if 0 in quesGrid:
        n = 0
        event = pygame.event.poll()
        main_surface.fill((0,0,0))
        if event.type == pygame.QUIT:
            break
        elif event.type == pygame.KEYUP:
            if event.key==pygame.K_UP:
                starti -= 1
                if starti < 0:
                    starti = 8
                starti = starti % 9
            elif event.key==pygame.K_LEFT:
                startj -= 1
                if startj < 0:
                    startj = 8
                startj = startj % 9
            elif event.key==pygame.K_DOWN:
                starti += 1
                starti = starti % 9
            elif event.key==pygame.K_RIGHT:
                startj += 1
                startj = startj % 9
        elif event.type == pygame.KEYDOWN:
            if event.key not in [pygame.K_UP, pygame.K_DOWN, pygame.K_RIGHT, pygame.K_LEFT]:
                n = event.key
                n = int(n)
                n = n - 48
        total_seconds = frame_count // frame_rate
        minutes = total_seconds // 60
        seconds = total_seconds % 60
        output_string = f'Time:  {minutes}:{seconds}'
        text = font.render(output_string, True, (255,255,255))
        main_surface.blit(text, [225, 562])
        frame_count += 1
        clock.tick(frame_rate)
        if temp == 0:
            wrongMoves = 0
            correctMoves = 0
            temp += 1
        output_string = f'Wrong Moves: {wrongMoves}'
        text = font.render(output_string, True, (255,0,0))
        main_surface.blit(text, [350, 552])
        output_string = f'Corect Moves: {correctMoves}'
        text = font.render(output_string, True, (0,255,0))
        main_surface.blit(text, [350, 572])
        display()
    else:
        event = pygame.event.poll()
        main_surface.fill((0,0,0))
        if event.type == pygame.QUIT:
            break
pygame.quit()