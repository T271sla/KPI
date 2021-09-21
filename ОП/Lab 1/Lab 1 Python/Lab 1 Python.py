import math

def func():
    PI = math.pi

    #Введення даних
    print("Enter the radius(R):")
    R = int(input())
    print("Enter the height(H):")
    H = int(input())

    #Розрахунок
    V1 = float(R * R * H * PI)
    V2 = float(V1/3)

    #Виведення даних
    print("Volume of the cylinder:")
    print (V1)
    print ("Volume of the cone:")
    print(V2)
    input("Press Enter to continue.")
func()