def func():
    
    print("Enter a:")
    a = float(input())
    print("Enter b:")
    b = float(input())
    print("Enter c:")
    c = float(input())
    Sum_1 = a + b
    Sum_2 = a + b
    Sum_3 = b + c
    
    if Sum_1 % 2 == 0:
        print('a+b is even')
    else:
        print('a+b is uneven')
    
    if Sum_2 % 2 == 0:
        print('a+c is even')
    else:
        print('a+c is uneven')
    
    if Sum_3 % 2 == 0:
        print('b+c is even')
    else:
        print('b+c is uneven')

    input("Press Enter to continue.")

func()