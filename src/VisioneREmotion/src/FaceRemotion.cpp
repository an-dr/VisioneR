// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include <unistd.h>
#include <string>
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions


#include "FaceRemotion.hpp"

FaceRemotion::FaceRemotion(std::string port_name, int baudrate)
{
    m_serial_port = open(port_name.c_str(), O_RDWR);

    // Check for errors
    if (m_serial_port < 0)
    {
        // printf("Error %i from open: %s\n", errno, stderr(errno));
    }

    // Create new termios struct, we call it 'tty' for convention
    // No need for "= {0}" at the end as we'll immediately write the existing
    // config to this struct
    struct termios tty;

    // Read in existing settings, and handle any error
    // NOTE: This is important! POSIX states that the struct passed to tcsetattr()
    // must have been initialized with a call to tcgetattr() overwise behaviour
    // is undefined
    if (tcgetattr(m_serial_port, &tty) != 0)
    {
        // printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)

    tty.c_cflag &= ~CSIZE; // Clear all the size bits, then use one of the statements below
    tty.c_cflag |= CS8;    // 8 bits per byte (most common)

    tty.c_cflag &= ~CRTSCTS;       // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON; // we normally want to disable canonical mode

    tty.c_lflag &= ~ECHO;   // Disable echo
    tty.c_lflag &= ~ECHOE;  // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo

    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 10; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate
    cfsetispeed(&tty, baudrate);
    cfsetospeed(&tty, baudrate);

    // Save tty settings, also checking for error
    if (tcsetattr(m_serial_port, TCSANOW, &tty) != 0)
    {
        // printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

void FaceRemotion::ShowThinking()
{
    write(m_serial_port, "6", 1);
}

void FaceRemotion::ShowBlink(int delay)
{
    write(m_serial_port, "0", 1);
    Delay(delay);
    write(m_serial_port, "1", 1);
}

void FaceRemotion::ShowCalm(int delay)
{
    write(m_serial_port, "0", 1);
    Delay(delay);
}

void FaceRemotion::ShowHappy(int delay)
{
    write(m_serial_port, "2", 1);
    Delay(delay);
}

void FaceRemotion::ShowSad(int delay)
{
    write(m_serial_port, "3", 1);
    Delay(delay);
}

void FaceRemotion::ShowDunno(int delay)
{
    write(m_serial_port, "4", 1);
    Delay(delay);
}

void FaceRemotion::ShowConfused(int delay)
{
    write(m_serial_port, "5", 1);
    Delay(delay);
}

void FaceRemotion::Delay(int ms)
{
    usleep(ms * 1000);
}

FaceRemotion::~FaceRemotion()
{
    close(m_serial_port);
}
