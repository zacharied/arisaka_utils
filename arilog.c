/* arilog: a simple and fast user-local logging utility. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/file.h>

#define ARILOG_FILE_DEFAULT strcat(getenv("HOME"), "/.arilog")

typedef enum {
    INFO,
    DEBUG,
    WARNING,
    ERROR
} log_level;

char *log_tag(log_level l) {
    switch (l) {
        case INFO:    return "INFO";
        case DEBUG:   return "DEBUG";
        case WARNING: return "WARN";
        case ERROR:   return "ERROR";
        default:      return NULL;
    }
}

int main(int argc, char const *argv[]) {
    log_level level;
    int argi = 1;

    if (argc == 1) {
        exit(1);
    }

    if (argv[argi][0] == '-') {
        switch (argv[argi++][1]) {
            case 'i':
                level = INFO;
                break;
            case 'd':
                level = DEBUG;
                break;
            case 'w':
                level = WARNING;
                break;
            case 'e':
                level = ERROR;
                break;
            default:
                exit(2);
                break;
        }
    } else {
        level = INFO;
    }

    const char *namespace_env = getenv("ARILOG_NS");
    const char *namespace;
    if (namespace_env) {
        namespace = namespace_env;
    } else {
        namespace = argv[argi++];
        if (argc - argi == 0) exit(1);
    }

    time_t t = time(NULL);
    struct tm *time = localtime(&t);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%y-%m-%d %H:%M:%S", time);

    char *log_file = getenv("ARILOG_FILE");
    if (log_file == NULL) log_file = ARILOG_FILE_DEFAULT;

    int fd = open(log_file, O_APPEND);
    flock(fd, LOCK_EX);
    dprintf(fd, "[%s][%5s] <%s> %s\n", timestr, log_tag(level), namespace, argv[argi]);
    close(fd);

    return 0;
}
