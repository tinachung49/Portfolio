import sys

class Record:
    def __init__(self, category, description, amount):
        self._category = category
        self._description = description
        self._amount = amount

    @property
    def category(self):
        return self._category

    @property
    def description(self):
        return self._description

    @property
    def amount(self):
        return self._amount


class Records:
    def __init__(self):
        self._initial_money, record_data = self._initialize()
        self._records = [Record(*data) for data in record_data]

    def _initialize(self):
        records = []
        try:
            with open('records.txt', 'r') as f:
                lines = f.readlines()
                if not lines:
                    raise ValueError("Empty file")
                try:
                    initial_money = int(lines[0].strip())
                except ValueError:
                    sys.stderr.write("Invalid value for initial money in records.txt.\n")
                    raise ValueError
                for line in lines[1:]:
                    parts = line.strip().rsplit(' ', 2)
                    if len(parts) != 3 or not parts[2].lstrip('-').isdigit():
                        raise ValueError
                    cat, desc, amt = parts
                    records.append((cat, desc, int(amt)))
        except FileNotFoundError:
            try:
                initial_money = int(input("How much money do you have? "))
            except ValueError:
                sys.stderr.write("Invalid value for money. Set to 0 by default.\n")
                initial_money = 0
        except ValueError:
            sys.stderr.write("Invalid format in records.txt. Deleting the contents.\n")
            open('records.txt', 'w').close()
            try:
                initial_money = int(input("How much money do you have? "))
            except ValueError:
                sys.stderr.write("Invalid value for money. Set to 0 by default.\n")
                initial_money = 0
            records = []
        return initial_money, records

    def add(self, record_input, categories):
        try:
            temp = [tuple(item.strip().rsplit(' ', 2)) for item in record_input.split(',')]
            for cat, desc, amt in temp:
                if not categories.is_category_valid(cat):
                    sys.stderr.write("The specified category is not in the category list.\n")
                    sys.stderr.write('You can check the category list by command "view categories".\n')
                    sys.stderr.write("Fail to add a record.\n")
                    return
            for cat, desc, amt in temp:
                self._records.append(Record(cat, desc, int(amt)))
        except ValueError:
            sys.stderr.write("The format of a record should be like this: meal breakfast -50.\n")
            sys.stderr.write("Fail to add a record.\n")
        except Exception:
            sys.stderr.write("Fail to add a record.\n")

    def view(self):
        print("Here's your expense and income records:")
        print(f"{'Category':<15} {'Description':<20} {'Amount':>6}")
        print(f"{'='*15} {'='*20} {'='*6}")
        for r in self._records:
            print(f"{r.category:<15} {r.description:<20} {r.amount:>6}")
        print(f"{'='*15} {'='*20} {'='*6}")
        balance = self._initial_money + sum(r.amount for r in self._records)
        print(f"Now you have {balance} dollars.")

    def delete(self, index):
        try:
            index = int(index) - 1
            if 0 <= index < len(self._records):
                r = self._records.pop(index)
                print(f"Deleted record: {r.category} {r.description} {r.amount}")
            else:
                sys.stderr.write("Invalid record number.\n")
        except ValueError:
            sys.stderr.write("Invalid format. Fail to delete a record.\n")

    def find(self, target_categories):
        filtered = [r for r in self._records if r.category in target_categories]
        print("Here's your expense and income records under category:")
        print(f"{'Category':<15} {'Description':<20} {'Amount':>6}")
        print(f"{'='*15} {'='*20} {'='*6}")
        total = 0
        for r in filtered:
            print(f"{r.category:<15} {r.description:<20} {r.amount:>6}")
            total += r.amount
        print(f"{'='*15} {'='*20} {'='*6}")
        print(f"The total amount above is {total}.")

    def save(self):
        with open('records.txt', 'w') as f:
            f.write(f"{self._initial_money}\n")
            for r in self._records:
                f.write(f"{r.category} {r.description} {r.amount}\n")


class Categories:
    def __init__(self):
        self._categories = [
            'expense', ['food', ['meal', 'snack', 'drink'], 'transportation', ['bus', 'railway']],
            'income', ['salary', 'bonus']
        ]

    def view(self, categories=None, indent=0):
        if categories is None:
            categories = self._categories
        i = 0
        while i < len(categories):
            if isinstance(categories[i], str):
                print('  ' * indent + '- ' + categories[i])
                if i + 1 < len(categories) and isinstance(categories[i + 1], list):
                    self.view(categories[i + 1], indent + 1)
                    i += 1
            i += 1

    def is_category_valid(self, category, categories=None):
        if categories is None:
            categories = self._categories
        for i in range(len(categories)):
            if isinstance(categories[i], str) and categories[i] == category:
                return True
            elif isinstance(categories[i], list):
                if self.is_category_valid(category, categories[i]):
                    return True
        return False

    def find_subcategories(self, category):
        def find_subcategories_gen(category, categories, found=False):
            if isinstance(categories, list):
                for index, child in enumerate(categories):
                    yield from find_subcategories_gen(category, child, found)
                    if child == category and index + 1 < len(categories) and isinstance(categories[index + 1], list):
                        yield from find_subcategories_gen(category, categories[index + 1], True)
            else:
                if categories == category or found:
                    yield categories

        return list(find_subcategories_gen(category, self._categories))


categories = Categories()
records = Records()

while True:
    command = input('\nWhat do you want to do (add / view / delete / view categories / find / exit)? ').strip().lower()
    if command == 'add':
        record = input('Add some expense or income records with category, description, and amount (separate by spaces):\ncat1 desc1 amt1, cat2 desc2 amt2, cat3 desc3 amt3, ...\n')
        records.add(record, categories)
    elif command == 'view':
        records.view()
    elif command == 'delete':
        for i, r in enumerate(records._records):
            print(f"{i+1}. {r.category:<15} {r.description:<20} {r.amount}")
        delete_index = input("Which record do you want to delete? ")
        records.delete(delete_index)
    elif command == 'view categories':
        categories.view()
    elif command == 'find':
        category = input('Which category do you want to find? ')
        target_categories = categories.find_subcategories(category)
        records.find(target_categories)
    elif command == 'exit':
        records.save()
        break
    else:
        sys.stderr.write('Invalid command. Try again.\n')
