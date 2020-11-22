from random import randint
from time import time

def is_prime_recursive(n, div = 2, div_count = 0):
  if n < 2 or div_count > 0: return False
  if div == n: return n
  if n % div == 0: div_count+=1
  return is_prime_recursive(n, div+1, div_count)

def is_prime_iterative(n):
  if n < 2: return False
  div = 2
  while div < n:
    if n % div == 0: return False
    div+=1
  return n

def highest_prime_number_finder(l, is_prime_func):
  highest_prime = 0
  for n in l:
    is_prime = is_prime_func(n)
    if is_prime and is_prime > highest_prime: highest_prime = is_prime
  return highest_prime

def is_prime_runtime_test(l, is_prime_func):
  start = time()
  highest_prime_number_finder(l, is_prime_func)
  return time() - start

def random_int_list():
  l = []
  for i in range(1000):
    l.append(randint(1, 1000))
  return l

l = random_int_list()
recursive_runtime = is_prime_runtime_test(l, is_prime_recursive)
iterative_runtime = is_prime_runtime_test(l, is_prime_iterative)

print('Recursive runtime:', recursive_runtime)
print('Iterative runtime:', iterative_runtime)
print('Runtime diff:', abs(recursive_runtime - iterative_runtime))
