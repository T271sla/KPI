import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

class StudentRecord {
    private String lastName;
    private String firstName;
    private String birthDate;
    private String phoneNumber;

    public StudentRecord(String lastName, String firstName, String birthDate, String phoneNumber) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.birthDate = birthDate;
        this.phoneNumber = phoneNumber;
    }

    @Override
    public String toString() {
        return "Last name: " + lastName +
                ", First name: " + firstName +
                ", Birth date: " + birthDate +
                ", Phone number: " + phoneNumber;
    }

    // Getters and setters for the StudentRecord class, if needed
}

class Validator {
    public static boolean isValidFirstName(String firstName) {
        return Pattern.matches("^[A-Za-z]+$", firstName);
    }

    public static boolean isValidLastName(String lastName) {
        return Pattern.matches("^[A-Za-z]+$", lastName);
    }

    public static boolean isValidBirthDate(String birthDate) {
        return Pattern.matches("^\\d{1,2}-\\d{1,2}-\\d{4}$", birthDate);
    }

    public static boolean isValidPhoneNumber(String phoneNumber) {
        return Pattern.matches("^\\d+$", phoneNumber);
    }
}

public class Main {
    public static void main(String[] args) {
        List<StudentRecord> journal = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Enter student's last name:");
            String lastName = scanner.nextLine();
            if (!Validator.isValidLastName(lastName)) {
                System.out.println("Error! Invalid last name.");
                continue;
            }

            System.out.println("Enter student's first name:");
            String firstName = scanner.nextLine();
            if (!Validator.isValidFirstName(firstName)) {
                System.out.println("Error! Invalid first name.");
                continue;
            }

            System.out.println("Enter student's birth date (DD-MM-YYYY format):");
            String birthDate = scanner.nextLine();
            if (!Validator.isValidBirthDate(birthDate)) {
                System.out.println("Error! Invalid birth date.");
                continue;
            }

            System.out.println("Enter student's phone number:");
            String phoneNumber = scanner.nextLine();
            if (!Validator.isValidPhoneNumber(phoneNumber)) {
                System.out.println("Error! Invalid phone number.");
                continue;
            }

            StudentRecord record = new StudentRecord(lastName, firstName, birthDate, phoneNumber);
            journal.add(record);
            System.out.println("Record added to the journal.");

            System.out.println("Do you want to add another record? (Y/N)");
            String response = scanner.nextLine();
            if (!response.equalsIgnoreCase("Y")) {
                break;
            }
        }

        System.out.println("\nJournal records:");
        for (StudentRecord record : journal) {
            System.out.println(record);
        }
    }
}
