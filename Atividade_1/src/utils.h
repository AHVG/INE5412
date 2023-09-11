#ifndef _H_UTILS
#define _H_UTILS

#include <string>

#define RESET_COLOR "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BRIGHT_BLACK "\033[1;30m"
#define BRIGHT_RED "\033[1;31m"
#define BRIGHT_GREEN "\033[1;32m"
#define BRIGHT_YELLOW "\033[1;33m"
#define BRIGHT_BLUE "\033[1;34m"
#define BRIGHT_MAGENTA "\033[1;35m"
#define BRIGHT_CYAN "\033[1;36m"
#define BRIGHT_WHITE "\033[1;37m"
#define BLACK_BACKGROUND "\033[1;40m"
#define RED_BACKGROUND "\033[1;41m"
#define GREEN_BACKGROUND "\033[1;42m"
#define YELLOW_BACKGROUND "\033[1;43m"
#define BLUE_BACKGROUND "\033[1;44m"
#define MAGENTA_BACKGROUND "\033[1;45m"
#define CYAN_BACKGROUND "\033[1;46m"
#define WHITE_BACKGROUND "\033[1;47m"
#define WEAK_BLACK_BACKGROUND "\033[1;100m"
#define WEAK_RED_BACKGROUND "\033[1;101m"
#define WEAK_GREEN_BACKGROUND "\033[1;102m"
#define WEAK_YELLOW_BACKGROUND "\033[1;103m"
#define WEAK_BLUE_BACKGROUND "\033[1;104m"
#define WEAK_MAGENTA_BACKGROUND "\033[1;105m"
#define WEAK_CYAN_BACKGROUND "\033[1;106m"
#define WEAK_WHITE_BACKGROUND "\033[1;107m"

void customCout(std::string text, std::string color);
void setColor(std::string color);
void resetColor();

#endif