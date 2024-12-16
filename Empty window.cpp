// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>

//a c++ application that creates an empty window

// Function prototype
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    //this is to check if i have a working API using messagebox that displays a message on the screen with the text i pass into it
    //MessageBox(NULL, L"Hello, this is Bubbles.",L"Welcome to My first GUI", MB_OK);
    /* Explanation of the arguments inside message box
    1. First argument is the window handler of the parent window but since the message box has no parent window i will pass null into it
    if there was a parent window, i would put it as the first argument
    2. Second argument is a text in form of lpcstr which is array of characters. i will pass a string there
    3. Third argument is the caption of the message box
    4. Last argument is the type of message box.

    reason for using wide-character string
         Windows provides two versions of most API functions, including MessageBox:
          MessageBoxA: ANSI version, which works with narrow-character strings (const char*).
          MessageBoxW: Unicode version, which works with wide-character strings (const wchar_t*).
          The MessageBox macro automatically maps to either MessageBoxA or MessageBoxW depending on the project's character set setting.
          A wide-character string is prefixed with L
          To satisfy the LPCWSTR parameter, you must provide wide-character strings
    */

    //create a window class that holds the data for the window and register the window class so that we can create multiple windows from that class
    // Create a window class
    WNDCLASSW wc = { 0 };

    /*
    1.type edge brudge
    defines the background of the window and any argument we include we need to C Cast that to the type and you can also supply some color
    and the API defines some color constants
    2.define edge cursor
    without this cursor the window will not have any cursor and the cursor will not be displayed inside the window
    the function loadcursor is used to load some cursor into the application
    */

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;


    //after successfully creating the class you need to register it
    //introduction to if statement to check if registration of class was successful
    // Register the class
    if (!RegisterClassW(&wc))
        return -1;


    //if registration was successful then we can create the window from our class
    // Create a window
    CreateWindowW(L"myWindowClass", L"My window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 500, NULL, NULL, hInst, NULL);

    // Message loop
    MSG msg = { 0 };


    while (GetMessage(&msg, NULL, 0, 0))
    {

        //this function returns a message into a structure
        //this loop is used to ranslate and dispatch the message for further processing
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure function
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

    /*
    Explaination of arguments
    1.Handler by which the message has been sent. basically defines the window
    2.the unsigned integer it is the message that has been sent
    */

    //introduction to switch statement
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//makes the get message function to return false
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);//this function takes care of the rest of the messages
    }
    return 0;
}
