#include <scrolling.hpp>

Scrolling::Scrolling(String response, int size): size(size), curr(0) {
    JsonDocument json;
    error = deserializeJson(json, response);

    firstBuffer = new char[size + 1];
    secondBuffer = new char[size + 1];

    if (json["upcoming"].size() == 0) {
        const char* first = "No Scheduled";
        const char* second = "Departures";
        strcpy(firstBuffer, first);
        strcpy(secondBuffer, second);
        empty = true;
        return;
    }

    // honestly don't really need error checking here since the api is written by us but ig best to have a failsafe
    const char* bus = json["upcoming"][0]["BusName"] | "";
    const char* timeFromNow = json["upcoming"][0]["TimeFromNow"] | "";


    snprintf(firstBuffer, size + 1, "%-*s%*s", size - (int)strlen(timeFromNow), bus, (int)strlen(timeFromNow), timeFromNow);
    
    snprintf(maxBuffer, MAX_BUFFER, "%s to %s | %s     ", 
        json["upcoming"][0]["LineName"] | "", 
        json["upcoming"][0]["Destination"] | "",
        json["upcoming"][0]["ScheduledPlatform"] | ""
    );

    len = strlen(maxBuffer);
    strncpy(secondBuffer, maxBuffer, size);
    secondBuffer[size] = '\0';
    empty = false;
}

Scrolling::~Scrolling() {
    delete[] firstBuffer;
    delete[] secondBuffer;
}

const char* Scrolling::getFirstBuffer() {
    return firstBuffer;
}

const char* Scrolling::getSecondBuffer() {
    return secondBuffer;
}

DeserializationError Scrolling::getError() {
    return error;
}

void Scrolling::Update() {
    if (empty) return;

    if (len - 5 <= size) {
        return;
    }

    for (int i = 0; i < size; i++) {
        secondBuffer[i] = maxBuffer[(curr + i) % len];
    }
    secondBuffer[size] = '\0';

    curr = (curr + 1) % len;
}

