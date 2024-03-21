// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "App.hpp"
#include "Input/InputFiles.hpp"

int main(int argc, char **argv)
{
    InputFiles input;
    input.LoadFiles("input");
    return App(&input);
}
