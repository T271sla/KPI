import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a value for N: ");
        int N = scanner.nextInt();
        int maxZeroCount = -1;
        int primeWithMostZeroes = -1;

        for (int i = N - 1; i >= 2; i--) {
            if (isPrime(i)) {
                int zeroCount = countZeroesInBinary(i);
                if (zeroCount > maxZeroCount) {
                    maxZeroCount = zeroCount;
                    primeWithMostZeroes = i;
                }
            }
        }

        if (primeWithMostZeroes != -1) {
            System.out.println("Prime number with the most zeroes in binary form less than " + N + ": " + primeWithMostZeroes);
            System.out.println("Binary representation: " + Integer.toBinaryString(primeWithMostZeroes));
        } else {
            System.out.println("No prime number found less than " + N + ".");
        }
    }

    public static boolean isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;

        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }

    public static int countZeroesInBinary(int num) {
        String binaryString = Integer.toBinaryString(num);
        int count = 0;
        for (int i = 0; i < binaryString.length(); i++) {
            if (binaryString.charAt(i) == '0') {
                count++;
            }
        }
        return count;
    }
}