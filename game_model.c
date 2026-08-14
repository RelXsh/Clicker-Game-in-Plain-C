#include <stdio.h>

int current_points=0;
int step=1;

FILE* game_data;

void save_data(void)
{
    game_data = fopen("save.txt", "w");

    if (game_data == NULL)
        NULL;
    else
        printf("The file is created Successfully \n");

    fprintf(game_data, "%d\n", current_points);
    fprintf(game_data, "%d\n", step);
    fclose(game_data);
}

void load_data(void)
{
    game_data = fopen("save.txt", "r");

    if (game_data == NULL)
    {
        printf("No saved data exists\n");
        save_data();
    }

    else
    {
        printf("Saved data found! Loading...\n");
        fscanf(game_data, "%d", &current_points);
        fscanf(game_data, "%d", &step);
        fclose(game_data);

        printf("%d\n", current_points);
        printf("%d\n", step);
    }
}

void increase_points(void)
{
    current_points = current_points + step;
}

int try_upgrade_step(int price)
{
    if (current_points >= price) {
        current_points -= price;
        step++;
        return 1;
    }
    return 0;
}

int get_current_points(void)
{
    return current_points;
}

int get_step(void)
{
    return step;
}

int get_upgrade_price(void)
{
    return 5;
}

void initialize_game_logic(void)
{
    load_data();
}
