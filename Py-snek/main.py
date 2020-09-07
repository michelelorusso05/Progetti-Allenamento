import pygame
import sys
from random import randint

# Costants
WIDTH = 800
HEIGHT = 600
SQUARE_SIZE = 20
GRID_WIDTH = WIDTH / SQUARE_SIZE
GRID_HEIGHT = HEIGHT / SQUARE_SIZE
TARGET_FRAMERATE = 10

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GRAY = (32, 32, 32)
LIGHT_GRAY = (128, 128, 128)
LIGHTER_GRAY = (192, 192, 192)

# Initialization
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('snek')


class Snake:
    x = round(GRID_WIDTH / 2)
    y = round(GRID_HEIGHT / 2)
    length = 1
    tail_squares_pos = []
    is_alive = True

    axisVertical = 0
    axisHorizontal = 0

    def draw(self, screen_sur):
        # Draw head
        pygame.draw.rect(screen_sur, WHITE, (self.x * SQUARE_SIZE, self.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
        # Draw body
        for pos in self.tail_squares_pos:
            pygame.draw.rect(screen_sur, WHITE, (pos[0] * SQUARE_SIZE, pos[1] * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def update_pos(self, axis):
        if self.length > 1:
            try:
                self.tail_squares_pos = [(self.x, self.y)] + self.tail_squares_pos[:-1]
            except IndexError:
                pass

        self.x += axis[0]
        self.y += axis[1]

        if self.x < 0 or self.x > GRID_WIDTH - 1 or self.y < 0 or self.y > GRID_HEIGHT - 1:
            self.is_alive = False

        for pos in self.tail_squares_pos:
            if (self.x, self.y) == pos:
                self.is_alive = False

    def add_square(self):
        self.length += 1
        self.tail_squares_pos.append((self.x, self.y))

    def relive(self):
        self.x = round(GRID_WIDTH / 2)
        self.y = round(GRID_HEIGHT / 2)
        self.length = 1
        self.tail_squares_pos = []
        self.is_alive = True


class Fruit:
    x = randint(0, round(GRID_WIDTH - 1))
    y = randint(0, round(GRID_HEIGHT - 1))

    def draw(self, screen_sur):
        pygame.draw.rect(screen_sur, RED, (self.x * SQUARE_SIZE, self.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def check_for_snake(self, snake_istance):
        if snake_istance.x == self.x and snake_istance.y == self.y:
            snake_istance.add_square()

            # Check if the new position matches with any part of the body of the snake;
            # If it does, generate a new position
            while True:
                valid_position = True
                self.x = randint(0, round(GRID_WIDTH - 1))
                self.y = randint(0, round(GRID_HEIGHT - 1))

                for pos in snake_istance.tail_squares_pos:
                    if pos == (self.x, self.y):
                        valid_position = False
                if self.x == snake_istance.x and self.y == snake_istance.y:
                    valid_position = False
                if valid_position:
                    break


def clear_screen():
    screen.fill(BLACK)


clock = pygame.time.Clock()
snake = Snake()
fruit = Fruit()


def main():
    input_tuple = (1, 0)
    score_font = pygame.font.Font('bumpitup.ttf', 144)
    retry_font = pygame.font.Font('bumpitup.ttf', 24)
    retry = retry_font.render(f'ded, press r to retry', True, LIGHT_GRAY)
    retry_rect = retry.get_rect()
    retry_rect.center = (WIDTH // 2, HEIGHT - HEIGHT // 6)
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            keys = pygame.key.get_pressed()

            if (keys[pygame.K_w] or keys[pygame.K_UP]) and input_tuple[1] != 1:
                input_tuple = (0, -1)
            if (keys[pygame.K_s] or keys[pygame.K_DOWN]) and input_tuple[1] != -1:
                input_tuple = (0, 1)
            if (keys[pygame.K_a] or keys[pygame.K_LEFT]) and input_tuple[0] != 1:
                input_tuple = (-1, 0)
            if (keys[pygame.K_d] or keys[pygame.K_RIGHT]) and input_tuple[0] != -1:
                input_tuple = (1, 0)
            if keys[pygame.K_ESCAPE]:
                pygame.quit()
                sys.exit()
            if keys[pygame.K_r] and not snake.is_alive:
                snake.relive()
                input_tuple = (1, 0)

        speed_multiplier = 5 * ((snake.length - 1) // 10)
        # haha yes speed go brrrrrr
        clock.tick(TARGET_FRAMERATE + speed_multiplier)
        if snake.is_alive:
            snake.update_pos(input_tuple)

        fruit.check_for_snake(snake)
        text = score_font.render(f'{snake.length - 1}', True, GRAY)
        text_rect = text.get_rect()
        text_rect.center = (WIDTH // 2, HEIGHT // 2)

        clear_screen()
        screen.blit(text, text_rect)
        snake.draw(screen)
        fruit.draw(screen)

        if not snake.is_alive:
            screen.blit(retry, retry_rect)

        pygame.display.flip()


def menu():
    title_font = pygame.font.Font('bumpitup.ttf', 96)
    options_font = pygame.font.Font('bumpitup.ttf', 54)
    help_font = pygame.font.Font('bumpitup.ttf', 14)

    title = title_font.render(f'snek', True, WHITE)
    title_rect = title.get_rect()
    title_rect.center = (WIDTH // 2, HEIGHT // 6)

    play = options_font.render(f'Play', True, LIGHT_GRAY)
    play_rect = play.get_rect()
    play_rect.center = (WIDTH // 2, HEIGHT // 2)

    quit_opt = options_font.render(f'Quit', True, LIGHT_GRAY)
    quit_rect = quit_opt.get_rect()
    quit_rect.center = (WIDTH // 2, HEIGHT // 2 + HEIGHT // 6)

    help_txt = help_font.render("WASD or arrows to move, ESC to quit", True, LIGHT_GRAY)
    help_rect = help_txt.get_rect()
    help_rect.center = (240, HEIGHT - 15)

    author_txt = help_font.render("Created by Michele", True, LIGHT_GRAY)
    author_rect = author_txt.get_rect()
    author_rect.center = (WIDTH - 135, HEIGHT - 15)

    play_color = LIGHT_GRAY
    quit_color = LIGHT_GRAY

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if play_rect.collidepoint(pygame.mouse.get_pos()):
                play_color = LIGHTER_GRAY
                if pygame.mouse.get_pressed()[0]:
                    main()
            else:
                play_color = LIGHT_GRAY

            if quit_rect.collidepoint(pygame.mouse.get_pos()):
                quit_color = LIGHTER_GRAY
                if pygame.mouse.get_pressed()[0]:
                    pygame.quit()
                    sys.exit()
            else:
                quit_color = LIGHT_GRAY

        clock.tick(60)

        play = options_font.render(f'Play', True, play_color)
        play_rect = play.get_rect()
        play_rect.center = (WIDTH // 2, HEIGHT // 2)

        quit_opt = options_font.render(f'Quit', True, quit_color)
        quit_rect = quit_opt.get_rect()
        quit_rect.center = (WIDTH // 2, HEIGHT // 2 + HEIGHT // 6)

        clear_screen()
        screen.blit(title, title_rect)
        screen.blit(play, play_rect)
        screen.blit(quit_opt, quit_rect)
        screen.blit(help_txt, help_rect)
        screen.blit(author_txt, author_rect)

        pygame.display.flip()


if __name__ == "__main__":
    menu()
