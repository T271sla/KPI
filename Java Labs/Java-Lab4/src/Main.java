import java.util.ArrayList;
import java.util.List;

// Клас, що представляє людину
class Person {
    public Person(){}
}

// Класи, що представляють спеціальних пасажирів
class Fireman extends Person {}
class Policeman extends Person {}

// Клас, що представляє автомобіль
class Vehicle<T> {
    protected int maxSeats;
    protected int seatsTaken;
    protected List<? super T> passengers; // Use a wildcard for the passenger list

    public Vehicle(int maxSeats) {
        this.maxSeats = maxSeats;
        seatsTaken = 0;
        passengers = new ArrayList<>();
    }

    public int getMaxSeats() {
        return maxSeats;
    }

    public int getSeatsTaken() {
        return seatsTaken;
    }

    public void takePassenger(T passenger) {
        if (seatsTaken < maxSeats) {
            passengers.add(passenger);
            seatsTaken++;
        } else {
            throw new RuntimeException("Всі місця зайняті");
        }
    }

    public void dropOffPassenger(T passenger) {
        if (passengers.contains(passenger)) {
            passengers.remove(passenger);
            seatsTaken--;
        } else {
            throw new RuntimeException("Цей пасажир не знаходиться в автомобілі");
        }
    }
}


// Підкласи для конкретних видів автомобілів
class Bus extends Vehicle {
    public Bus(int maxSeats) {
        super(maxSeats);
    }
}

class Car extends Vehicle {
    public Car(int maxSeats) {
        super(maxSeats);
    }
}

class Taxi extends Car {
    public Taxi(int maxSeats) {
        super(maxSeats);
    }
}

class PoliceCar extends Car {
    public PoliceCar(int maxSeats) {
        super(maxSeats);
    }
}

class FireTruck<T> extends Car {
    public FireTruck(int maxSeats) {
        super(maxSeats);
    }

    @Override
    public void takePassenger(Object person) {
        if (person instanceof Fireman) {
            super.takePassenger(person);
        } else {
            throw new IllegalArgumentException("Only Fireman can be added to a FireTruck.");
        }
    }
}

class Road {
    public List<? super Vehicle> carsInRoad = new ArrayList<>();

    public int getCountOfHumans() {
        int totalHumans = 0;

        for (Object obj : carsInRoad) {
            if (obj instanceof Vehicle) {
                Vehicle vehicle = (Vehicle) obj;
                totalHumans += vehicle.getSeatsTaken();
            }
        }

        return totalHumans;
    }

    public void addCarToRoad(Vehicle car) {
        carsInRoad.add(car);
    }
}


public class Main {
    public static void main(String[] args) {
        Fireman dude = new Fireman();
        FireTruck truck = new FireTruck<>(3);
        System.out.println(truck.getMaxSeats());
        truck.takePassenger(dude);

        Person man = new Person();
        Person guy = new Person();
        Car car = new Car(5);
        car.takePassenger(man);
        car.takePassenger(guy);;
        System.out.println(car.getSeatsTaken());

        Road road = new Road();
        road.addCarToRoad(truck);
        road.addCarToRoad(car);
        System.out.println(road.getCountOfHumans());

    }
}
