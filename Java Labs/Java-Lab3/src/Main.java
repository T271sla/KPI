import java.util.*;
import java.util.stream.Collectors;
import java.util.Scanner;

// Модель
class Book {
    private String title;
    private String author;
    private String publisher;
    private int year;
    private int pages;
    private double price;

    public Book(String title, String author, String publisher, int year, int pages, double price) {
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        this.year = year;
        this.pages = pages;
        this.price = price;
    }

    // Геттери і сеттери
    public String getTitle() {
        return title;
    }

    public String getAuthor() {
        return author;
    }

    public String getPublisher() {
        return publisher;
    }

    public int getYear() {
        return year;
    }

    public int getPages() {
        return pages;
    }

    public double getPrice() {
        return price;
    }
}

// Контролер
class BookController {
    private List<Book> bookList;

    public BookController(List<Book> bookList) {
        this.bookList = bookList;
    }

    public List<Book> getBooksByAuthor(String author) {
        return bookList.stream()
                .filter(book -> book.getAuthor().equals(author))
                .collect(Collectors.toList());
    }

    public List<Book> getBooksByPublisher(String publisher) {
        return bookList.stream()
                .filter(book -> book.getPublisher().equals(publisher))
                .collect(Collectors.toList());
    }

    public List<Book> getBooksPublishedAfterYear(int year) {
        return bookList.stream()
                .filter(book -> book.getYear() > year)
                .collect(Collectors.toList());
    }

    public void sortBooksByPublisher() {
        bookList.sort(Comparator.comparing(Book::getPublisher));
    }
}

// Вид
class BookView {
    public void printBooks(List<Book> books) {
        if (books.isEmpty()) {
            System.out.println("Книги не знайдені.");
        } else {
            for (Book book : books) {
                System.out.println("Назва: " + book.getTitle());
                System.out.println("Автор: " + book.getAuthor());
                System.out.println("Видавництво: " + book.getPublisher());
                System.out.println("Рік видання: " + book.getYear());
                System.out.println("Кількість сторінок: " + book.getPages());
                System.out.println("Ціна: " + book.getPrice());
                System.out.println();
            }
        }
    }

    public void printMessage(String message) {
        System.out.println(message);
    }
}

public class Main {
    public static void main(String[] args) {
        // Створення масиву даних
        List<Book> allBooks = new ArrayList<>();
        allBooks.add(new Book("Книга 1", "Автор 1", "Видавництво 1", 2022, 300, 20.0));
        allBooks.add(new Book("Книга 2", "Автор 2", "Видавництво 2", 2021, 250, 15.0));
        allBooks.add(new Book("Книга 3", "Автор 1", "Видавництво 3", 2020, 350, 18.0));
        allBooks.add(new Book("Книга 4", "Автор 3", "Видавництво 2", 2019, 400, 22.0));
        allBooks.add(new Book("Книга 5", "Автор 2", "Видавництво 4", 2021, 280, 16.0));
        allBooks.add(new Book("Книга 6", "Автор 2", "Видавництво 1", 2022, 280, 16.0));
        allBooks.add(new Book("Книга 7", "Автор 1", "Видавництво 1", 2023, 280, 16.0));
        allBooks.add(new Book("Книга 8", "Автор 3", "Видавництво 2", 2021, 280, 16.0));
        allBooks.add(new Book("Книга 9", "Автор 4", "Видавництво 3", 2022, 280, 16.0));
        allBooks.add(new Book("Книга 10", "Автор 3", "Видавництво 2", 2023, 280, 16.0));
        allBooks.add(new Book("Книга 11", "Автор 1", "Видавництво 3", 2014, 280, 16.0));
        allBooks.add(new Book("Книга 12", "Автор 4", "Видавництво 4", 2015, 280, 16.0));
        allBooks.add(new Book("Книга 13", "Автор 1", "Видавництво 1", 2013, 280, 16.0));
        allBooks.add(new Book("Книга 14", "Автор 4", "Видавництво 4", 2021, 280, 16.0));
        allBooks.add(new Book("Книга 15", "Автор 4", "Видавництво 1", 2018, 280, 16.0));

        Collections.shuffle(allBooks);
        List<Book> books = allBooks.subList(0, 10);

        BookController controller = new BookController(books);
        BookView view = new BookView();

        Scanner scanner = new Scanner(System.in);

        while (true) {
            view.printMessage("Menu:");
            view.printMessage("1. Get a list of books by a specific author");
            view.printMessage("2. Get a list of books published by a specific publisher");
            view.printMessage("3. Get a list of books published after a specific year");
            view.printMessage("4. Sort books by publisher");
            view.printMessage("5. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine();  // Clear the newline character

            switch (choice) {
                case 1:
                    view.printMessage("Enter the author's name:");
                    String author = scanner.nextLine();
                    List<Book> booksByAuthor = controller.getBooksByAuthor(author);
                    view.printBooks(booksByAuthor);
                    break;
                case 2:
                    view.printMessage("Enter the publisher's name:");
                    String publisher = scanner.nextLine();
                    List<Book> publisherBooks = controller.getBooksByPublisher(publisher);
                    view.printBooks(publisherBooks);
                    break;
                case 3:
                    view.printMessage("Enter the year:");
                    int year = scanner.nextInt();
                    List<Book> yearBooks = controller.getBooksPublishedAfterYear(year);
                    view.printBooks(yearBooks);
                    break;
                case 4:
                    controller.sortBooksByPublisher();
                    view.printMessage("Books sorted by publisher:");
                    view.printBooks(books);
                    break;
                case 5:
                    System.exit(0);
                    break;
                default:
                    view.printMessage("Invalid choice. Please try again.");
            }
        }
    }
}

