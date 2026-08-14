#include <stdio.h>

int current_points=0;
int button_click_gain=1;

FILE* game_data;

void save_data(void)
{
    fopen_s(&game_data, "save.txt","w");

    if (game_data == NULL)
        NULL;
    else
        printf("The file is created Successfully \n");

    fprintf_s(game_data, "%d\n", current_points);
    fprintf_s(game_data, "%d\n", button_click_gain);
    fclose(game_data);
}

void load_data(void)
{
    fopen_s(&game_data, "save.txt","r");

    if (game_data == NULL)
    {
        printf("No saved data exists\n");
        save_data();
    }

    else
    {
        printf("Saved data found! Loading...\n");
        fscanf_s(game_data, "%d", &current_points);
        fscanf_s(game_data, "%d", &button_click_gain);
        fclose(game_data);

        printf_s("%d\n", current_points);
        printf_s("%d\n", button_click_gain);
    }
}

void on_button_click(void)
{
    current_points = current_points + button_click_gain;
    // Invoke some sort of event to update the UI
}

void upgrade_button_click_gain(int price)
{
    button_click_gain = button_click_gain * 2;
    current_points = current_points - price;
}

void initialize_game_logic(void)
{
    load_data();
}
