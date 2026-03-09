/**
 * Winston Shih
 * Satyam Garg
 * CS 4337.004 
 * CS 4337 HW 4 Question 2 Java Enum 
 * Shows the strengths of Java Enums in comparison to C enums.
 */
public class JavaEnumDemo {
    
    // Difference 1: Java enums can be defined as classes with methods and fields.
    enum Day {
        MONDAY("Start of work week", 1),
        TUESDAY("Second day", 2),
        WEDNESDAY("Midweek", 3),
        THURSDAY("Almost Friday", 4),
        FRIDAY("End of work week", 5),
        SATURDAY("Weekend", 6),
        SUNDAY("Weekend", 7);
        
        // Java enums can have fields.
        private final String description;
        private final int dayNumber;
        
        // Java enums can have constructors.
        Day(String description, int dayNumber) {
            this.description = description;
            this.dayNumber = dayNumber;
        }
        
        // Java enums can have methods.
        public String getDescription() {
            return description;
        }
        // Returns number associated with day.
        public int getDayNumber() {
            return dayNumber;
        }
        // Returns if day is on weekend.
        public boolean isWeekend() {
            return this == SATURDAY || this == SUNDAY;
        }
    }
    
    // Difference 2: Java enums are type-safe, which means mixing variables of different data types causes errors.
    enum Color {
        RED, GREEN, BLUE
    }
    
    public static void main(String[] args) {
        System.out.println("=== Java Enum Demonstration ===\n");
        
        // Difference 1: Using enum methods and fields
        System.out.println("Difference 1: Enums with methods and fields");
        Day today = Day.FRIDAY;
        System.out.println("Today: " + today);
        System.out.println("Description: " + today.getDescription());
        System.out.println("Day Number: " + today.getDayNumber());
        System.out.println("Is Weekend? " + today.isWeekend());
        System.out.println();
        
        // Difference 2: Type safety - cannot assign integer or mix enums
        System.out.println("Difference 2: Type Safety");
        Day day = Day.MONDAY;
        Color color = Color.RED;
        // day = color; // Compilation error - type mismatch
        // day = 1; // Compilation error - cannot assign int to enum
        System.out.println("Day: " + day + ", Color: " + color);
        System.out.println("Type safety ensures no mixing of different enum types");
        System.out.println();
        
        // Difference 3: Built-in methods like values().
        System.out.println("Difference 3: Built-in methods");
        System.out.println("All days using values():");
        for (Day d : Day.values()) {
            System.out.println("  " + d + " (ordinal: " + d.ordinal() + ")");
        }
        System.out.println();
        
        //  valueOf outputs value of a day enumeration.
        Day parsed = Day.valueOf("WEDNESDAY");
        System.out.println("Parsed from string: " + parsed);
        System.out.println();
        
        // Switch statement with enums
        System.out.println("Switch statement example:");
        switch (today) {
            case MONDAY:
                System.out.println("Back to work!");
                break;
            case FRIDAY:
                System.out.println("TGIF!");
                break;
            case SATURDAY:
            case SUNDAY:
                System.out.println("Weekend time!");
                break;
            default:
                System.out.println("Regular work day");
        }
    }
}