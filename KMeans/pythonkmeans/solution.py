import random

centers = []

input_file = "my_data9.txt"
output_file = "result9.txt"

def input():
    with open(input_file) as f:
        content = f.readlines()
    input_arr = []
    content = [x.strip() for x in content]
    counter = 0
    for x in content:
        sp = x.split(' ')
        input_arr.append([float(sp[0]), float(sp[1])])
    return input_arr



def calc_dist(x_1, x_2):
    return (x_1[0] - x_2[0]) ** 2 + (x_1[1] - x_2[1]) ** 2

INF = 100000000

def get_closest(point, k):
    min_dist, min_ind = INF, 0

    for j in range(k):
        dist = calc_dist(point, centers[j])
        if dist < min_dist:
            min_dist = dist
            min_ind = j
    return min_ind

def run_k_means(arr, k):
    for _ in range (k):
        rnd = random.randint(0, len(arr) - 1)
        centers.append(arr[rnd])

    cluster = [0 for _ in range(len(arr))]
    changed = True

    while changed:
        changed = False

        for i in range(len(arr)):
            new_cluster = get_closest(arr[i], k)
            if new_cluster != cluster[i]:
                changed = True
                cluster[i] = new_cluster

        for i in range(k):
            points = []
            for j in range(len(arr)):
                if cluster[j] == i:
                    points.append(arr[j])
            if len(points) == 0:
                continue

            centers[i][0] = sum(point[0] for point in points) / len(points)
            centers[i][1] = sum(point[1] for point in points) / len(points)

    return cluster

def main():
    colors = [
        "red", "green", "black", "yellow", "gray", "blue"
    ];

    k = 3

    input_arr = input()
    another_arr = []

    for i in range(len(input_arr)):
        another_arr.append([input_arr[i][0], input_arr[i][1]])
        print(input_arr[i][0], input_arr[i][1])
    print("\n")


    clstr = run_k_means(another_arr, k)

    with open(output_file, "w") as text_file:
        for i in range(len(input_arr)):
            print(input_arr[i][0], input_arr[i][1], colors[clstr[i]])
            text_file.write("{0} {1} {2}\n".format(input_arr[i][0], input_arr[i][1], colors[clstr[i]]))

main()
