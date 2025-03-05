import matplotlib.pyplot as plt
import pandas as pd
from io import StringIO


with open("sorting_times.txt", "r") as file:
    data = file.read()

parts = data.strip().split("\n\n")

size_data = pd.read_csv(
    StringIO(parts[0]),
    sep='\s+',
    header=None, 
    names=["Size", "RadixSortTime", "StdSortTime"]
)

size_data["RadixSortTime"] = size_data["RadixSortTime"].replace(0, 1e-10)
size_data["StdSortTime"] = size_data["StdSortTime"].replace(0, 1e-10)

plt.figure(figsize=(10, 5))
plt.plot(size_data["Size"], size_data["RadixSortTime"], label="Radix Sort")
plt.plot(size_data["Size"], size_data["StdSortTime"], label="std::sort")
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.title("Time vs Array Size")
plt.legend()
plt.xscale("log")
plt.yscale("log")
plt.grid(True)
plt.show()


sorted_percentage_data = pd.read_csv(
    StringIO(parts[1]),
    sep='\s+',
    header=None, 
    names=["SortedPercentage", "RadixSortTime", "StdSortTime"]
)

sorted_percentage_data["RadixSortTime"] = sorted_percentage_data["RadixSortTime"].replace(0, 1e-10)
sorted_percentage_data["StdSortTime"] = sorted_percentage_data["StdSortTime"].replace(0, 1e-10)

plt.figure(figsize=(10, 5))
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["RadixSortTime"], label="Radix Sort")
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["StdSortTime"], label="std::sort")
plt.xlabel("Sorted Percentage")
plt.ylabel("Time (seconds)")
plt.title("Time vs Sorted Percentage")
plt.legend()
plt.grid(True)
plt.show()


num_digits_data = pd.read_csv(
    StringIO(parts[2]),
    sep='\s+',
    header=None, 
    names=["NumDigits", "RadixSortTime", "StdSortTime"]
)


num_digits_data["RadixSortTime"] = num_digits_data["RadixSortTime"].replace(0, 1e-10)
num_digits_data["StdSortTime"] = num_digits_data["StdSortTime"].replace(0, 1e-10)

plt.figure(figsize=(10, 5))
plt.plot(num_digits_data["NumDigits"], num_digits_data["RadixSortTime"], label="Radix Sort")
plt.plot(num_digits_data["NumDigits"], num_digits_data["StdSortTime"], label="std::sort")
plt.xlabel("Number of Digits")
plt.ylabel("Time (seconds)")
plt.title("Time vs Number of Digits")
plt.legend()
plt.grid(True)
plt.show()