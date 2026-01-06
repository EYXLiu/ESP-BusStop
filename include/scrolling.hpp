#ifndef SCROLLING_HPP
#define SCROLLING_HPP

#include <ArduinoJson.h>

#define MAX_BUFFER 64

class Scrolling {
    private:
        DeserializationError error;
        int size;
        char* firstBuffer;
        char* secondBuffer;
        int curr;
        int len;
        char maxBuffer[MAX_BUFFER];
        bool empty;
        
    public:
        Scrolling(String response, int size);
        ~Scrolling();
        const char* getFirstBuffer();
        const char* getSecondBuffer();
        DeserializationError getError();
        int getLen();

        void Update();
};

#endif
