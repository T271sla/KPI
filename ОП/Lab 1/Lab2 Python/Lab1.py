import math

def func():
    PI = math.pi
    print("Enter radius(R):")
    R = int(input())
    print("Enter height(H):")
    H = int(input())
    V1 = float(R * R * H * PI)
    V2 = float(V1/3)
    print("Volume of the cylinder:")
    print (V1)
    print ("Volume of the cone:")
    print(V2)
    input("Press Enter to continue.")
func()