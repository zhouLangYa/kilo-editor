#include<stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
	char c;

	enableRawMode();

	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
	return 0;
}


