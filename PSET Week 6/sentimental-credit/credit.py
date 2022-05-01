from sys import exit
from cs50 import get_string


def main():
    cc = get_string("CC Number: ")
    # Copy of the cc for checking if VISA, MASTER or AMEX
    ccCopy = cc
    # If lenght of the cc input is not 13,15 or 16, quit
    if (len(cc)) not in (13, 15, 16):
        print("INVALID")
        exit(1)
    else:
        # Check if lenght of the card is odd or even, to apply the validation correctly
        if ((len(cc) % 2) == 0):
            ccvalidation(cc, ccCopy)
        else:
            # If it's odd, add a 0 in front, so we can use the same formulas
            adjustedcc = '0' + cc
            ccvalidation(adjustedcc, ccCopy)


def ccvalidation(cc, ccCopy):
    evenlist = []
    oddlist = []
    finallist = []
    # Get every other namber, from the second to last, multiply by 2, and sum the digits, add them to the list
    for i in range(0, len(cc), 2):
        evennumber = int(cc[i]) * 2
        evenstring = str(evennumber)
        for j in range(0, len(evenstring), 1):
            evensplit = int(evenstring[j])
            evenlist.append(evensplit)
    # Get every other namber, from the last, multiply by 2, add them to the list
    for l in range(1, len(cc), 2):
        oddnumber = int(cc[l])
        oddlist.append(oddnumber)
    finallist = oddlist + evenlist

    # Verify if the final sum divided by 10 results in 0
    tst = finalsum(finallist)
    finalcheck = int(tst % 10)
    if (finalcheck) != 0:
        print("INVALID")
        exit(1)
    else:
        # Check first 2 digits to determine the type of card
        check = int(ccCopy[0:2])
        if check == 37 or check == 34:
            print("AMEX")
            exit(0)
        elif check <= 55 and check >= 51:
            print("MASTERCARD")
            exit(0)
        elif int(check / 10) == 4:
            print("VISA")
            exit(0)
        else:
            print("INVALID")
            exit(2)

# Sum the numbers on the final list


def finalsum(list):
    sum = 0
    for number in list:
        sum += number
    return sum


if __name__ == "__main__":
    main()
