#include <stdio.h>
#include <uv.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <octane.h>
#include "responders/sds_responder.hpp"

void timer_callback(uv_timer_t* timer);

void on_request(http_connection* connection, http_request** requests, int number_of_requests);

char* current_time;
uv_timer_t timer;

int main(int argc, char *argv[]) {
    current_time = (char *) malloc(sizeof(char)*30;
    
    http_listener* listener = new_http_listener();
    uv_timer_init(listener->loop, &timer);
    uv_timer_start(&timer, timer_callback, 0, 500);

    begin_listening(listener, "0.0.0.0", 8000, false, 40, 128, NULL, NULL, NULL, on_request);

    printf("Listening...\n");
    free(current_time);
}

void on_request(http_connection* connection, http_request** requests, int number_of_requests) {
    write_batch* batch = create_write_batch(number_of_requests);

    for (int i=0; i<number_of_requests; i++) {
        if (requests[i]->path[1] == 'p') {
            create_plaintext_response_sds(batch);
        } else if (requests[i]->path[1] == 'j') {
            create_json_response_sds(batch);
        }
    }
    if (http_connection_is_writable(connection)) {
        // TODO: Use the return values from uv_write()
        int rc = http_connection_write(connection, batch);
    } else {
        // TODO: Handle closing the stream.
    }

    free_http_requests(requests, number_of_requests);
}

void timer_callback(uv_timer_t* timer) {
    // Taken from libreactor implementation
    static const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    static const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    time_t t;
    struct tm tm;
    char* old_time;
    char* new_time;

    old_time = current_time;
    new_time = (char*) malloc(sizeof(char)*30);

    time(&t);
    gmtime_r(&t, &tm);
    strftime(new_time, 30, "---, %d --- %Y %H:%M:%S GMT", &tm);
    memcpy(new_time, days[tm.tm_wday], 3);
    memcpy(new_time + 8, months[tm.tm_mon], 3);

    current_time = new_time;
    free(old_time);
}
