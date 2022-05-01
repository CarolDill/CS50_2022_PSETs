def main():
    # Use height to build pyramid
    height = get_height()
    for i in range(height):
        for j in range(height - i - 1, 0, -1):
            print(" ", end="")
        for k in range(i + 1):
            print("#", end="")
        print("  ", end="")
        for l in range(i + 1):
            print("#", end="")
        print()


# No use of cs50 library, ask user for input
def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                break
        # If not a number, continue asking
        except ValueError:
            n = int(input("Height: "))
    return n


main()