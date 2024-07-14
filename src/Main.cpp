/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Main
*/

#include <string>
#include <iostream>

#include "Menu.hpp"
#include "Firejam.hpp"

static int help(void)
{
    std::cout << HELP_MESSAGE << std::endl;

    return SUCCESS;
}

int main(int ac, char **)
{
    Firejam::Menu menu;

    if (ac == NB_ARGUMENTS) {
        return menu.run();
    }

    return help();
}
