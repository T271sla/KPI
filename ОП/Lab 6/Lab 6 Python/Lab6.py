def func(n):
    if n >=10:
        while n >= 10:
            n /= 10
        return int (n)
    else:
        return int (n)
        
print ("Enter a, b, c ∈ [1; +inf)")
a = int(input())
b = int(input())
c = int(input())

if a >= 1 and b >= 1 and c >= 1:
    sum = func(a) + func(b) + func(c)
    print ("Sum of first digits of entered numbers is:", sum)
else:
    print ("One number (or more) doesn't belong to the required range. Try again.")

input("Press Enter to continue.")
