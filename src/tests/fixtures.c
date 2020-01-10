#define _XOPEN_SOURCE

#include <stdio.h>
#include <check.h>
#include <unistd.h>

#include "librepo/util.h"
#include "fixtures.h"
#include "testsys.h"


/* define the global variable */
struct TestGlobals_s test_globals;

void
test_log_handler_cb(G_GNUC_UNUSED const gchar *log_domain,
                    GLogLevelFlags log_level,
                    const gchar *message,
                    G_GNUC_UNUSED gpointer user_data)
{
    time_t rawtime;
    char buffer[255];
    gchar *level = "";

    switch(log_level) {
        case G_LOG_LEVEL_ERROR:     level = "ERROR"; break;
        case G_LOG_LEVEL_CRITICAL:  level = "CRITICAL"; break;
        case G_LOG_LEVEL_WARNING:   level = "WARNING"; break;
        case G_LOG_LEVEL_MESSAGE:   level = "MESSAGE"; break;
        case G_LOG_LEVEL_INFO:      level = "INFO"; break;
        case G_LOG_LEVEL_DEBUG:     level = "DEBUG"; break;
        default:                    level = "UNKNOWN"; break;
    }

    time(&rawtime);
    strftime(buffer, 254, "%H:%M:%S", localtime(&rawtime));
    g_printerr("%s: %s %s\n", buffer, level, message);
}

void
lr_assert_strv_eq(const gchar * const *strv, ...)
{
    va_list args;
    ck_assert_msg(strv != NULL, "NULL isn't strv");
    va_start (args, strv);
    gchar **strv_p = (gchar **) strv;
    for (; *strv_p; strv_p++) {
        gchar *s = va_arg (args, gchar*);
        ck_assert_msg(s != NULL, "Lengths of lists are not the same");
        ck_assert_str_eq(*strv_p, s);
    }

    // strv list already ended, check if we really expected the end
    ck_assert_msg(va_arg(args, gchar*) == NULL,
                  "Lengths of lists are not the same");

    va_end (args);
}
