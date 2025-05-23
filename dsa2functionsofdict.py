MAX = 10  # Define maximum size for the hash table

class HashTable:
    def __init__(self):
        # Initialize the hash table with -1
        self.table = [[-1, -1] for _ in range(MAX)]

    def hash_key(self, num):
        # Simple hash function: modulo by 10
        return num % MAX

    def insert(self, num):
        key = self.hash_key(num)
        if self.table[key][0] == -1:
            # Insert directly if the slot is empty
            self.table[key][0] = num
        else:
            # Linear probing for collision resolution
            i = key
            while self.table[i][0] != -1:
                i = (i + 1) % MAX
                if i == key:  # If table is full
                    print("Hash Table is full!")
                    return
            self.table[i][0] = num

    def find(self, num):
        key = self.hash_key(num)
        i = key
        while self.table[i][0] != -1:
            if self.table[i][0] == num:
                print(f"Found {num} at index {i}")
                return
            i = (i + 1) % MAX
            if i == key:  # Back to the starting point
                break
        print(f"{num} not found in the table.")

    def delete(self, num):
        key = self.hash_key(num)
        i = key
        while self.table[i][0] != -1:
            if self.table[i][0] == num:
                self.table[i][0] = -1  # Delete the number
                print(f"{num} deleted from index {i}")
                return
            i = (i + 1) % MAX
            if i == key:  # Back to the starting point
                break
        print(f"{num} not found to delete.")

    def display(self):
        print("\nThe Hash Table is...")
        for i in range(MAX):
            print(f"Index {i}: {self.table[i][0]}")

# Main function to drive the program
def main():
    ht = HashTable()

    n = int(input("\nNumber of elements you want to insert into HT: "))
    if n <= MAX:
        for i in range(n):
            num = int(input("\nEnter The Number: "))
            ht.insert(num)
        ht.display()
    else:
        print("Cannot insert more than 10 elements.")
    
    # Perform some find and delete operations
    find_num = int(input("\nEnter a number to find: "))
    ht.find(find_num)
    
    delete_num = int(input("\nEnter a number to delete: "))
    ht.delete(delete_num)

    ht.display()

if __name__ == "__main__":
    main()
