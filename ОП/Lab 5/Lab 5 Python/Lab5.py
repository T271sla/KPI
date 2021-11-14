for n in range(100,201):
    if all(n % i != 0 for i in range(2,n)):
        sum = 1 + ((n - 1) % 9)
        print(f"\nDigital root of {n} is {sum}")
input("Press Enter to continue.")