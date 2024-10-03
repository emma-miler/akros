#include "shell.h"

#include "../../clib.h"
#include "../../efi.h"

void ShellInstance::Start()
{
    _con.ClearScreen();
    while (true) {
        uchar commandBuffer[255];
        memset(commandBuffer, 0, 255);

        uchar individualCharBuf[2];
        memset(commandBuffer, 0, 2);

        int idx = 0;

        Keycode keycode;

        _con.Write(u"> ");

        while (true) {
            int scancode = _con.ReadOne(&keycode);

            uchar buf[8];
            snprintf(buf, 8, u"%d", scancode);
            //_con.Write(buf);
            // continue;

            if (keycode.UnicodeChar == 13) {
                _con.Write(u"\nEXECUTING COMMAND: ");
                _con.Write(commandBuffer);
                _con.Write(u"\n> ");
                memset(commandBuffer, 0, 255);
                idx = 0;
            }
            // SPECIAL
            else if (keycode.UnicodeChar == 0) {
                // BACKSPACE
                if (scancode == 8) {
                    idx--;
                    commandBuffer[idx] = 0;
                    idx = idx < 0 ? 0 : idx;
                    _con.ClearLine();
                    _con.Write(u"> ");
                    _con.Write(commandBuffer);
                }
                else {
                }
            }
            else {
                commandBuffer[idx] = keycode.UnicodeChar;
                idx++;
                individualCharBuf[0] = keycode.UnicodeChar;
                _con.Write(individualCharBuf);
            }
        }
    }
}