# Function to read paths from files
def read_paths_from_files(file_paths):
    paths = []
    for file_path in file_paths:
        with open(file_path, "r") as file:
            paths.extend(file.read().splitlines())
    return paths


# Sample input file paths (one for each laptop)
file_paths = ["laptop1.txt", "laptop2.txt", "laptop3.txt"]

# Read paths from files
input_data = read_paths_from_files(file_paths)

# Map: Split each path into its components and calculate the length of each path
mapped_data = [(path.split("/"), len(path.split("/"))) for path in input_data]

# Reduce: Find the longest path(s)
longest_path = max(mapped_data, key=lambda x: x[1])

# Output the longest path(s)
print("Longest path(s):", "/".join(longest_path[0]))
