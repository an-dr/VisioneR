// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <string>
#include <vector>

class FileScanner
{
public:
    FileScanner(const std::string &path);

    // Get all files in the directory by pattern
    std::vector<std::string> GetFiles(const std::string &pattern);
    
private:
    std::string m_path;
};
