def func(n):
    if n >=10:
        while n >= 10:
            k = n
            n /= 10
        mod = (k % 10) / 10
        func_res = n - mod
        return func_res
    else:
        func_res=n
        return func_res
        
print ("Enter a, b, c ∈ [1; +inf)")
a = int(input())
b = int(input())
c = int(input())

if a >= 1 and b >= 1 and c >= 1:
    res = func(a) + func(b) + func(c)
    print ("Sum of first digits of entered numbers is:", res)
else:
    print ("One number (or more) doesn't belong to the required range. Try again.")

input("Press Enter to continue.")