#ifndef LOG_H
#define LOG_H

#include "config.h"

#ifdef HAVE_LIBSYSTEMD
#include <systemd/sd-journal.h>
#endif

#ifdef HAVE_LIBSYSTEMD
#define log(level, format, args...) sd_journal_print(level, format, ##args);
#elif HAVE_SYSLOG
#define log(level, format, args...) syslog(level, format, ##args);
#else
#define log(level, format, args...) do {
        printf("<%d>", level);
        printf(format, ##args);
} while(0)
#endif

#endif
