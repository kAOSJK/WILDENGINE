#include "lib.h"

#define DRAW_HEIGHT (10)
#define DRAW_WIDTH (50)

int display_menu(int y_max, int x_max, char **language_ptr, char *buffer)
{
    char *language = *language_ptr;
    char *menu_key = NULL;
    /* WINDOWS VARs */
    WINDOW *menuwin;
    WINDOW *drawin;
    int height = 13;
    int width = 24;
    /* STORY LANGUAGES DATA VARs */
    char **languages_code = NULL;
    char **languages = NULL;
    char *menu_language = NULL;
    char *code = NULL;
    unsigned int languages_length = 0;
    unsigned int languages_code_length = 0;
    unsigned int index = 0;
    /* DRAWINGS VARs */
    char *draw_0 = NULL;
    int placement = 0;
    int drawwidth = 0;
    int drawheight = 0;
    int disable_drawing = 0;
    /* DATA VARs */
    char **choices;
    int options_length;
    int choice;
    int i;
    int highlight = 0;

    /* GET LANGUAGE MIN LENGTH, MALLOC IT, AND GET IT */
    languages_code_length = get_json_options_length("languages_code", buffer);
    languages_code = malloc(sizeof(char *) * languages_code_length);
    get_json_array_data(languages_code, "languages_code", buffer);

    /* GET LANGUAGE LENGTH, MALLOC IT, AND GET IT */
    languages_length = get_json_options_length("languages", buffer);
    languages = malloc(sizeof(char *) * languages_length);
    get_json_array_data(languages, "languages", buffer);

    /* GET THE RIGHT INDEX */
    for (i = 0; i < languages_length; i++)
    {
        if (strcmp(languages[i], language) == 0)
        {
            index = i;
            break;
        }
    }

    /* GET RIGHT STORY LANGUAGE */
    code = strdup(languages_code[index]);

    menu_language = strdup("menu");
    if (strcmp(code, "") != 0)
    {
        menu_language = realloc(menu_language, sizeof(char) * strlen(menu_language) + strlen(code) + 1 + 1);
        strcat(menu_language, "_");
        strcat(menu_language, code);
    }

    /* GET MENU LENGTH DATA */
    menu_key = strdup(menu_language);
    options_length = get_json_options_length(menu_key, buffer);

    if (options_length == 0)
    {
        /* MESSAGE OF BAD CHOOSED LANGUAGE */
        clear();
        printw("\nTranslation of the choosen language is not finished, switching to the default language\n\nYou can change at any moment the default language in the data.json file");
        refresh();
        getchar();

        /* FREE LANGUAGE */
        free(menu_language);
        menu_language = NULL;

        free(menu_key);
        menu_key = NULL;

        /* LOAD DEFAULT LANGUAGE */
        menu_language = strdup("menu");
        if (strcmp(languages_code[0], "") != 0)
        {
            menu_language = realloc(menu_language, sizeof(char) * strlen(menu_language) + strlen(languages_code[0]) + 1 + 1);
            strcat(menu_language, "_");
            strcat(menu_language, languages_code[0]);
        }

        /* GET MENU LENGTH DATA */
        menu_key = strdup(menu_language);
        options_length = get_json_options_length(menu_key, buffer);

        if (options_length == 0)
        {
            clear();
            printw("\nTranslation of the choosen default language is not finished, switching to static default language");
            refresh();
            getchar();

            /* GET MENU LENGTH DATA */
            menu_key = strdup("menu");
            options_length = get_json_options_length(menu_key, buffer);
        }

        clear();
        refresh();
    }

    /* GET USER WANTED POSITION */
    placement = get_json_data_int("menu_drawing_position", buffer);

    /* OPEN DRAWINGS FILES */
    if (placement != 0) /* if the user chooses a position for his drawing */
    {
        draw_0 = open_file(MENU_DRAWING_DATA_PATH, "r");

        if (draw_0 == NULL) /* if he has a drawing */
        {
            fprintf(stderr, "error: data/menu_drawing is null but user set a position\n");
            disable_drawing = 1;
        }
    }
    else
        disable_drawing = 1;

    /* CREATE DRAWINGS WINDOWS */
    if (disable_drawing == 0) /* if everything is ok for displaying user's drawing at desired position */
    {
        /* GET DRAWING SIZE */
        drawwidth = get_draw_width(draw_0);
        drawheight = get_draw_height(draw_0);

        if (placement == 1)
            drawin = newwin(drawheight, drawwidth, 2, x_max / 2 - (drawwidth / 2));
        else if (placement == 2)
            drawin = newwin(drawheight, drawwidth, y_max / 2 - (drawheight / 2), x_max - (drawwidth + drawwidth / 8));
        else if (placement == 3)
            drawin = newwin(drawheight, drawwidth, y_max - drawheight - 2, x_max / 2 - (drawwidth / 2));
        else if (placement == 4)
            drawin = newwin(drawheight, drawwidth, y_max / 2 - (drawheight / 2), drawwidth / 6);
        wrefresh(drawin);

        wprintw(drawin, draw_0);
        wrefresh(drawin);
    }

    /* CREATE MENU WINDOW */
    getmaxyx(stdscr, y_max, x_max);
    menuwin = create_newwin(height, width, y_max / 2 - (height / 2), x_max / 2 - (width / 2));

    /* ACTIVATE ARROW KEYS */
    keypad(menuwin, true);

    /* GET MENU DATA */
    choices = malloc(sizeof(char *) * options_length);
    get_json_array_data(choices, menu_key, buffer);

    while (1)
    {
        for (i = 0; i < options_length; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, (i * 2) + 1 + 1, (width / 2) - (strlen(choices[i]) / 2), "%s", choices[i]);
            wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_DOWN:
            highlight == options_length - 1 ? highlight = 0 : highlight++;
            break;
        case KEY_UP:
            highlight == 0 ? highlight = options_length - 1 : highlight--;
            break;
        default:
            break;
        }

        if (choice == 10)
            break;
    }

    /* FREE LANGUAGE MENU VARs */
    for (i = 0; i < languages_code_length; i++)
    {
        free(languages_code[i]);
        languages_code[i] = NULL;
    }

    free(languages_code);
    languages_code = NULL;

    for (i = 0; i < languages_length; i++)
    {
        free(languages[i]);
        languages[i] = NULL;
    }

    free(languages);
    languages = NULL;

    free(code);
    code = NULL;

    free(menu_language);
    menu_language = NULL;

    /* OTHERS FREE */
    for (i = 0; i < options_length; i++)
    {
        free(choices[i]);
        choices[i] = NULL;
    }

    free(choices);
    choices = NULL;

    free(menu_key);
    menu_key = NULL;

    free(draw_0);
    draw_0 = NULL;

    if (disable_drawing == 0)
        destroy_win(drawin);

    destroy_win(menuwin);

    return highlight;
}

char *display_languages(int y_max, int x_max, char *buffer)
{
    /* WINDOWS VARs */
    WINDOW *menuwin;
    WINDOW *drawin;
    int height = 13;
    int width = 24;
    /* DRAWINGS VARs */
    char *draw_0 = NULL;
    char *draw_1 = NULL;
    int placement = 0;
    int drawwidth = 0;
    int drawheight = 0;
    int disable_drawing = 0;
    /* DATA VARs */
    char **choices = NULL;
    char *answer = NULL;
    int options_length;
    int choice;
    int i;
    int highlight = 0;

    /* GET USER WANTED POSITION */
    placement = get_json_data_int("menu_drawing_position", buffer);

    /* OPEN DRAWINGS FILES */
    if (placement != 0) /* if the user chooses a position for his drawing */
    {
        draw_0 = open_file(MENU_DRAWING_DATA_PATH, "r");

        if (draw_0 == NULL) /* if he has a drawing */
        {
            fprintf(stderr, "error: data/menu_drawing is null but user set a position\n");
            disable_drawing = 1;
        }
    }
    else
        disable_drawing = 1;

    /* CREATE DRAWINGS WINDOWS */
    if (disable_drawing == 0) /* if everything is ok for displaying user's drawing at desired position */
    {
        /* GET DRAWING SIZE */
        drawwidth = get_draw_width(draw_0);
        drawheight = get_draw_height(draw_0);

        if (placement == 1)
            drawin = newwin(drawheight, drawwidth, 2, x_max / 2 - (drawwidth / 2));
        else if (placement == 2)
            drawin = newwin(drawheight, drawwidth, y_max / 2 - (drawheight / 2), x_max - (drawwidth + drawwidth / 8));
        else if (placement == 3)
            drawin = newwin(drawheight, drawwidth, y_max - drawheight - 2, x_max / 2 - (drawwidth / 2));
        else if (placement == 4)
            drawin = newwin(drawheight, drawwidth, y_max / 2 - (drawheight / 2), drawwidth / 6);
        wrefresh(drawin);

        wprintw(drawin, draw_0);
        wrefresh(drawin);
    }

    /* CREATE MENU WINDOW */
    getmaxyx(stdscr, y_max, x_max);
    menuwin = create_newwin(height, width, y_max / 2 - (height / 2), x_max / 2 - (width / 2));

    /* ACTIVATE ARROW KEYS */
    keypad(menuwin, true);

    options_length = get_json_options_length("languages", buffer);
    choices = malloc(sizeof(char *) * options_length);

    /* GET JSON FILE DATA */
    get_json_array_data(choices, "languages", buffer);

    while (1)
    {
        for (i = 0; i < options_length; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, (i * 2) + 1 + 1, (width / 2) - (strlen(choices[i]) / 2), "%s", choices[i]);
            wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_DOWN:
            highlight == options_length - 1 ? highlight = 0 : highlight++;
            break;
        case KEY_UP:
            highlight == 0 ? highlight = options_length - 1 : highlight--;
            break;
        default:
            break;
        }

        if (choice == 10)
            break;
    }

    answer = strdup(choices[highlight]);

    for (i = 0; i < options_length; i++)
    {
        free(choices[i]);
        choices[i] = NULL;
    }

    free(choices);
    choices = NULL;

    free(draw_0);
    draw_0 = NULL;

    free(draw_1);
    draw_1 = NULL;

    if (disable_drawing == 0)
        destroy_win(drawin);

    destroy_win(menuwin);

    return answer;
}

int get_draw_width(char *draw)
{
    unsigned int counter = 0;
    unsigned int width = 0;
    unsigned int i;

    for (i = 0; draw[i]; i++)
    {
        if (draw[i] == '\n')
        {
            if (counter > width)
                width = counter;
            counter = 0;
        }
        else
            counter++;
    }

    return width + 1;
}

int get_draw_height(char *draw)
{
    unsigned int height = 0;
    unsigned int i;

    for (i = 0; draw[i]; i++)
    {
        if (draw[i] == '\n')

            height++;
    }

    return height + 1;
}
