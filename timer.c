#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Function prototypes
void showMenu();
void alarm();
void countdownTimer();
void countupTimer();
void nonStopTimer();
void showTimeForCities();
void displayCityTime(int offset, const char *cityName);
void beep(int times);
int kbhit(void);  // This is the function that detects key press (cross-platform solution)

int main() {
    int choice;

    // Main loop for menu selection
    while(1) {
        showMenu();
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                alarm();
                break;
            case 2:
                countdownTimer();
                break;
            case 3:
                countupTimer();
                break;
            case 4:
                nonStopTimer();
                break;
            case 5:
                showTimeForCities();
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please select between 1 and 6.\n");
        }
    }
    return 0;
}

// Function to display the menu
void showMenu() {
    printf("\n=====================\n");
    printf("     Clock Library    \n");
    printf("=====================\n");
    printf("1) Alarm (Beep 10 times with snooze option)\n");
    printf("2) Countdown Timer\n");
    printf("3) Countup Timer (with time limit)\n");
    printf("4) Non Stop Timer (until you stop it)\n");
    printf("5) Show Time for 3 Cities (Israel, USA, China)\n");
    printf("6) Exit\n");
}

void alarm() {
    int snooze;
    int alarmTime;
    printf("Set alarm time (in seconds): ");
    scanf("%d", &alarmTime);

    int startTime = time(NULL);  // Record the start time
    int elapsedTime = 0;  // Initialize elapsed time

    while(elapsedTime < alarmTime) {
        elapsedTime = time(NULL) - startTime;  // Calculate elapsed time
        printf("\rAlarm Time: %d seconds passed", elapsedTime);  // Show the seconds passed
        fflush(stdout);  // Ensure the output is updated in real-time
        sleep(1);  // Wait for a second before checking again
    }

    beep(10);  // Beep 10 times when the time is up

    printf("\nAlarm finished! Do you want to snooze? (1 = yes, 0 = no): ");
    scanf("%d", &snooze);
    if (snooze == 1) {
        printf("Snoozing for 5 seconds...\n");
        sleep(5);
        beep(10);  // Beep again after snooze
    }
}


// Countdown Timer function: Counts down from the time you specify
void countdownTimer() {
    int seconds;
    printf("Enter countdown time in seconds: ");
    scanf("%d", &seconds);

    while(seconds >= 0) {
        printf("\rCountdown: %02d:%02d:%02d", seconds / 3600, (seconds % 3600) / 60, seconds % 60);
        fflush(stdout);
        sleep(1);
        seconds--;
    }
    printf("\nTime's up!\n");
}

// Countup Timer function: Counts up to a specified time limit
void countupTimer() {
    int limitMinutes;
    printf("Enter count-up time limit in minutes: ");
    scanf("%d", &limitMinutes);

    int seconds = 0;
    int limitSeconds = limitMinutes * 60;

    while (seconds <= limitSeconds) {
        printf("\rCountup: %02d:%02d:%02d", seconds / 3600, (seconds % 3600) / 60, seconds % 60);
        fflush(stdout);
        sleep(1);
        seconds++;
    }
    printf("\nTime's up!\n");
}

// Non-Stop Timer function: Continuously counts up until you stop it
void nonStopTimer() {
    int seconds = 0;
    char stop;
    printf("Press 'q' to stop the timer...\n");

    while(1) {
        printf("\rNon-Stop Timer: %02d:%02d:%02d", seconds / 3600, (seconds % 3600) / 60, seconds % 60);
        fflush(stdout);
        sleep(1);
        seconds++;

        // Check if the user wants to stop the timer
        if (kbhit()) {
            stop = getchar();
            if (stop == 'q' || stop == 'Q') {
                break;
            }
        }
    }
    printf("\nTimer stopped.\n");
}

// Show Time for 3 Cities function: Display time for Israel, USA, China
void showTimeForCities() {
    printf("\nTime for Major Cities:\n");
    displayCityTime(3, "Israel");    // Israel (GMT+3)
    displayCityTime(-5, "USA");      // USA (GMT-5)
    displayCityTime(8, "China");     // China (GMT+8)
}

void displayCityTime(int offset, const char *cityName) {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = gmtime(&t);  // Get UTC time

    // Adjust time for city based on offset
    tm_info->tm_hour += offset;

    if (tm_info->tm_hour >= 24) {
        tm_info->tm_hour -= 24;
    } else if (tm_info->tm_hour < 0) {
        tm_info->tm_hour += 24;
    }

    printf("%s Time: %02d:%02d:%02d\n", cityName, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
}

// Beep function to simulate alarm sound (beeps for the given number of times)
void beep(int times) {
    for (int i = 0; i < times; i++) {
        Beep(600,600);
    }
}

// Function to check if a key has been pressed (cross-platform solution)
int kbhit(void) {
    #ifdef _WIN32
    // For Windows
    return _kbhit();
    #else
    // For Linux/macOS
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
    #endif
}
