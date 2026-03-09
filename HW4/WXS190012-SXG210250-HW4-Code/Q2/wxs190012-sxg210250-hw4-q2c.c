#include <stdio.h>
#include <string.h>
/**
 * Winston Shih (WXS190012)
 * Satyam Garg (SXG210250)
 * CS 4337.004 
 * CS 4337 HW 4 Question 2 C Program for Enum
 * This shows the limitations of C enums compared to Java enums.
 */


// Difference 1: C enums CANNOT have fields, methods, or constructors, so we need to implement with structs and manual functions.
enum Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
// To simulate Java's enum with fields, we need a separate struct to define enum's constants.
typedef struct {
    enum Day day;
    const char* description;
    int dayNumber;
} DayInfo;

// Without constructors, C enums need manual data initialization.
DayInfo dayInfoArray[] = {
    {MONDAY, "Start of work week", 1},
    {TUESDAY, "Second day", 2},
    {WEDNESDAY, "Midweek", 3},
    {THURSDAY, "Almost Friday", 4},
    {FRIDAY, "End of work week", 5},
    {SATURDAY, "Weekend", 6},
    {SUNDAY, "Weekend", 7}
};
// Gets a description of a day enum constant.
const char* getDescription(enum Day day) {
    return dayInfoArray[day].description;
}
// Gets Day Number of a Enum constant.
int getDayNumber(enum Day day) {
    return dayInfoArray[day].dayNumber;
}
// Returns if a day is on weekend or not.
int isWeekend(enum Day day) {
    return (day == SATURDAY || day == SUNDAY);
}
// Returns name of day enum.
const char* getDayName(enum Day day) {
    switch(day) {
        case MONDAY: return "MONDAY";
        case TUESDAY: return "TUESDAY";
        case WEDNESDAY: return "WEDNESDAY";
        case THURSDAY: return "THURSDAY";
        case FRIDAY: return "FRIDAY";
        case SATURDAY: return "SATURDAY";
        case SUNDAY: return "SUNDAY";
        default: return "UNKNOWN";
    }
}
//Returns value of a day enum.
enum Day valueOf(const char* name) {
    if (strcmp(name, "MONDAY") == 0) return MONDAY;
    if (strcmp(name, "TUESDAY") == 0) return TUESDAY;
    if (strcmp(name, "WEDNESDAY") == 0) return WEDNESDAY;
    if (strcmp(name, "THURSDAY") == 0) return THURSDAY;
    if (strcmp(name, "FRIDAY") == 0) return FRIDAY;
    if (strcmp(name, "SATURDAY") == 0) return SATURDAY;
    if (strcmp(name, "SUNDAY") == 0) return SUNDAY;
    return MONDAY; 
}
// Difference 2: C enums are not type-safe
enum Color {
    RED,
    GREEN,
    BLUE
};

const char* getColorName(enum Color color) {
    switch(color) {
        case RED: return "RED";
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        default: return "UNKNOWN";
    }
}
//Main method to demonstrate C enums.
int main() {
    printf("=== C Enum Demonstration ===\n\n");
    
    // Difference 1: Using simulated enum methods and fields
    printf("Difference 1: Enums with methods and fields\n");
    enum Day today = FRIDAY;
    printf("Today: %s\n", getDayName(today));
    printf("Description: %s\n", getDescription(today));
    printf("Day Number: %d\n", getDayNumber(today));
    printf("Is Weekend? %s\n", isWeekend(today) ? "true" : "false");
    printf("NOTE: C requires separate structs and functions to simulate this!\n");
    printf("\n");
    
    // Difference 2: Type safety.
    printf("Difference 2: Type Safety\n");
    enum Day day = MONDAY;
    enum Color color = RED;
    // This works in C, but does not because of lack of type safety.
    day = color; // No compilation error even though both variables are integers.
    printf("Day: %s, Color: %s\n", getDayName(day), getColorName(color));
    // Another example of no type safety.
    day = 1; // Assigbning integer to enum does not cause compilation error.
    printf("Assigned integer 1 to day: %s\n", getDayName(day));
    printf("WARNING: C does NOT have type safety - mixing types is allowed!\n");
    printf("\n");
    // Difference 3: Shows manual implementation of Java enum built in methods.
    printf("Difference 3: Built-in methods\n");
    printf("All days using manual iteration (no values() method):\n");
    // C has no values() method - must iterate manually
    for (enum Day d = MONDAY; d <= SUNDAY; d++) {
        // C has no ordinal() method since enum value is the ordinal.
        printf("  %s (ordinal: %d)\n", getDayName(d), d);
    }
    printf("\n");
    // Manual valueOf() implementation in C.
    enum Day parsed = valueOf("WEDNESDAY");
    printf("Parsed from string: %s\n", getDayName(parsed));
    printf("NOTE: C requires manual string parsing - no built-in valueOf()!\n");
    printf("\n");
    // Switch statement with enums
    printf("Switch statement example:\n");
    switch (today) {
        case MONDAY:
            printf("Back to work!\n");
            break;
        case FRIDAY:
            printf("TGIF!\n");
            break;
        case SATURDAY:
        case SUNDAY:
            printf("Weekend time!\n");
            break;
        default:
            printf("Regular work day\n");
    }
    
    return 0;
}