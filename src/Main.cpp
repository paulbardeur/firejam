/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Main
*/

#include <string>
#include <iostream>

#include "Firejam.hpp"

static int help(void)
{
    std::cout << HELP_MESSAGE << std::endl;

    return SUCCESS;
}

int main(int ac, char **av)
{
    if (ac ==  1) {
        return firejam();
    }

    return help();
}