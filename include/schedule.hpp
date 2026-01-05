#ifndef TEXT_HPP
#define TEXT_HPP

#include <ArduinoJson.h>

class Schedule {
    private:
        String response;
        JsonDocument json;
        DeserializationError error;
        int size;
        char* firstBuffer;
        char* secondBuffer;
        char* bottomBuffer;
        int curr;
        
    public:
        Schedule(String response, int size);
        ~Schedule();
        const char* getFirstBuffer();
        const char* getSecondBuffer();
        const char* getBottomBuffer();
        DeserializationError getError();
        int getLen();

        void Update();
};

#endif
