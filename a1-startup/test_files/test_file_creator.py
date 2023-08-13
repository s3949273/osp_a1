import random
import string

def generate_random_word(size):
  """Generates a random word of a given size."""
  letters = string.ascii_lowercase
  return ''.join([random.choice(letters) for _ in range(size)])+" "

def main():
  """Generates a text file with random words of a given size."""
  size = int(input("Enter the size of the random words: "))
  with open('a.txt', 'w') as f:
    for _ in range(10000000):
        for _ in range(10):
            f.write(generate_random_word(size))
        f.write("\n")

if __name__ == '__main__':
  main()