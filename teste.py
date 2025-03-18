def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(num ** 0.5) + 1):
        if num % i == 0:
            return False
    return True

def print_divisors(num):
    print(f"Divisors of {num}: ", end="")
    for i in range(1, num + 1):
        if num % i == 0:
            print(i, end=" ")
    print()

# Main program
number = int(input("Enter a number: "))

# Check if the number is even or odd
if number % 2 == 0:
    print(f"{number} is Even")
else:
    print(f"{number} is Odd")

# Check if the number is prime
if is_prime(number):
    print(f"{number} is a Prime number")
else:
    print(f"{number} is not a Prime number")

# Print the divisors of the number
print_divisors(number)
