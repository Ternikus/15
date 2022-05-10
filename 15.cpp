// игра "Пятнашки"
// управление стрелками

#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

const int SIZE = 4; // размер игрового поля
const int MAX_Value = 16; //мксимальное колво ячеек

int game_map[SIZE][SIZE]; // игровая карта
int right_map[SIZE][SIZE]; // правильная итоговая карта

struct coordinate // хранилище координат нулевого элемента
{
    int x;
    int y;
} zero; // объект

void create_right_map() // создаем правильную карту заполненую по порядку
{
    int right_value = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            right_map[i][j] = right_value++;
    }
    right_map[SIZE - 1][SIZE - 1] = 0; // нулевой элемент в нижний правый угол
}

void create_game_map() // рандомно создаем игровую карту
{
    int size_temp = MAX_Value;
    int temporary[16];// временный массив из которого будем брать значения в игровую карту
    for (int i = 0; i < MAX_Value; i++)
        temporary[i]=i;
    int limit = MAX_Value;
    int value;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            //cin >> value;
            value = rand() % limit--;
            game_map[i][j] = temporary[value];
            if (game_map[i][j] == 0) // сохраняем координаты нулевого элемента
            {
                zero.x = j;
                zero.y = i;
            }
            for (int c = value; c < size_temp; ++c)
            {
                temporary[c] = temporary[c + 1];
            }
            --size_temp;
        }
    }
}

void screen() // выводим массив на экран
{
    system("cls");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game_map[i][j] != 0)
                cout << setw(2) << setfill('0') << game_map[i][j] << ' ';
            else
                cout << "** "; // нулевой элемент
        }
        cout << '\n';
    }
}
bool check_map() // сравнение игровой и правильной карты для определения конца игры
{
    if (game_map == right_map)
        return true;
    return false;
}

void up_move() // ход вверх (нулевой элемент вниз)
{
    if (zero.y > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
        zero.y--;
        game_map[zero.y][zero.x] = 0;
    }
}

void down_move() // ход вниз (нулевой элемент вверх)
{
    if (zero.y < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
        zero.y++;
        game_map[zero.y][zero.x] = 0;
    }
}

void right_move() // ход вправо (нулевой элемент влево)
{
    if (zero.x < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
        zero.x++;
        game_map[zero.y][zero.x] = 0;
    }
}

void left_move() // ход влево (нулевой элемент вправо)
{
    if (zero.x > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
        zero.x--;
        game_map[zero.y][zero.x] = 0;
    }


}

void get_direction() // определяем нажатую игроком стрелку
{
    int move = static_cast<int> (_getch()); // UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
    switch (move)
    {
    case 72:
    {
        up_move(); break;
    }
    case 80:
    {
        down_move(); break;
    }
    case 77:
    {
        right_move(); break;
    }
    case 75:
    {
        left_move(); break;
    }
    default:
    {
        get_direction();
    }
    }
}

int main()
{
    srand(static_cast<int>(time(NULL)));

    create_right_map(); // создание игровых карт
    do
    {
        create_game_map();
    } while (check_map());

    do // игровой цикл
    {
        screen();
        get_direction();
    } while (!check_map());

    cout << "\nYou win!\nGame over!\n";
    _getch();
}