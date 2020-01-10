#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "testsys.h"
#include "fixtures.h"
#include "test_mirrorlist.h"
#include "librepo/rcodes.h"
#include "librepo/types.h"
#include "librepo/mirrorlist.h"
#include "librepo/util.h"

#define MIRRORLIST_DIR        "mirrorlists"

START_TEST(test_mirrorlist_init)
{
    LrMirrorlist *ml = NULL;

    ml = lr_mirrorlist_init();
    fail_if(ml == NULL);
    lr_mirrorlist_free(ml);
}
END_TEST

START_TEST(test_mirrorlist_01)
{
    int fd;
    gboolean ret;
    char *path;
    GSList *elem = NULL;
    LrMirrorlist *ml = NULL;
    GError *tmp_err = NULL;

    path = lr_pathconcat(test_globals.testdata_dir, MIRRORLIST_DIR,
                         "mirrorlist_01", NULL);
    fd = open(path, O_RDONLY);
    lr_free(path);
    fail_if(fd < 0);
    ml = lr_mirrorlist_init();
    fail_if(ml == NULL);
    ret = lr_mirrorlist_parse_file(ml, fd, &tmp_err);
    close(fd);
    fail_if(!ret);
    fail_if(tmp_err);

    fail_if(g_slist_length(ml->urls) != 2);

    elem = g_slist_nth(ml->urls, 0);
    fail_if(!elem);
    fail_if(g_strcmp0(elem->data, "http://foo.bar/fedora/linux/"));

    elem = g_slist_nth(ml->urls, 1);
    fail_if(!elem);
    fail_if(g_strcmp0(elem->data, "ftp://ftp.bar.foo/Fedora/17/"));
    lr_mirrorlist_free(ml);
}
END_TEST

START_TEST(test_mirrorlist_02)
{
    int fd;
    gboolean ret;
    char *path;
    LrMirrorlist *ml = NULL;
    GError *tmp_err = NULL;

    path = lr_pathconcat(test_globals.testdata_dir, MIRRORLIST_DIR,
                         "mirrorlist_02", NULL);
    fd = open(path, O_RDONLY);
    lr_free(path);
    fail_if(fd < 0);
    ml = lr_mirrorlist_init();
    fail_if(ml == NULL);
    ret = lr_mirrorlist_parse_file(ml, fd, &tmp_err);
    close(fd);
    fail_if(!ret);
    fail_if(tmp_err);
    fail_if(g_slist_length(ml->urls) != 0);
    lr_mirrorlist_free(ml);
}
END_TEST

START_TEST(test_mirrorlist_03)
{
    int fd;
    gboolean ret;
    char *path;
    LrMirrorlist *ml = NULL;
    GError *tmp_err = NULL;

    path = lr_pathconcat(test_globals.testdata_dir, MIRRORLIST_DIR,
                         "mirrorlist_03", NULL);
    fd = open(path, O_RDONLY);
    lr_free(path);
    fail_if(fd < 0);
    ml = lr_mirrorlist_init();
    fail_if(ml == NULL);
    ret = lr_mirrorlist_parse_file(ml, fd, &tmp_err);
    close(fd);
    fail_if(!ret);
    fail_if(tmp_err);
    fail_if(g_slist_length(ml->urls) != 0);
    lr_mirrorlist_free(ml);
}
END_TEST

Suite *
mirrorlist_suite(void)
{
    Suite *s = suite_create("mirrorlist");
    TCase *tc = tcase_create("Main");
    tcase_add_test(tc, test_mirrorlist_init);
    tcase_add_test(tc, test_mirrorlist_01);
    tcase_add_test(tc, test_mirrorlist_02);
    tcase_add_test(tc, test_mirrorlist_03);
    suite_add_tcase(s, tc);
    return s;
}
