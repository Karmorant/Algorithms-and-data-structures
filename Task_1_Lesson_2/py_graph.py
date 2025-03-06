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
    names=["Size", "BubbleSort", "ImprovedBubbleSort", "ShakerSort", "CombSort"]
)

plt.figure(figsize=(10, 5))
plt.plot(size_data["Size"], size_data["BubbleSort"], label="Bubble Sort")
plt.plot(size_data["Size"], size_data["ImprovedBubbleSort"], label="Improved Bubble Sort")
plt.plot(size_data["Size"], size_data["ShakerSort"], label="Shaker Sort")
plt.plot(size_data["Size"], size_data["CombSort"], label="Comb Sort")
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
    names=["SortedPercentage", "BubbleSort", "ImprovedBubbleSort", "ShakerSort", "CombSort"]
)

plt.figure(figsize=(10, 5))
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["BubbleSort"], label="Bubble Sort")
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["ImprovedBubbleSort"], label="Improved Bubble Sort")
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["ShakerSort"], label="Shaker Sort")
plt.plot(sorted_percentage_data["SortedPercentage"], sorted_percentage_data["CombSort"], label="Comb Sort")
plt.xlabel("Sorted Percentage")
plt.ylabel("Time (seconds)")
plt.title("Time vs Sorted Percentage")
plt.legend()
plt.grid(True)
plt.show()