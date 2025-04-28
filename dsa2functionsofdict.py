MAX = 10  # Define maximum size for the hash table

class WOChain:
    def __init__(self):
        self.a = [[-1, -1] for _ in range(MAX)]  # Initialize the hash table with -1

    def hash_key(self, num):
        key = num % 10
        return key

    def chain(self, key, num):
        flag = False
        count = sum(1 for i in self.a if i[0] != -1)  # Count number of filled slots

        if count == MAX:
            print("\nHash Table Is Full")
            self.display()
            exit(1)

        if self.a[key][0] == -1:
            self.a[key][0] = num
        else:
            ch = self.a[key][1]  # Get the chain index
            if ch == -1:
                # Linear probing in the table if the chain is not yet established
                for i in range(key + 1, MAX):
                    if self.a[i][0] == -1:
                        self.a[i][0] = num
                        self.a[key][1] = i
                        flag = True
                        break

                if not flag:
                    for i in range(0, key):
                        if self.a[i][0] == -1:
                            self.a[i][0] = num
                            self.a[key][1] = i
                            flag = True
                            break
            else:
                while self.a[ch][0] != -1 and self.a[ch][1] != -1:
                    ch = self.a[ch][1]

                for i in range(ch + 1, MAX):
                    if self.a[i][0] == -1:
                        self.a[i][0] = num
                        self.a[ch][1] = i
                        flag = True
                        break

                if not flag:
                    for i in range(0, key):
                        if self.a[i][0] == -1:
                            self.a[i][0] = num
                            self.a[ch][1] = i
                            flag = True
                            break

    def display(self):
        print("\nThe Hash Table is...")
        for i in range(MAX):
            print(f"{i} {self.a[i][0]} {self.a[i][1]}")

# Main function to drive the program
def main():
    h = WOChain()

    n = int(input("\nNumber of elements you want to insert into HT: "))
    if n <= MAX:
        for i in range(n):
            num = int(input("\nEnter The Number: "))
            key = h.hash_key(num)
            h.chain(key, num)

        h.display()
    else:
        print("Hash table size = 10")

if __name__ == "__main__":
    main()
